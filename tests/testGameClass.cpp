//
// Created by cool8 on 29.09.2021.
//

#include "gtest/gtest.h"
#include "../src/Game.h"

TEST(GameIsWin, isWin) {
    ASSERT_EQ(Game::isWin("champion"), true);
    ASSERT_EQ(Game::isWin("ch_mpion"), false);
    ASSERT_EQ(Game::isWin("______"), false);
}

TEST(GameCheckWord, checkWord) {
    Game game;
    game.setWord("SPORT");
    ASSERT_EQ(game.checkWord(25, 18), true);
    ASSERT_EQ(game.checkWord(29, 18), false);
}

