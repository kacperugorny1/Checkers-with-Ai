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


/// <summary>
/// Oblicza pozycje na planszy
/// </summary>
/// <param name="board">: plansza</param>
/// <returns>warto�� pozycji</returns>
int evaluation(int board[8][8]);


/// <summary>
/// Minimax bez alfa beta ci��
/// </summary>
/// <param name="board">: plansza</param>
/// <param name="depth">: g��boko�� oblicze�</param>
/// <param name="maximizing_player">: kt�ry gracz</param>
/// <param name="was_a_capture">: Czy to drugi ruch? - musi bi� tym samym pionem</param>
/// <param name="coords">: koordy z kt�rych musi by� ruch je�li by�o bicie wcze�niej</param>
/// <returns>strukture eval kt�ra zawiera warto�� i ruch do wykonania</returns>
Eval minimax(int board[8][8], int depth, bool maximizing_player, bool was_a_capture, sf::Vector2i coords);

/// <summary>
/// Minimax z alfa beta ci�ciami
/// </summary>
/// <param name="board">: plansza</param>
/// <param name="depth">: g��boko�� oblicze�</param>
/// <param name="maximizing_player">: kt�ry gracz</param>
/// <param name="was_a_capture">: Czy to drugi ruch? - musi bi� tym samym pionem</param>
/// <param name="coords">: koordy z kt�rych musi by� ruch je�li by�o bicie wcze�niej</param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <returns>strukture eval kt�ra zawiera warto�� i ruch do wykonania</returns>
Eval minimax(int board[8][8], int depth, bool maximizing_player, bool was_a_capture, sf::Vector2i coords, int alpha, int beta);