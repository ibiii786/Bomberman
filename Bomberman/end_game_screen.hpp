// Added comments for better understanding
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


class EndGameScreen
{
	sf::Text mainText;									
	sf::Text subText1;									
	sf::Text subText2;									

public:

	void Draw(sf::RenderWindow & window);

	void DisplayPlayer1Win(bool player1win);

	void LoadFont(const sf::Font & font);
};