#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string str, char separator) {
    int startIndex = 0, endIndex = 0;
    vector<string> strings;
    for (int i = 0; i <= str.size(); i++) {

        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}


void createTable(const string &query) {
    istringstream iss(query);
    string tableName;
    vector<string> columns;
    string column;

    // Получаем имя таблицы
    iss.ignore(256, ' ');
    iss.ignore(256, ' ');
    iss >> tableName;

    // Получаем список столбцов
    string columnsStr;
    getline(iss, columnsStr, '(');
    getline(iss, columnsStr, ')');

    istringstream issColumns(columnsStr);
    while (getline(issColumns, column, ',')) {
        columns.push_back(column);
    }

    // Создаем файл с именем tableName.csv
    ofstream file;
    auto fileName = tableName + ".csv";
    file.open(fileName);

    if (file.is_open()) {
        // Записываем заголовок таблицы в файл
        cout << columns.size();
        for (size_t i = 0; i < columns.size(); ++i) {
            const vector<string> &splitted = split(columns[i], ' ');
            file << splitted.at(0);
            if (i != columns.size() - 1) {
                file << ",";
            }
        }
        file << endl;

        cout << "Файл " << tableName << ".csv успешно создан." << endl;

        file.close();

    } else {
        cout << "Не удалось создать файл." << endl;
    }

}


void insertValues(const string &query) {
    istringstream iss(query);
    string tableName;
    string values;

    // Получаем имя таблицы
    iss.ignore(256, ' ');
    iss.ignore(256, ' ');
    iss >> tableName;

    // Получаем список значений
    string valuesStr;
    getline(iss, valuesStr, '(');
    getline(iss, valuesStr, ')');

    ofstream file(tableName + ".csv", ios::app);
    if (file.is_open()) {


        file << valuesStr << endl;
        cout << valuesStr << endl;
        cout << "Значения успешно добавлены в файл " << tableName << ".csv." << endl;
        file.close();
    } else {
        cout << "Не удалось открыть файл." << endl;
    }
}

vector<string> select(const vector<string> command) {
    int startIndex = 1;
    string fileName = "";
    vector<string> columns;
    if (command.at(1) == "*") {
        fileName = command.at(3);
    }

    while (command.at(startIndex) != "from" && command.at(startIndex) != "*") {
        columns.push_back(command.at(startIndex));
        if (command.at(startIndex + 1) == "from") break;
        startIndex++;
    }

    fileName = command.at(startIndex + 2);
    vector<string> conditions;
    if (startIndex + 3 < command.size() - 1) {
        for (int i = startIndex + 4; i < command.size(); i++) {
            conditions.push_back(command.at(i));
        }
    }

    vector<string> res;


    ifstream in("/Users/1ommy/university/kp_6/" + fileName + ".csv");
    if (in.is_open()) {
        string first_line;
        string line;
        getline(in, first_line);
        vector<string> columns_in_file = split(first_line, ',');

        while (getline(in, line)) {
            if (conditions.empty() && command.at(1) == "*") res.push_back(line);
            if (command.at(1) == "*") {
                res.push_back(line);
//                cout << line << endl;
            } else {
                const string &copy_line = line;
                vector<string> actual_line = split(copy_line, ',');

                vector<vector<string>>
                        all_columns_and_values;

                for (string el: conditions) {
                    string column;
                    vector<string> column_and_value = split(el, '=');
                    all_columns_and_values.push_back(column_and_value);
                }

                bool is_ok = 1;

                for (auto el: all_columns_and_values) {
                    string column = el.at(0);
                    string value = el.at(1);

                    for (int i = 0; i < columns_in_file.size(); i++) {
                        if (columns_in_file.at(i) == column) {
                            if (actual_line.at(i) != value) is_ok *= 0;
                        }
                    }
                }

                if (is_ok) res.push_back(line);
            }
        }
    } else {
        cout << "ошибка при попытке открыть файл: " << fileName;
    }

    in.close();
    return res;
}


/*
 * сделай связочную таблицу как в many to many
 */
int main() {
    string sqlQuery;

    cout << "Введите SQL команду: ";


    getline(cin, sqlQuery);

    if (sqlQuery.find("create table") != string::npos) {
        createTable(sqlQuery);
    } else if (sqlQuery.find("insert into") != string::npos) {
        insertValues(sqlQuery);
    } else if (sqlQuery.find("select") != string::npos) {
        auto partsOfCommand = split(sqlQuery, ' ');
        auto cmd1 = select(partsOfCommand);

        for (string el: cmd1) {
            cout << el << endl;
        }

        string newSqlQuery;
        cout << "Введите еще одну SQL команду: ";
        getline(cin, newSqlQuery);
//select id,name,surname from users
//select id,cpu,gpu,memory,user_id from pcs
        auto newPartsOfCommand = split(newSqlQuery, ' ');
        auto cmd2 = select(newPartsOfCommand);

        for (int i = 0; i < cmd2.size(); i++) {
            vector<string> current = split(cmd2.at(i), ',');

            if (current.at(1) == "pentium") {
                string user_id = current.at(4);

                for (const auto &i: cmd1) {
                    vector<string> currentUser = split(i, ',');
                    if (currentUser.at(0) == user_id) cout << i << endl;
                }
            }
        }


    } else {
        cout << "Некорректная SQL команда." << endl;
    }

    return 0;
}


// first cmd - select user, second cmd - select pcs
/*
 * users: id, name, surname
 * pcs: id, cpu, gpu, memory, user_id
 */