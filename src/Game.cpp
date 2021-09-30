//
// Created by cool8 on 29.09.2021.
//

#include "Game.h"

int Game::gotoXY(int y, int x)
{
    return printf("\E[%d;%dH", x, y);
}

int Game::getch()
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(0, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(0, TCSANOW, &oldattr);
    return (ch);
}

int Game::clrscr()
{
    return printf("\E[H\E[J");
}

int Game::setFGColor()
{
    return printf("\E[3%dm", 0);
}

int Game::setBGColor()
{
    return printf("\E[4%dm", 7);
}

void Game::outputPhase(int i)
{
    cout << phase[i];
}

int Game::defcolor()
{
    printf("\E[0m");
    return 0;
}

void Game::outputAlphas()
{
    for (int i = 0; i < 26; i++) {
        cout << alpha[i] << "   ";
        if (i == 12) {
            cout << endl;
        }
    }
}

void Game::outputMenu(int i)
{
    cout << "Hangman!" << endl;
    cout << "_____________________________________" << endl;
    if (i == 0) {
        cout << "* 1. Play" << endl;
    } else {
        cout << "1. Play" << endl;
    }
    if (i == 1) {
        cout << "* 2. Settings" << endl;
    } else {
        cout << "2. Settings" << endl;
    }
    if (i == 2) {
        cout << "* 3. Exit" << endl;
    } else {
        cout << "3. Exit" << endl;
    }
}

void Game::outputWord(const string& word)
{
    for (unsigned int i = 0; i < word.size(); i++) {
        cout << ' ' << word[i] << ' ';
    }
}

bool Game::checkWord(int i, int j)
{
    bool flag = false;
    if (i > 0)
        i--;
    char selectAlpha = alpha[(j - 17) * 13 + i / 4];
    for (unsigned int k = 0; k < word.size(); k++) {
        if (selectAlpha == word[k]) {
            outWord[k] = word[k];
            flag = true;
        }
    }
    if (!flag)
        _phase++;
    return flag;
}

void Game::outputSettings(int i)
{
    cout << "Settings:" << endl;
    if (i == 0) {
        cout << "* 1. Add a new word" << endl;
    } else {
        cout << "1. Add a new word" << endl;
    }
    if (i == 1) {
        cout << "* 2. Add a new words from file" << endl;
    } else {
        cout << "2. Add a new words from file" << endl;
    }
    if (i == 2) {
        cout << "* 3. Back" << endl;
    } else {
        cout << "3. Back" << endl;
    }
}

bool Game::isWin(const string& word)
{
    unsigned long int foundIndex = word.find('_');
    if (foundIndex != string::npos)
        return false;
    return true;
}

void Game::Play()
{
    string theme = getTheme();
    if (theme.empty()) {
        cout << "ERROR!" << endl;
        sleep(1);
        return;
    }
    setWord(theme);
    outputPhase(_phase);
    cout << endl << "      ";
    outputWord(outWord);
    cout << endl << endl;
    outputAlphas();
    int i = 0, j = 17;
    int k = 0;
    gotoXY(i, j);
    setBGColor();
    setFGColor();
    cout << alpha[k];
    getch();
    while (true) {
        if (_phase == phase.size() - 1) {
            sleep(3);
            defcolor();
            return;
        }
        if (isWin(outWord)) {
            defcolor();
            sleep(1);
            clrscr();
            cout << win;
            sleep(3);
            return;
        }
        int c = getch();
        if (c == '\033') {
            getch();
            switch (getch()) {
            case 'B': {
                gotoXY(i, j);
                defcolor();
                cout << alpha[k];
                if (k > 12) {
                    gotoXY(i, --j);
                    k -= 13;
                } else {
                    gotoXY(i, ++j);
                    k += 13;
                }
                setFGColor();
                setBGColor();
                cout << alpha[k];
                break;
            }
            case 'A': {
                gotoXY(i, j);
                defcolor();
                cout << alpha[k];
                if (k < 12) {
                    gotoXY(i, ++j);
                    k += 13;
                } else {
                    gotoXY(i, --j);
                    k -= 13;
                }
                setFGColor();
                setBGColor();
                cout << alpha[k];
                break;
            }
            case 'D': {
                gotoXY(i, j);
                defcolor();
                cout << alpha[k];
                if (k == 0 || k == 13) {
                    gotoXY(i += 49, j);
                    k += 12;
                } else {
                    (i == 5) ? gotoXY(i -= 5, j) : gotoXY(i -= 4, j);
                    k--;
                }
                setFGColor();
                setBGColor();
                cout << alpha[k];
                break;
            }
            case 'C': {
                gotoXY(i, j);
                defcolor();
                cout << alpha[k];
                if (k == 12 || k == 25) {
                    gotoXY(i -= 48, j);
                    k -= 12;
                } else {
                    (i == 0) ? gotoXY(i += 5, j) : gotoXY(i += 4, j);
                    k++;
                }
                setFGColor();
                setBGColor();
                cout << alpha[k];
                break;
            }
            default:
                break;
            }
        } else if (c == 10) {
            checkWord(i, j);
            defcolor();
            clrscr();
            outputPhase(static_cast<int>(_phase));
            cout << endl << "      ";
            outputWord(outWord);
            cout << endl << endl;
            outputAlphas();
            gotoXY(i, j);
            setFGColor();
            setBGColor();
            cout << alpha[k];
        }
    }
}

