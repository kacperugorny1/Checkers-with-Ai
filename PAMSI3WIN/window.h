#pragma once
#include <SFML/Graphics.hpp>

#define black_sq sf::Color(179, 150, 71)
#define white_sq sf::Color::White
#define canva_color sf::Color(42, 46, 66, 0)
#define black_piece sf::Color::Black
#define white_piece sf::Color(230, 234, 240)




/// <summary>
/// Rysuje klatke 
/// </summary>
/// <param name="window"></param>
/// <param name="board">: plansza</param>
/// <param name="is_moving">: jaki pionek jest pod myszk¹</param>
/// <param name="mouse_pos">: pozycja myszki</param>
/// <param name="turn">: kogo tura</param>
/// <param name="end">: czy koniec gry</param>
void draw_board(sf::RenderWindow& window,int board[8][8], int is_moving, sf::Vector2i mouse_pos, int turn, bool end = false);