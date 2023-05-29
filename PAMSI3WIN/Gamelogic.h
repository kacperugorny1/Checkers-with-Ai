#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

/// <summary>
/// handle_press sprawdza czy ppm wciœniêty znajduje siê na planszy i na odpowiednim pionku, jeœli tak to "podnosi pionka"
/// </summary>
/// <param name="board">: Plansza</param>
/// <param name="turn">: Kogo kolej</param>
/// <param name="mouse_Pos">: Pozycja myszy</param>
/// <param name="available_pos">: dostêpne pozycje</param>
/// <param name="picked_coords"></param>
/// <param name="is_moving"></param>
void handle_press(int board[8][8],int& turn,sf::Vector2i mouse_Pos, std::list<sf::Vector2i>& available_pos, sf::Vector2i& picked_coords, int& is_moving);

/// <summary>
/// puszczenie pionka - jeœli jest podniesiony pionek to do k³adzie
/// </summary>
/// <param name="board">: plansza</param>
/// <param name="turn">: tura</param>
/// <param name="mouse_Pos">: Pozycja myszy</param>
/// <param name="available_pos">: dostepne pozycje</param>
/// <param name="picked_coords">: sk¹d podniesiony</param>
/// <param name="is_moving">: typ pionka</param>
void handle_release(int board[8][8],int& turn, sf::Vector2i mouse_Pos, std::list<sf::Vector2i>& available_pos, sf::Vector2i& picked_coords, int& is_moving);

/// <summary>
/// Szuka bicia na planszy dla danego gracza
/// </summary>
/// <param name="board">: plansza</param>
/// <param name="whos_turn">: kogo tura</param>
/// <returns>true - jeœli jest bicie</returns>
bool look_for_capture(int board[8][8], int whos_turn);


/// <summary>
/// Sprwadza czy jest jakikolwiek ruch mo¿liwy na planszy dla danego gracza
/// </summary>
/// <param name="board">: plansza</param>
/// <param name="whos_turn">: tura</param>
/// <returns>true - jest ruch dostepny</returns>
bool look_for_moves(int board[8][8], int whos_turn);

/// <summary>
/// Wykonaj ruch - przestaw pionka
/// </summary>
/// <param name="board">: Plansza</param>
/// <param name="turn">: Kogo tura</param>
/// <param name="from">: Koordynaty sk¹d podniesiony</param>
/// <param name="where">: Koordynaty gdzie k³adziony</param>
/// <param name="is_moving">: Typ pionka</param>
/// <returns> Liste ruchów jeœli mo¿liwe podwójne bicie - kiedy nie lista pusta</returns>
std::list<sf::Vector2i> make_a_move(int board[8][8], int turn, sf::Vector2i from, sf::Vector2i where, int& is_moving);


/// <summary>
/// Legalne ruchy dla danej pozycji 
/// </summary>
/// <param name="board">: plansza</param>
/// <param name="turn">: Kogo tura</param>
/// <param name="pos">: Pozycja pionka</param>
/// <param name="is_moving">: typ pionka</param>
/// <param name="only_captures">: Czy tylko bicia</param>
/// <returns>Liste ruchów dostêpnych dla danej pozycji</returns>
std::list<sf::Vector2i> legal_moves(int board[8][8], int turn, sf::Vector2i pos, int is_moving, bool only_captures = false);