void Game::Settings()
{
    clrscr();
    int i = 0;
    outputSettings(i % 3);
    getch();
    while (true) {
        int c = getch();
        if (c == '\033') {
            getch();
            switch (getch()) {
            case 'A': {
                clrscr();
                outputSettings(--i % 3);
                break;
            }
            case 'B': {
                clrscr();
                outputSettings(++i % 3);
                break;
            }
            }
        } else if (c == 10) {
            clrscr();
            if (i % 3 == 0) {
                string theme;
                cout << "Enter a topic:";
                cin >> theme;
                themes.addUserWord(theme);
                clrscr();
                getch();
                outputSettings(i = 0);
            }
            if (i % 3 == 1) {
                cout << "Enter file name:";
                string filename;
                getline(cin, filename);
                themes.addFileWords(filename);
                clrscr();
                outputSettings(i = 0);
            }
            if (i % 3 == 2) {
                return;
            }
        }
    }
}

void Game::setWord(const string& theme)
{
    outWord.clear();
    word = themes.getWord(theme);
    outWord.resize(word.size(), '_');
}

string Game::getTheme()
{
    clrscr();
    auto iter = themes.themes.begin();
    cout << "List of topics:" << endl;
    unsigned int k = 1;
    for (const auto& i : themes.themes) {
        cout << k++ << ". " << i.first << endl;
    }
    cout << endl << "Topic number:";
    cin >> k;
    if (k == 0 || k > themes.themes.size()) {
        return "";
    }
    for (unsigned int i = 0; i + 1 != k; i++, iter++) {
        continue;
    }
    clrscr();
    return iter->first;
}

void Game::Menu()
{
    clrscr();
    int i = 0;
    outputMenu(i % 3);
    while (true) {
        int c = getch();
        if (c == '\033') {
            getch();
            switch (getch()) {
            case 'A':
                clrscr();
                outputMenu(--i % 3);
                break;
            case 'B':
                clrscr();
                outputMenu(++i % 3);
                break;
            case 10:
                clrscr();
                if (i % 3 == 0) {
                    Play();
                    clrscr();
                    i = 0;
                    outputMenu(i % 3);
                    _phase = 0;
                    outWord.resize(word.size(), '_');
                }
                if (i % 3 == 1) {
                    Settings();
                }
                if (i % 3 == 2) {
                    return;
                }
            }
        } else if (c == 10) {
            clrscr();
            if (i % 3 == 0) {
                Play();
                clrscr();
                i = 0;
                outputMenu(i % 3);
                _phase = 0;
                outWord.resize(word.size(), '_');
            }
            if (i % 3 == 1) {
                Settings();
            }
            if (i % 3 == 2) {
                return;
            }
        }
    }
}