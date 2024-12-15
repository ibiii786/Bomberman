// Added comments for better understanding
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "graphic_object.hpp"
#include "enum.hpp"
#include "bomb.hpp"
#include "map.hpp"

class Player : public GraphicObject
{
	sf::Vector2f velocity;										
	sf::Vector2f defaultVelocity;								
	States playerState;											
	std::string name;											
	bool canGoUp, canGoDown, canGoLeft, canGoRight;				
	float timeSinceBomb, bombCooldown;							

public:
	sf::Texture texture_p1, texture_p2;							
	int bombPlaced;												
	bool killed = false;										
	
	Player(std::string name);

	void MoveWSAD(const sf::Time & deltaTime, Map & map);

	void MoveArrows(const sf::Time & deltaTime, Map & map);

	void GoUp(const sf::Time & deltaTime, Map & map);

	void GoDown(const sf::Time & deltaTime, Map & map);

	void GoLeft(const sf::Time & deltaTime, Map & map);

	void GoRight(const sf::Time & deltaTime, Map & map);

	void ForbidGoingLeft() { canGoLeft = false; };

	void ForbidGoingRight() { canGoRight = false; };

	void ForbidGoingDown() { canGoDown = false; };

	void ForbidGoingUp() { canGoUp = false; };

	void AllowGoingLeft() { canGoLeft = true; };

	void AllowGoingRight() { canGoRight = true; };

	void AllowGoingDown() { canGoDown = true; };

	void AllowGoingUp() { canGoUp = true; };

	void Update(const sf::Time deltaTime);

	void UpdateSprite();

	void UpdateCollisionBox();

	void CheckForCollisions(const sf::Time & deltaTime, Map & map);

	bool IsKilled() { return killed; };

	void Kill() { killed = true; };
	
	void SaveToFile(bool param);
};