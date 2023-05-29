#include "Gamelogic.h"



void handle_press(int board[8][8],int& turn, sf::Vector2i mouse_Pos, std::list<sf::Vector2i>& available_pos, sf::Vector2i& picked_coords, int& is_moving) {
    if (is_moving != 0)
        return;
    if (mouse_Pos.x < 340 || mouse_Pos.x>940 || mouse_Pos.y < 100 || mouse_Pos.y > 700)
        return;

    int column = (mouse_Pos.x - 340) / 75;
    int row = (mouse_Pos.y - 100) / 75;
    if (available_pos.empty() && picked_coords.x == row && picked_coords.y == column) { // chyba ten if jest do wywalenia - nie przeszkadza ale nic nie robi, dla pewnosci narazie zostaje
        is_moving = board[row][column];
        board[row][column] = 0;
        return;
    }
    if (!(turn < 0 && board[row][column] < 0) && !(turn > 0 && board[row][column] > 0)) // zlapanie nie tego piona w nie swojej turze
        return;
    is_moving = board[row][column];
    picked_coords.x = row;
    picked_coords.y = column;
    available_pos = legal_moves(board, turn, picked_coords, is_moving, look_for_capture(board, turn));
    board[row][column] = 0;

}




void handle_release(int board[8][8], int& turn, sf::Vector2i mouse_Pos, std::list<sf::Vector2i>& available_pos, sf::Vector2i& picked_coords, int& is_moving) {
    if (is_moving == 0)
        return;
    if (mouse_Pos.x < 340 || mouse_Pos.x > 940 || mouse_Pos.y < 100 || mouse_Pos.y > 700) {
        board[picked_coords.x][picked_coords.y] = is_moving;
        is_moving = 0;
        picked_coords = { -1,-1 };
        return;
    }

    sf::Vector2i indexes = { (mouse_Pos.y - 100) / 75 , (mouse_Pos.x - 340) / 75 };

    for (sf::Vector2i coord : available_pos) {
        if (coord != indexes)
            continue;
        available_pos = make_a_move(board,turn, picked_coords, coord, is_moving);
        if (available_pos.size() != 0)
            return;

        is_moving = 0;
        picked_coords = { -1,-1 };
        turn = -turn;
        return;
    }
    board[picked_coords.x][picked_coords.y] = is_moving;
    is_moving = 0;
    picked_coords = { -1,-1 };

}



std::list<sf::Vector2i> make_a_move(int board[8][8],int turn, sf::Vector2i from, sf::Vector2i where, int& is_moving) {
    board[where.x][where.y] = is_moving;
    std::list<sf::Vector2i> legal_mv;
    if (is_moving == 0)
        return legal_mv;
    // jeœli dojdzie na koniec planszy zmiana na króla
    if (where.x == 0 && is_moving == 1)
        board[where.x][where.y] = 2;
    if (where.x == 7 && is_moving == -1)
        board[where.x][where.y] = -2;

    // jeœli ruch wykonany o 2 pola to zbij pionka i sprawdŸ czy jest mo¿liwoœæ kolejnego bicia
    if (std::abs(where.x - from.x) == 2) {
        board[from.x + (where.x - from.x) / 2][from.y + (where.y - from.y) / 2] = 0;
        legal_mv = legal_moves(board, turn, { where.x,where.y }, board[where.x][where.y], true);
        is_moving = 0;
        board[from.x][from.y] = 0;
        from = { where.x ,where.y };
    }
    else
        board[from.x][from.y] = 0;

    return legal_mv;
}


bool look_for_capture(int board[8][8], int whos_turn) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != whos_turn && board[i][j] != whos_turn * 2)
                continue;
            if (!legal_moves(board, whos_turn, { i,j }, board[i][j], true).empty())
                return true;
        }
    return false;
}


bool look_for_moves(int board[8][8], int whos_turn) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != whos_turn && board[i][j] != whos_turn * 2)
                continue;
            if (!legal_moves(board,whos_turn, { i,j }, board[i][j], false).empty())
                return true;
        }
    return false;
}


std::list<sf::Vector2i> legal_moves(int board[8][8], int turn, sf::Vector2i pos, int is_moving, bool only_captures) {
    std::list<sf::Vector2i> positions;

    //both logic
    if (pos.y - 1 >= 0 && pos.x + (-1) * turn >= 0 && pos.x + (-1) * turn <= 7 && board[pos.x + (-1) * turn][pos.y - 1] == 0 && !only_captures)
        positions.push_back({ pos.x + (-1) * turn, pos.y - 1 });
    else if (pos.x + (-2) * turn >= 0 && pos.x + (-2) * turn <= 7 && pos.y - 2 >= 0 &&
        (board[pos.x + (-1) * turn][pos.y - 1] == -turn || board[pos.x + (-1) * turn][pos.y - 1] == -turn * 2)
        && board[pos.x + (-2) * turn][pos.y - 2] == 0) {
        if (only_captures == false)
            return legal_moves(board, turn, pos, is_moving, true);
        positions.push_back({ pos.x + (-2) * turn, pos.y - 2 });
    }


    if (pos.y + 1 <= 7 && pos.x + (-1) * turn >= 0 && pos.x + (-1) * turn <= 7 && board[pos.x + (-1) * turn][pos.y + 1] == 0 && !only_captures)
        positions.push_back({ pos.x + (-1) * turn, pos.y + 1 });
    else if (pos.x + (-2) * turn >= 0 && pos.x + (-2) * turn <= 7 && pos.y + 2 <= 7 &&
        (board[pos.x + (-1) * turn][pos.y + 1] == -turn || board[pos.x + (-1) * turn][pos.y + 1] == -turn * 2)
        && board[pos.x + (-2) * turn][pos.y + 2] == 0) {
        if (only_captures == false)
            return legal_moves(board,turn, pos, is_moving, true);
        positions.push_back({ pos.x + (-2) * turn, pos.y + 2 });
    }

    if (!(is_moving == 2 || is_moving == -2)) {
        return positions;

    }

    // king section
    if (pos.y - 1 >= 0 && pos.x + turn >= 0 && pos.x + turn <= 7 && board[pos.x + turn][pos.y - 1] == 0 && !only_captures)
        positions.push_back({ pos.x + turn, pos.y - 1 });
    else if (pos.x + 2 * turn >= 0 && pos.x + 2 * turn <= 7 && pos.y - 2 >= 0 &&
        (board[pos.x + turn][pos.y - 1] == -turn || board[pos.x + turn][pos.y - 1] == -turn * 2)
        && board[pos.x + 2 * turn][pos.y - 2] == 0) {
        if (only_captures == false)
            return legal_moves(board,turn, pos, is_moving, true);
        positions.push_back({ pos.x + 2 * turn, pos.y - 2 });
    }

    if (pos.y + 1 <= 7 && pos.x + turn >= 0 && pos.x + turn <= 7 && board[pos.x + turn][pos.y + 1] == 0 && !only_captures)
        positions.push_back({ pos.x + turn, pos.y + 1 });
    else if (pos.x + 2 * turn >= 0 && pos.x + 2 * turn <= 7 && pos.y + 2 <= 7 &&
        (board[pos.x + turn][pos.y + 1] == -turn || board[pos.x + turn][pos.y + 1] == -turn * 2)
        && board[pos.x + 2 * turn][pos.y + 2] == 0) {
        if (only_captures == false)
            return legal_moves(board,turn, pos, is_moving, true);
        positions.push_back({ pos.x + 2 * turn, pos.y + 2 });
    }


    return positions;
}
