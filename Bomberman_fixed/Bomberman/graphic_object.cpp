// Added comments for better understanding
#include <iostream>
#include "graphic_object.hpp"



sf::Vector2f GraphicObject::GetPosition()
{
	return this->position;
}

void GraphicObject::SetPosition(const sf::Vector2f & position)
{
	this->position = position;
}

sf::FloatRect GraphicObject::GetCollisionBox()
{
	return this->collisionBox;
}

void GraphicObject::LoadTexture(const sf::Texture & texture)
{
	sprite.setTexture(texture);
}

void GraphicObject::Draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}
