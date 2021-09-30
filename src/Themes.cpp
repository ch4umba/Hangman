//
// Created by cool8 on 29.09.2021.
//

#include "Themes.h"

std::vector<std::string> Themes::splitWords(std::string words) {
    std::vector<std::string> w;
    std::string temp;
    for (unsigned int i = 0; i < words.size(); i++) {
        if (words[i] == ' ' || words[i] == words[words.size() - 1]) {
            if (words[i] == words[words.size() - 1]) {
                temp.push_back(words[i]);
            }
            w.push_back(temp);
            temp.clear();
            continue;
        }
        temp.push_back(words[i]);
    }
    return w;
}

bool Themes::check(std::string &word) {
    for (char & i : word) {
        if (!isalpha(i)) {
            return false;
        }
        i = (char)toupper(i);
    }
    return true;
}

Themes::Themes() {
    std::vector<std::string> v;
    v.emplace_back("TRAMPOLINE");
    themes.insert(make_pair("SPORT", v));
}

std::string Themes::getWord(const std::string& theme) {
    return themes[theme][rand() % themes[theme].size()];
}

void Themes::addUserWord(std::string theme) {
    auto iter = themes.find(theme);
    if (!check(theme)) {
        std::cout << "ERROR!" << std::endl;
        sleep(2);
        return;
    }

    if (iter == themes.end()) {
        std::vector<std::string> word;
        std::string w;
        std::cout << "Enter the word:";
        std::cin >> w;
        if (!check(w)) {
            std::cout << "ERROR!" << std::endl;
            sleep(2);
            return;
        }
        word.push_back(w);
        themes.insert(make_pair(theme, word));
    } else {
        std::string w;
        std::cout << "Enter the word:";
        std::cin >> w;
        if (!check(w)) {
            std::cout << "ERROR!" << std::endl;
            sleep(2);
            return;
        }
        iter->second.push_back(w);
    }
}

void Themes::addFileWords(const std::string& path) {
    std::ifstream fin(path);
    if (fin.is_open()) {
        std::map<std::string, std::vector<std::string>>::iterator iter;
        while (!fin.eof()) {
            std::string theme, w;
            fin >> theme;
            fin.get();
            fin.get();
            getline(fin, w);
            w.pop_back();
            iter = themes.find(theme);
            std::vector<std::string> words = splitWords(w);
            if (iter == themes.end()) {
                themes.insert(make_pair(theme, words));
            } else {
                for (auto & word : words) {
                    themes[theme].push_back(word);
                }
            }
        }
    }
    fin.close();
    /* Порядок добавления слов через файл:
    Тема1
    Слово1 Слово2 Слово3 Слово4
    Тема2
    Слово1 Слово2 Слово3 Слово4
    (АНГЛИЙСКИЕ СЛОВА И ТЕМЫ)
    */
}
