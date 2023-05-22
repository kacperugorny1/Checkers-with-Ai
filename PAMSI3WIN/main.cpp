#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <vector>
#include "window.h"
#include "Minimax.h"
#include "Gamelogic.h"
#include <Windows.h>


#define white_turn 1
#define black_turn -1


//issues minmax is pretty stupid
// black on minimax is even stupidier
// minimax_ab is even more stupidier xd
// OKAY ALPHA BETA REJECTS THE CASES WHEN THERE IS ONLY ONE LEGAL MOVE, AND IT IS VERY UNLIKELY TO TAKE
// SO THATS THING TO FIX, IF THERE IS ONLY ONE LEGAL MOVE IT SHOULDNT CUT WHEN THE VALUE IS HORRENDOUS




int main()
{
   /*
    int board[8][8] = { 0, -1, 0, -1, 0, -1, 0, -1,
                    -1, 0, -1, 0, -1, 0, -1, 0,
                    0, -1, 0, -1, 0, -1, 0, -1,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    1, 0, 1, 0, 1, 0, 1, 0,
                    0, 1, 0, 1, 0, 1, 0, 1,
                    1, 0, 1, 0, 1, 0, 1, 0 };
                    */
    

 int board[8][8] = { 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 1, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, -1, 0, -1, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 1, 0, 1, 0, -1, 0,
                    0, 0, 0, 1, 0, -1, 0, -1,
                    0, 0, 1, 0, 0, 0, 0, 0 };



    int turn = white_turn;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Warcaby", sf::Style::Default, settings);
    sf::Clock clock;
    int frames = 0;
    int is_moving = 0;
    int num_of_moves = 0;
    sf::Vector2i picked_coords;

    std::list<sf::Vector2i> legal_moves;
    sf::Vector2i previous_cords = { 0,0 };

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

        if (clock.getElapsedTime().asSeconds() > 1) {
            Eval move;
            if (turn > 0)
                move = minimax(board, 4, true, was_capture,previous_cords,-1000000000,1000000000);
            else
                move = minimax(board, 4, false, was_capture,previous_cords, -1000000000, 1000000000);
            std::cout <<std::endl<<move.eval<<" " << move.from.x << "." << move.from.y << " " << move.to.x 
                << "." << move.to.y <<" "<<move.capture << " " << ((turn > 0)?"white":"black") << std::endl;
            make_a_move(board,turn, move.from, move.to, board[move.from.x][move.from.y]);
            was_capture = move.capture;
            previous_cords = move.to;
            if (!move.capture)
                turn = -turn;
            clock.restart();
        }

     
        
        

        //Players vs BOT player is white
       /*
        if (turn < 0) {
            Eval move;
            Sleep(1000);
            move = minimax(board, 3, false, was_capture,previous_cords);
            make_a_move(board,turn, move.from, move.to, board[move.from.x][move.from.y]);
            was_capture = move.capture;
            previous_cords = move.to;
            if (!move.capture)
                turn = -turn;
            clock.restart();
        }
        */
       

        //Players vs BOT player is black
        /*
        if (turn > 0) {
            Eval move;
            Sleep(1000);
            move = minimax(board, 6, true, was_capture, previous_cords);
            make_a_move(board,turn, move.from, move.to, board[move.from.x][move.from.y]);
            was_capture = move.capture;
            previous_cords = move.to;
            if (!move.capture)
                turn = -turn;
            clock.restart();
        }
        */
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            handle_press(board,turn,sf::Mouse::getPosition(window), legal_moves, picked_coords, is_moving);
        }

        
        if (event.type == sf::Event::MouseButtonReleased) {
            handle_release(board,turn,sf::Mouse::getPosition(window), legal_moves, picked_coords, is_moving);
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



