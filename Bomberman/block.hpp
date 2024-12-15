// Added comments for better understanding
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "graphic_object.hpp"
#include "enum.hpp"

class Block : public GraphicObject
{
public:
	int type;											
	bool destroyed = false;								
	bool exploded = false;								

	virtual void Update(const sf::Time deltaTime);

	virtual void SetUp() = 0;

	void Explode() { exploded = true; };

	void Destroy() { destroyed = true; };

	bool IsDestroyed() { return destroyed; };

	bool IsExploded() { return exploded; };
};