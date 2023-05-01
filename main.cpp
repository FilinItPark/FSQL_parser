#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>

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


void select(const vector<string> command) {
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

    cout << "FILENAME: " << fileName << endl;
    for (const auto &t: columns) {
        cout << "column: " << t << endl;
    }
    for (const auto &t: conditions) {
        cout << "column: " << t << endl;
    }

    ifstream in("/Users/1ommy/university/kp_6/" + fileName + ".csv");
    if (in.is_open()) {
        string first_line;
        string line;
        getline(in, first_line);
        vector<string> columns_in_file = split(first_line, ',');

        while (getline(in, line)) {
            if (command.at(1) == "*") {
                cout << line << endl;
            } else {
                const string &copy_line = line;
                vector<string> actual_line = split(copy_line, ',');
                /*
                        1.Бежимся по conditions, смотрим какие нам нужны колонки вообще
                      2.Определяем индексы этих колонок в перемнной columns
                        3.Смотрим, чтобы значения, которые мы передали в where были равны тому что лежит в строке
                        4. Если это так, то выводим на экран эту никому не нужную залупу
                */
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

                    for (int i = 0; i < columns.size(); i++) {
                        if (columns_in_file.at(i) == column) {
                            if (actual_line.at(i) != value) is_ok *= 0;
                        }
                    }
                }

                if (is_ok) cout << line << endl;
            }
        }
    } else {
        cout << "ошибка при попытке открыть файл: " << fileName;
    }

    in.close();
}

void create(const vector<string> command) {
    // create table tableName (column1 type,...,columnn type)
    string fileName = command.at(2);
    vector<string> columns;

    for (int i = 4; i < command.size(); i += 3) {
        columns.push_back(command.at(i));
    }

    string templ = "";

    for (int i = 0; i < columns.size() - 1; i++) {
        templ = templ + columns.at(i) + ',';
    }
    templ += columns.at(columns.size() - 1);

    cout << templ;
    ofstream outfile("/Users/1ommy/university/kp_6" + fileName + ".csv");

    outfile << templ << endl;
    outfile.close();
}

void deleteFile(const vector<string> command) {
    if (filesystem::remove("/Users/1ommy/university/kp_6/" + command.at(2) + ".csv")) {
        cout << "File was successfully deleted";
    }
}


bool parse(string command) {
    const vector<string> partsOfCommand = split(std::move(command), ' ');


    const string cmd = partsOfCommand.at(0);
    if (cmd == "select") {
        select(partsOfCommand);
    } else if (cmd == "create") {
        create(partsOfCommand);
    } else if (cmd == "drop") {
        deleteFile(partsOfCommand);
    } else {
        cout << "ПОШЕЛ НАХОЙ";
    }


    return 0;
}


int main() {
    bool res = parse("drop table users");
    cout << res;
}
