#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <vector>
#include "window.h"
#include <Windows.h>


#define white_turn 1
#define black_turn -1

void handle_press(sf::Vector2i mouse_Pos, std::list<sf::Vector2i> &available_pos, sf::Vector2i &picked_coords, int &is_moving);
void handle_release(sf::Vector2i mouse_Pos, std::list<sf::Vector2i> &available_pos, sf::Vector2i &picked_coords, int &is_moving);
bool look_for_capture(int board[8][8], int whos_turn);
bool check_for_win(int board,int turn);
bool look_for_moves(int board[8][8],int whos_turn);
std::list<sf::Vector2i> make_a_move(int board[8][8], sf::Vector2i from, sf::Vector2i where, int &is_moving);

std::list<sf::Vector2i> legal_moves(sf::Vector2i pos, int is_moving, bool only_captures = false);
int static_evaluation(int board[8][8]) {
    int sum = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            sum += board[i][j];
    return sum;
}
struct Eval {
    int eval;
    sf::Vector2i from;
    sf::Vector2i to;
    bool capture = false;

    Eval(int evals) { eval = evals; }
    Eval() {}
};

Eval minimax(int board[8][8], int depth, bool maximizing_player, bool was_a_capture) {
    if (depth == 0 || !look_for_moves(board, maximizing_player > 0? 1:-1))
        return static_evaluation(board);
    if (maximizing_player) {
        Eval maxEval(-1000000);
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
            {
                if(board[i][j] > 0)
                    for (sf::Vector2i move : legal_moves({ i,j }, board[i][j], was_a_capture||look_for_capture(board,1))) {
                        int board_cp[8][8];
                        for(int z = 0; z < 8; ++z)
                            std::copy(std::begin(board[z]), std::end(board[z]), std::begin(board_cp[z]));
                        Eval eval;
                        if (make_a_move(board_cp, { i,j }, move, board_cp[i][j]).size() != 0 && std::abs(i - move.x) == 2) {
                            eval = minimax(board_cp, depth - 1, true, true);
                            eval.from = { i,j };
                            eval.to = move;
                            eval.capture = true;
                        }
                        else {
                            eval = minimax(board_cp, depth - 1, false, false);
                            eval.from = { i,j };
                            eval.to = move;
                            eval.capture = false;
                        }
                        maxEval = maxEval.eval > eval.eval? maxEval:eval;
                    }
            }
        return maxEval;
    }
    else {
        Eval minEval(1000000);
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
            {
                if (board[i][j] < 0)
                    for (sf::Vector2i move : legal_moves({ i,j }, board[i][j], was_a_capture||look_for_capture(board,-1))) {
                        int board_cp[8][8];
                        for (int z = 0; z < 8; ++z)
                            std::copy(std::begin(board[z]), std::end(board[z]), std::begin(board_cp[z]));
                        Eval eval;
                        if (make_a_move(board_cp, { i,j }, move, board_cp[i][j]).size() != 0 && std::abs(i - move.x) == 2) {
                            eval = minimax(board_cp, depth - 1, false, true);
                            eval.from = { i,j };
                            eval.to = move;
                            eval.capture = true;
                        }
                        else {
                            eval = minimax(board_cp, depth - 1, true, false);
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



int board[8][8] = {0, -1, 0, -1, 0, -1, 0, -1,
                    -1, 0, -1, 0, -1, 0, -1, 0,
                    0, -1, 0, -1, 0, -1, 0, -1,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    1, 0, 1, 0, 1, 0, 1, 0,
                    0, 1, 0, 1, 0, 1, 0, 1,
                    1, 0, 1, 0, 1, 0, 1, 0 };
         
                    
int turn = white_turn;


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Warcaby", sf::Style::Default, settings);
    sf::Clock clock;
    int frames = 0;
    int is_moving = 0;
    int num_of_moves = 0;
    sf::Vector2i picked_coords;

    std::list<sf::Vector2i> legal_moves;

    bool was_capture = false;

    draw_board(window, board, is_moving, sf::Mouse::getPosition(window), turn);
    while (window.isOpen())
    {
        sf::Event event;

        //if (!look_for_moves(board, turn))
         //   break;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        

        //BOT VS BOT
        /*
        if (clock.getElapsedTime().asSeconds() > 1) {
            Eval move;
            if (turn > 0)
                move = minimax(board, 3, true, was_capture);
            else
                move = minimax(board, 10, false, was_capture);
            std::cout <<move.eval<<" " << move.from.x << "." << move.from.y << " " << move.to.x 
                << "." << move.to.y <<" "<<move.capture << " " << ((turn > 0)?"white":"black") << std::endl;
            make_a_move(board, move.from, move.to, board[move.from.x][move.from.y]);
            was_capture = move.capture;
            if (!move.capture)
                turn = -turn;
            clock.restart();
        }
        */

        //Players vs BOT
        if (turn < 0) {
            Eval move;
            Sleep(1000);
            move = minimax(board, 7, false, was_capture);
            make_a_move(board, move.from, move.to, board[move.from.x][move.from.y]);
            was_capture = move.capture;
            if (!move.capture)
                turn = -turn;
            clock.restart();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            handle_press(sf::Mouse::getPosition(window), legal_moves, picked_coords, is_moving);
        }

        
        if (event.type == sf::Event::MouseButtonReleased) {
            handle_release(sf::Mouse::getPosition(window), legal_moves, picked_coords, is_moving);
        }
        draw_board(window, board, is_moving, sf::Mouse::getPosition(window), turn);
    }
    draw_board(window, board, is_moving, sf::Mouse::getPosition(window), turn, true);
    while (true) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }


    return 0;
}



void handle_press(sf::Vector2i mouse_Pos, std::list<sf::Vector2i> &x, sf::Vector2i &picked_coords, int &is_moving) {
    if (is_moving != 0)
        return;
    if (mouse_Pos.x < 340 || mouse_Pos.x>940 || mouse_Pos.y < 100 || mouse_Pos.y > 700)
        return;
   
    int column = (mouse_Pos.x - 340) / 75;
    int row = (mouse_Pos.y - 100) / 75;
    if (x.empty() && picked_coords.x == row && picked_coords.y == column) {
        is_moving = board[row][column];
        board[row][column] = 0;
        return;
    }
    if (!(turn < 0 && board[row][column] < 0) && !(turn > 0 && board[row][column] > 0))
        return;
    is_moving = board[row][column];
    picked_coords.x = row;
    picked_coords.y = column;
    board[row][column] = 0;
    x = legal_moves(picked_coords, is_moving,look_for_capture(board,turn));

}



void handle_release(sf::Vector2i mouse_Pos, std::list<sf::Vector2i> &x, sf::Vector2i &picked_coords, int &is_moving) {
    if (is_moving == 0)
        return;
    if (mouse_Pos.x < 340 || mouse_Pos.x > 940 || mouse_Pos.y < 100 || mouse_Pos.y > 700) {
        board[picked_coords.x][picked_coords.y] = is_moving;
        is_moving = 0;
        picked_coords = { -1,-1 };
        return;
    }
    
    sf::Vector2i indexes = { (mouse_Pos.y - 100) / 75 , (mouse_Pos.x - 340) / 75 };

    for(sf::Vector2i coord : x) {
        if (coord != indexes)
            continue;
        x = make_a_move(board, picked_coords, coord, is_moving);
        if (x.size() != 0)
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

std::list<sf::Vector2i> make_a_move(int board[8][8], sf::Vector2i from, sf::Vector2i where, int &is_moving) {
    board[where.x][where.y] = is_moving;
    std::list<sf::Vector2i> legal_mv;
    if (where.x == 0 && is_moving == 1)
        board[where.x][where.y] = 2;
    if (where.x == 7 && is_moving == -1)
        board[where.x][where.y] = -2;
    if (std::abs(where.x - from.x) == 2) {
        board[from.x + (where.x - from.x) / 2][from.y + (where.y - from.y) / 2] = 0;
        legal_mv = legal_moves({ where.x,where.y }, is_moving, true);
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
            if (board[i][j] != whos_turn && board[i][j] != whos_turn*2)
                continue;
            if (!legal_moves({ i,j }, board[i][j], true).empty())
                return true;
        }
    return false;
}

bool look_for_moves(int board[8][8], int whos_turn) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != whos_turn && board[i][j] != whos_turn * 2)
                continue;
            if (!legal_moves({ i,j }, board[i][j], false).empty())
                return true;
        }
    return false;
}






std::list<sf::Vector2i> legal_moves(sf::Vector2i pos, int is_moving, bool only_captures) {
    std::list<sf::Vector2i> positions;

    //both logic
    if (pos.y - 1 >= 0 &&  pos.x + (-1) * turn >= 0 && pos.x + (-1) * turn <= 7 && board[pos.x + (-1) * turn][pos.y - 1] == 0 && !only_captures)
        positions.push_back({ pos.x + (-1) * turn, pos.y - 1 });
    else if (pos.x + (-2) * turn >= 0 && pos.x + (-2) * turn <= 7 && pos.y - 2 >= 0 &&
        (board[pos.x + (-1) * turn][pos.y - 1] == -turn || board[pos.x + (-1) * turn][pos.y - 1] == -turn * 2)
        && board[pos.x + (-2) * turn][pos.y - 2] == 0) {
        if (only_captures == false)
            return legal_moves(pos, is_moving, true);
        positions.push_back({ pos.x + (-2) * turn, pos.y - 2 });
    }
        

    if  (pos.y + 1 <= 7 && pos.x + (-1) * turn >= 0 && pos.x + (-1) * turn <= 7 && board[pos.x + (-1) * turn][pos.y + 1] == 0 && !only_captures)
            positions.push_back({ pos.x + (-1) * turn, pos.y + 1 });
    else if ( pos.x + (-2) * turn >= 0 && pos.x + (-2) * turn <= 7 && pos.y + 2 <= 7 &&
        (board[pos.x + (-1) * turn][pos.y + 1] == -turn || board[pos.x + (-1) * turn][pos.y + 1] == -turn * 2)
        && board[pos.x + (-2) * turn][pos.y + 2] == 0) {
        if (only_captures == false)
            return legal_moves(pos, is_moving, true);
        positions.push_back({ pos.x + (-2) * turn, pos.y + 2 }); 
    }

    if (!(is_moving == 2 || is_moving == -2)) {
        for (auto x : positions) {
            std::cout << x.x << " " << x.y << std::endl;
        }
        return positions;

    }
        
    // king section
    if (pos.y - 1 >= 0 && pos.x + turn >= 0 && pos.x + turn <= 7 && board[pos.x + turn][pos.y - 1] == 0  && !only_captures)
        positions.push_back({ pos.x + turn, pos.y - 1 });
    else if(pos.x + 2 * turn >= 0 && pos.x + 2 * turn <= 7 && pos.y - 2 >= 0 &&
        (board[pos.x + turn][pos.y - 1] == -turn || board[pos.x + turn][pos.y - 1] == -turn*2)
        && board[pos.x + 2 * turn][pos.y - 2] == 0){
        if (only_captures == false)
            return legal_moves(pos, is_moving, true);
        positions.push_back({ pos.x + 2 * turn, pos.y - 2 });
    }

    if (pos.y + 1 <= 7 && pos.x + turn >= 0 && pos.x + turn <= 7 && board[pos.x + turn][pos.y + 1] == 0 && !only_captures)
            positions.push_back({ pos.x + turn, pos.y + 1 });
    else if (pos.x + 2 * turn >= 0 && pos.x + 2 * turn <= 7 && pos.y + 2 <= 7 &&
        (board[pos.x + turn][pos.y + 1] == -turn || board[pos.x + turn][pos.y + 1] == -turn * 2)
        && board[pos.x + turn][pos.y + 2] == 0) {
        if (only_captures == false)
            return legal_moves(pos, is_moving, true);
        positions.push_back({ pos.x + 2 * turn, pos.y + 2 });
    }

    for (auto x : positions) {
        std::cout << x.x << " " << x.y << std::endl;
    }

    return positions;
}
