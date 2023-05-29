#include "window.h"



void draw_board(sf::RenderWindow& window, int board[8][8], int is_moving, sf::Vector2i mouse_pos, int turn, bool end) {
    sf::RectangleShape rect(sf::Vector2f(75, 75));
    sf::CircleShape piece(30);
    sf::Text text;
    sf::CircleShape inner_piece(20);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(50);
    window.clear(canva_color);
    if (!end) {
        std::string trn = (turn > 0 ? "WHITE" : "BLACK");
        text.setString(trn + " TURN");
        text.setPosition(485, 25);
        window.draw(text);
    }
    else if (end) {
        std::string trn = (turn < 0 ? "WHITE" : "BLACK");
        text.setString(trn + " WON");
        text.setPosition(500, 25);
        window.draw(text);

    }

    text.setCharacterSize(20);
    for (int i = 0; i < 64; ++i) {
        bool black_square = (i + (int)floor(i / 8)) % 2;
        int row = i / 8;
        int column = i % 8;
        if (column == 0) {
            text.setString(std::to_string(row));
            text.setPosition(320, 130 + row * 75);
            
            window.draw(text);
        }
        if (row == 0) {
            text.setString(std::to_string(column));
            text.setPosition(370 + column*75, 75);

            window.draw(text);
        }

        rect.setFillColor((i + row) % 2 == 0 ? white_sq : black_sq);
        rect.setPosition(sf::Vector2f(340 + column * 75, 100 + row * 75));
        window.draw(rect);
        if (board[row][column] == -1) {
            piece.setFillColor(black_piece);
            piece.setPosition(340 + column * 75 + 7.5, 100 + row * 75 + 7.5);
            window.draw(piece);
        }
        if (board[row][column] == -2) {
            piece.setFillColor(black_piece);
            piece.setPosition(340 + column * 75 + 7.5, 100 + row * 75 + 7.5);
            window.draw(piece);
            inner_piece.setFillColor(sf::Color::Red);
            inner_piece.setPosition(340 + column * 75 + 17.5, 100 + row * 75 + 17.5);
            window.draw(inner_piece);
        }
        if (board[row][column] == 2) {
            piece.setFillColor(white_piece);
            piece.setPosition(340 + column * 75 + 7.5, 100 + row * 75 + 7.5);
            window.draw(piece);
            inner_piece.setFillColor(sf::Color::Red);
            inner_piece.setPosition(340 + column * 75 + 17.5, 100 + row * 75 + 17.5);
            window.draw(inner_piece);
        }
        if (board[row][column] == 1) {
            piece.setFillColor(white_piece);
            piece.setPosition(340 + column * 75 + 7.5, 100 + row * 75 + 7.5);
            window.draw(piece);
        }
        if (is_moving > 0) {
            piece.setFillColor(white_piece);
            piece.setPosition(mouse_pos.x - 30, mouse_pos.y - 30);
            window.draw(piece);
            if (is_moving == 2) {
                inner_piece.setFillColor(sf::Color::Red);
                inner_piece.setPosition(mouse_pos.x - 30 + 10, mouse_pos.y - 30 + 10);
                window.draw(inner_piece);
            }
        }
        if (is_moving < 0) {
            piece.setFillColor(black_piece);
            piece.setPosition(mouse_pos.x - 30, mouse_pos.y - 30);
            window.draw(piece);
            if (is_moving == -2) {
                inner_piece.setFillColor(sf::Color::Red);
                inner_piece.setPosition(mouse_pos.x - 30 + 10, mouse_pos.y - 30 + 10);
                window.draw(inner_piece);
            }
        }
        
    }


    window.display();
}