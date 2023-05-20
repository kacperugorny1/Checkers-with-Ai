#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>


void handle_press(int board[8][8],int& turn,sf::Vector2i mouse_Pos, std::list<sf::Vector2i>& available_pos, sf::Vector2i& picked_coords, int& is_moving);
void handle_release(int board[8][8],int& turn, sf::Vector2i mouse_Pos, std::list<sf::Vector2i>& available_pos, sf::Vector2i& picked_coords, int& is_moving);
bool look_for_capture(int board[8][8], int whos_turn);
bool look_for_moves(int board[8][8], int whos_turn);

std::list<sf::Vector2i> make_a_move(int board[8][8], int turn, sf::Vector2i from, sf::Vector2i where, int& is_moving);
std::list<sf::Vector2i> legal_moves(int board[8][8], int turn, sf::Vector2i pos, int is_moving, bool only_captures = false);