// Added comments for better understanding
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "block.hpp"

class Map
{
	unsigned int gameMap[11][15];						

public:
	int tileSize;										
	Block * blocks[11][15];								

	Map();			

	~Map();

	void LoadTiles();

	void Update(const sf::Time deltaTime);

	void Draw(sf::RenderWindow & window);

	void LoadFromFile();
};


