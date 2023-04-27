//
// Created by Иван Березуцкий on 26.04.2023.
//

#ifndef KP_6_FSQL_H
#define KP_6_FSQL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


class fSQL {
public:
    bool parse(string command) {
        const vector<string> &partsOfCommand = split(command, ' ');
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

private:

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
    }

    void select(const vector<string> command) {
        int startIndex = 1;
        string fileName = "";
        vector<string> columns;
        if (command.at(1) == "*") {
            fileName = command.at(3);
        }

        while (command.at(startIndex) != "from") {
            columns.push_back(command.at(startIndex));
            startIndex++;
        }

        fileName = command.at(startIndex + 2);
        vector<string> conditions;
        if (startIndex + 3 < command.size() - 1) {
            for (int i = startIndex + 3; i < command.size(); i++) {
                conditions.push_back(command.at(i));
            }
        }

        ifstream in(fileName);
        if (in.is_open()) {
            string first_line;
            string line;
            getline(in, first_line);
            vector<string> columns = split(first_line, ',');

            while (getline(in, line)) {
                if (command.at(1) == "*") {
                    cout << line << endl;
                } else {
                    const string &copy_line = line;
                    vector<string> actual_line = split(copy_line, ',');
                    /*
                     * 1. Бежимся по conditions, смотрим какие нам нужны колонки вообще
                     * 2. Определяем индексы этих колонок в перемнной columns
                     * 3. Смотрим, чтобы значения, которые мы передали в where были равны тому что лежит в строке
                     * 4. Если это так, то выводим на экран эту  никому не нужную залупу
                     */
                    vector<vector<string>> all_columns_and_values;
                    for (string el: conditions) {
                        string column;
                        vector<string> column_and_value = split(el, '=');
                        all_columns_and_values.push_back(column_and_value);
                    }
                    vector<int> indexes;
                    for (int i = 0; i < columns.size(); ++i) {
                    }
                }
            }
        }

        in.close();
    }

    void create(const vector<string> command) {
    }

    void deleteFile(const vector<string> command) {
    }

};


#endif //KP_6_FSQL_H
