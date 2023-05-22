#pragma once
#include <SFML/Graphics.hpp>
#include "Gamelogic.h"

struct Eval {
    int eval;
    sf::Vector2i from;
    sf::Vector2i to;
    bool capture = false;

    Eval(int evals) { eval = evals; }
    Eval() {}
};

int static_evaluation(int board[8][8]);
Eval minimax(int board[8][8], int depth, bool maximizing_player, bool was_a_capture, sf::Vector2i coords);
Eval minimax(int board[8][8], int depth, bool maximizing_player, bool was_a_capture, sf::Vector2i coords, int alpha, int beta);