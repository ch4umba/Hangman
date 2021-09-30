//
// Created by cool8 on 29.09.2021.
//

#ifndef UNTITLED1_GAME_H
#define UNTITLED1_GAME_H

#include "Themes.h"
#include <ctime>
#include <cstdio>
#include <sys/ioctl.h>
#include <termios.h>

using namespace std;

class Game {
private:
    Themes themes;

    const string win{"*          *    ***    *        *     *        *    "
                     "******    ***       **\n"
                     "*          *     *     **       *     **       *    *     "
                     "    *  *      **\n"
                     "*          *     *     *  *     *     *  *     *    *     "
                     "    *   *     **\n"
                     "*          *     *     *   *    *     *   *    *    "
                     "******    *  *      **\n"
                     "*    **    *     *     *     *  *     *     *  *    *     "
                     "    * *       **\n"
                     "*  *    *  *     *     *      * *     *      * *    *     "
                     "    *   *       \n"
                     "**        **     *     *       **     *       **    *     "
                     "    *    *    **\n"
                     "*          *    ***    *        *     *        *    "
                     "******    *     *   **\n"};

    const vector<string> phase{{"\n"
                                "\n"
                                "\n"
                                "\n"
                                "\n"
                                "\n"
                                "\n"
                                "\n"
                                "\n"
                                "\n"
                                "\n"
                                "    $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                                "    $                          $\n"},
                               {"           $$$$$$$$$$$$$$$\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "    $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                                "    $                          $\n"},
                               {"           $$$$$$$$$$$$$$$\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "    $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                                "    $                          $\n"},
                               {"           $$$$$$$$$$$$$$$\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           O             $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "    $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                                "    $                          $\n"},
                               {"           $$$$$$$$$$$$$$$\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           O             $\n"
                                "         /   \\           $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "    $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                                "    $                          $\n"},
                               {"           $$$$$$$$$$$$$$$\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           O             $\n"
                                "         / | \\           $\n"
                                "           |             $\n"
                                "                         $\n"
                                "                         $\n"
                                "                         $\n"
                                "    $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                                "    $                          $\n"},
                               {"           $$$$$$$$$$$$$$$\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           |             $\n"
                                "           O             $\n"
                                "         / | \\           $\n"
                                "           |             $\n"
                                "          / \\            $\n"
                                "                         $\n"
                                "                         $\n"
                                "    $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                                "    $       GAME OVER!         $\n"}};

    const vector<char> alpha{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                             'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                             'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    string word;
    string outWord;
    int _phase = 0;

    static int getch();

    static int gotoXY(int x, int y);

    void outputPhase(int i);

    void outputAlphas();

    static void outputMenu(int i);

    static void outputWord(const string &word);

    static void outputSettings(int i);

    void Play();

    void Settings();

    static int clrscr();

    static int setFGColor();

    static int setBGColor();

    static int defcolor();

    string getTheme();

public:
    void Menu();

    static bool isWin(const string &word);

    void setWord(const string &theme);

    bool checkWord(int i, int j);
};


#endif //UNTITLED1_GAME_H
