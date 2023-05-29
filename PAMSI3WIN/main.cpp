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



int main()
{
    // reprezentacja planszy
    int board[8][8] = {0, -1, 0, -1, 0, -1, 0, -1,
                    -1, 0, -1, 0, -1, 0, -1, 0,
                    0, -1, 0, -1, 0, -1, 0, -1,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    1, 0, 1, 0, 1, 0, 1, 0,
                    0, 1, 0, 1, 0, 1, 0, 1,
                    1, 0, 1, 0, 1, 0, 1, 0 };
                
                     

    int turn = white_turn;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    //Otwarcie okna
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Warcaby", sf::Style::Default, settings);
    sf::Clock clock;
    int is_moving = 0;
    int num_of_moves = 0;
    int depth = 8;
    int depth_1 = 8;
    int gamemode = 0;
    sf::Vector2i picked_coords;
    std::list<sf::Vector2i> legal_moves;
    sf::Vector2i previous_cords = { 0,0 };

    bool was_capture = false;

    draw_board(window, board, is_moving, sf::Mouse::getPosition(window), turn);


    //Wybór trybu gry
    std::cout << "Wybierz tryb gry, 1 - bot vs bot, 2 - gracz czarny, 3 - gracz bialy, ka¿da inna - gracz vs gracz\n";
    std::cin >> gamemode;
    if (gamemode == 2 || gamemode == 3) {
        std::cout << "Podaj glebie bota\n";
        std::cin >> depth;
    }
    else if (gamemode == 1) {
        std::cout << "Podaj glebie bota bialego\n";
        std::cin >> depth;
        std::cout << "Podaj glebie bota czarnego\n";
        std::cin >> depth_1;
    }



    //G³ówna pêtla
    while (window.isOpen())
    {
        sf::Event event;
        //Sprawdz czy koniec gry
        if (!look_for_moves(board, turn) && is_moving == 0)
           break;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        //BOT vs BOT
        if (gamemode == 1 && clock.getElapsedTime().asSeconds() > 1) {
            Eval move;
            if (turn > 0)
                move = minimax(board, depth, true, was_capture, previous_cords, -1000000000, 1000000000);
            else
                move = minimax(board, depth_1, false, was_capture,previous_cords, -1000000000, 1000000000);
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
        
        if (turn < 0 && gamemode == 3) {
            Eval move;
            Sleep(1000);
            move = minimax(board, depth, false, was_capture, previous_cords, -1000000000, 1000000000);
            if (move.to.x == 0 && move.to.y == 0)
                std::cout << "skip";

            make_a_move(board,turn, move.from, move.to, board[move.from.x][move.from.y]);
            was_capture = move.capture;
            previous_cords = move.to;
            std::cout << evaluation(board)<< " " << move.eval << " " << move.from.x << "." << move.from.y << " " << move.to.x
                << "." << move.to.y << " " << move.capture << " " << ((turn > 0) ? "white" : "black") << std::endl;
            if (!move.capture)
                turn = -turn;
            clock.restart();
            
        }
        
       

        //Players vs BOT player is black
        
        if (turn > 0 && gamemode == 2) {
            Eval move;
            Sleep(1000);
            move = minimax(board, depth, true, was_capture, previous_cords, -1000000000, 1000000000);
            make_a_move(board,turn, move.from, move.to, board[move.from.x][move.from.y]);
            was_capture = move.capture;
            previous_cords = move.to;
            std::cout << evaluation(board) << " " << move.eval << " " << move.from.x << "." << move.from.y << " " << move.to.x
                << "." << move.to.y << " " << move.capture << " " << ((turn > 0) ? "white" : "black") << std::endl;
            if (!move.capture)
                turn = -turn;
            clock.restart();
        }
        

        //Wciœniêcie lewego przycisku myszy
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            handle_press(board,turn,sf::Mouse::getPosition(window), legal_moves, picked_coords, is_moving);
        }

        //Wciœniêcie prawego przycisku myszy
        if (event.type == sf::Event::MouseButtonReleased) {
            handle_release(board,turn,sf::Mouse::getPosition(window), legal_moves, picked_coords, is_moving);
        }

        //Rysuj klatkê
        draw_board(window, board, is_moving, sf::Mouse::getPosition(window), turn);
    }

    //Rysuj klatkê ostatni¹ - po wygranej jednej ze stron
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



