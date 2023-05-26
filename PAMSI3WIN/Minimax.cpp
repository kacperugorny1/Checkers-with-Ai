#include "Minimax.h"


int evaluation(int board[8][8]) {
    int sum = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] == 2 || board[i][j] == -2) {
                sum += board[i][j] * 5;
                continue;
            }
            if (board[i][j] > 0) {
                if (i <= 3)
                    sum += board[i][j] * 7;
                else if(i == 7 || i == 0)
                    sum += board[i][j] * 6;
                else
                    sum += board[i][j] * 5;
            }
            else if (board[i][j] < 0) {
                if (i >= 4)
                    sum += board[i][j] * 7;
                else if (i == 7 || i == 0)
                    sum += board[i][j] * 6;
                else
                    sum += board[i][j] * 5;
            }

        }
    if (!look_for_moves(board, 1))
        return -999999;
    else if (!look_for_moves(board, -1))
        return 999999;
    return sum;
}



Eval minimax(int board[8][8], int depth, bool maximizing_player, bool was_a_capture, sf::Vector2i coords) {
    if (depth == 0 ){
        return evaluation(board);
    }
    if (maximizing_player) {
        Eval maxEval(-1000000);
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
            {
                if (board[i][j] <= 0)
                    continue;
                for (sf::Vector2i move : legal_moves(board, 1, { i,j }, board[i][j], was_a_capture || look_for_capture(board, 1))) {
                    if (coords.x != i && coords.y != -1 && was_a_capture)
                        continue;
                    int board_cp[8][8];
                    for (int z = 0; z < 8; ++z)
                        std::copy(std::begin(board[z]), std::end(board[z]), std::begin(board_cp[z]));
                    Eval eval;
                    if (make_a_move(board_cp, 1, { i,j }, move, board_cp[i][j]).size() != 0) {
                        eval = minimax(board_cp, depth - 1, true, true, move);
                        eval.from = { i,j };
                        eval.to = move;
                        eval.capture = true;
                    }
                    else {
                        eval = minimax(board_cp, depth - 1, false, false, move);
                        eval.from = { i,j };
                        eval.to = move;
                        eval.capture = false;
                    }
                    maxEval = maxEval.eval > eval.eval ? maxEval : eval;
                }
            }
        return maxEval;
    }
    else {
        Eval minEval(1000000);
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
            {
                if (board[i][j] >= 0)
                    continue;
                for (sf::Vector2i move : legal_moves(board,-1, { i,j }, board[i][j], was_a_capture || look_for_capture(board, -1))) {
                    if (coords.x != i && coords.y != -1 && was_a_capture)
                        continue;
                    int board_cp[8][8];
                    for (int z = 0; z < 8; ++z)
                        std::copy(std::begin(board[z]), std::end(board[z]), std::begin(board_cp[z]));
                    Eval eval;
                    if (make_a_move(board_cp,-1, { i,j }, move, board_cp[i][j]).size() != 0) {
                        eval = minimax(board_cp, depth - 1, false, true, move);
                        eval.from = { i,j };
                        eval.to = move;
                        eval.capture = true;
                    }
                    else {
                        eval = minimax(board_cp, depth - 1, true, false, move);
                        eval.from = { i,j };
                        eval.to = move;
                        eval.capture = false;
                    }
                    minEval = minEval.eval < eval.eval ? minEval : eval;
                }
            }
        return minEval;
    }
}


Eval minimax(int board[8][8], int depth, bool maximizing_player, bool was_a_capture, sf::Vector2i coords, int alpha, int beta) {
    if (depth == 0 || !look_for_moves(board, maximizing_player == true ? 1 : -1)) {
        return evaluation(board);
    }
    if (maximizing_player) {
        Eval maxEval(-1000000);
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
            {
                if (board[i][j] <= 0)
                    continue;

                if ((coords.x != i || coords.y != j) && was_a_capture)
                    continue;
                auto moves = legal_moves(board, 1, { i,j }, board[i][j], was_a_capture || look_for_capture(board, 1));
                for (sf::Vector2i move :moves) {
                    int board_cp[8][8];
                    for (int z = 0; z < 8; ++z)
                        std::copy(std::begin(board[z]), std::end(board[z]), std::begin(board_cp[z]));
                    Eval eval;
                    if (make_a_move(board_cp, 1, { i,j }, move, board_cp[i][j]).size() != 0) {
                        eval = minimax(board_cp, depth, true, true, move, alpha, beta);
                        eval.capture = true;
                    }
                    else {
                        eval = minimax(board_cp, depth - 1, false, false, move, alpha, beta);
                        eval.capture = false;
                    }
                    eval.from = { i,j };
                    eval.to = move;
                    maxEval = maxEval.eval > eval.eval ? maxEval : eval;
                    alpha = alpha > eval.eval ? alpha : eval.eval;
                    if (beta <= alpha && moves.size() > 1) {
                        return maxEval;
                    }
                }
            }
        return maxEval;
    }
    else {
        Eval minEval(1000000);
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
            {
                if (board[i][j] >= 0)
                    continue;
                auto moves = legal_moves(board, -1, { i,j }, board[i][j], was_a_capture || look_for_capture(board, -1));

                if ((coords.x != i || coords.y != j) && was_a_capture)
                    continue;
                for (sf::Vector2i move : moves) {
                    int board_cp[8][8];
                    for (int z = 0; z < 8; ++z)
                        std::copy(std::begin(board[z]), std::end(board[z]), std::begin(board_cp[z]));
                    Eval eval;
                    if (make_a_move(board_cp, -1, { i,j }, move, board_cp[i][j]).size() != 0) {
                        eval = minimax(board_cp, depth, false, true, move, alpha, beta);
                        eval.capture = true;
                    }
                    else {
                        eval = minimax(board_cp, depth - 1, true, false, move, alpha, beta);
                        eval.capture = false;
                    }
                    eval.from = { i,j };
                    eval.to = move;
                    minEval = minEval.eval < eval.eval ? minEval : eval;
                    beta = beta < eval.eval ? beta : eval.eval;
                    if (beta <= alpha && moves.size() > 1) {
                        return minEval;
                    }
                }
            }
        return minEval;
    }
}