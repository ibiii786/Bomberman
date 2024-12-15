// Added comments for better understanding
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class GraphicObject
{
protected:
	sf::Vector2f position;
	sf::FloatRect collisionBox;
	sf::Sprite sprite;

public:
	 sf::Vector2f GetPosition();

	void SetPosition(const sf::Vector2f & position);

	sf::FloatRect GetCollisionBox();

	void LoadTexture(const sf::Texture & texture);

	void Draw(sf::RenderWindow & window);
};