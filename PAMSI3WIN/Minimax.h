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
/// <returns>wartoœæ pozycji</returns>
int evaluation(int board[8][8]);


/// <summary>
/// Minimax bez alfa beta ciêæ
/// </summary>
/// <param name="board">: plansza</param>
/// <param name="depth">: g³êbokoœæ obliczeñ</param>
/// <param name="maximizing_player">: który gracz</param>
/// <param name="was_a_capture">: Czy to drugi ruch? - musi biæ tym samym pionem</param>
/// <param name="coords">: koordy z których musi byæ ruch jeœli by³o bicie wczeœniej</param>
/// <returns>strukture eval która zawiera wartoœæ i ruch do wykonania</returns>
Eval minimax(int board[8][8], int depth, bool maximizing_player, bool was_a_capture, sf::Vector2i coords);

/// <summary>
/// Minimax z alfa beta ciêciami
/// </summary>
/// <param name="board">: plansza</param>
/// <param name="depth">: g³êbokoœæ obliczeñ</param>
/// <param name="maximizing_player">: który gracz</param>
/// <param name="was_a_capture">: Czy to drugi ruch? - musi biæ tym samym pionem</param>
/// <param name="coords">: koordy z których musi byæ ruch jeœli by³o bicie wczeœniej</param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <returns>strukture eval która zawiera wartoœæ i ruch do wykonania</returns>
Eval minimax(int board[8][8], int depth, bool maximizing_player, bool was_a_capture, sf::Vector2i coords, int alpha, int beta);