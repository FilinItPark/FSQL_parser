//
// Created by Иван Березуцкий on 26.04.2023.
//

#ifndef KP_6_FILEPARSER_H
#define KP_6_FILEPARSER_H


#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class FileParser {
public:
    static bool parse(const std::string &command) {
        if (command.find("create file ") == 0) {
            std::string filename = command.substr(12);
            std::ofstream file(filename + ".txt");
            return true;
        } else if (command.find("select * from ") == 0) {
            std::string filename = command.substr(14);
            std::stringstream ss(command);
            std::string token;
            std::vector<std::string> tokens;
            while (std::getline(ss, token, ' ')) {
                tokens.push_back(token);
            }
            int limit = -1;
            if (tokens.size() > 4 && tokens[4] == "limit") {
                try {
                    limit = std::stoi(tokens[5]);
                } catch (...) {
                    return false;
                }
            }
            std::ifstream file(filename + ".txt");
            if (!file) {
                return false;
            }
            std::string line;
            int count = 0;
            while (limit < 0 || count < limit) {
                if (!std::getline(file, line)) {
                    break;
                }
                // do something with each line
                count++;
            }
            return true;
        } else if (command.find("select ") == 0) {
            std::string filename = command.substr(7);
            std::stringstream ss(filename);
            std::string token;
            std::vector<std::string> tokens;
            while (std::getline(ss, token, ' ')) {
                tokens.push_back(token);
            }
            if (tokens.size() < 3 || tokens[1] != "from") {
                return false;
            }
            std::ifstream file(tokens[2] + ".txt");
            if (!file) {
                return false;
            }
            std::string line;
            std::vector<int> indices;
            ss = std::stringstream(tokens[0]);
            while (std::getline(ss, token, ',')) {
                try {
                    indices.push_back(std::stoi(token));
                } catch (...) {
                    return false;
                }
            }
            int limit = -1;
            if (tokens.size() > 3 && tokens[3] == "limit") {
                try {
                    limit = std::stoi(tokens[4]);
                } catch (...) {
                    return false;
                }
            }
            int count = 0;
            while (limit < 0 || count < limit) {
                if (!std::getline(file, line)) {
                    break;
                }
                std::stringstream ss(line);
                std::string cell;
                int col = 0;
                while (std::getline(ss, cell, ',')) {
                    if (indices.empty() || std::find(indices.begin(), indices.end(), col) != indices.end()) {
                        // do something with the cell
                    }
                    col++;
                }
                count++;
            }
            return true;
        } else if (command.find("insert into ") == 0) {
            std::string filename = command.substr(12);
            std::stringstream ss(filename);
            std::string token;
            std::vector<std::string> tokens;
            while (std::getline(ss, token, ' ')) {
                tokens.push_back(token);
            }
            if (tokens.size() < 1) {
                return false;
            }
            std::ofstream file(tokens[0] + ".txt", std::ios::app);
//            if (!file
        }
    }
}


#endif //KP_6_FILEPARSER_H
