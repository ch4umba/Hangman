//
// Created by cool8 on 29.09.2021.
//

#ifndef UNTITLED1_THEMES_H
#define UNTITLED1_THEMES_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <unistd.h>

class Themes {
private:
    std::map<std::string, std::vector<std::string>> themes;

    static std::vector<std::string> splitWords(std::string words);

    static bool check(std::string &word);

public:
    friend class Game;

    Themes();

    std::string getWord(const std::string& theme);

    void addUserWord(std::string theme);

    void addFileWords(const std::string& path);
};

#endif //UNTITLED1_THEMES_H
