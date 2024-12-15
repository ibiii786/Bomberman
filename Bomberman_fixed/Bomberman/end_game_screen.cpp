// Added comments for better understanding
#include <iostream>
#include <SFML/Graphics.hpp>

#include "end_game_screen.hpp"

void EndGameScreen::Draw(sf::RenderWindow& window) {
    window.draw(mainText);
    window.draw(subText1);
    window.draw(subText2);
}

void EndGameScreen::DisplayPlayer1Win(bool player1win) {
    mainText.setPosition(290, 200);
    mainText.setCharacterSize(50);

    subText1.setPosition(290, 300);
    subText1.setCharacterSize(25);

    subText2.setPosition(290, 350);
    subText2.setCharacterSize(25);

    if (player1win)
        mainText.setString("Player 1 wins!");
    else
        mainText.setString("Player 2 wins!");

    subText1.setString("Press R to play again");
    subText2.setString("Press ESC to exit");

    // Set the text color to purple (RGB: 128, 0, 128)
    mainText.setFillColor(sf::Color(98, 209, 202));
    subText1.setFillColor(sf::Color(98, 209, 202));
    subText2.setFillColor(sf::Color(98, 209, 202));
}

void EndGameScreen::LoadFont(const sf::Font& font) {
    mainText.setFont(font);
    subText1.setFont(font);
    subText2.setFont(font);
}
