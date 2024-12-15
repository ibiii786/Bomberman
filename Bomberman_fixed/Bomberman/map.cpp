// Added comments for better understanding
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time() to seed the random number generator
#include "map.hpp"
#include "solid_wall.hpp"
#include "breakable_wall.hpp"
#include "background.hpp"
#include "bomb.hpp"
#include "explosion.hpp"

Map::Map() : tileSize(64) {};

Map::~Map()
{
	for (int w = 0; w < 11; w++)
	{
		for (int k = 0; k < 15; k++)
		{
			delete blocks[w][k];
			blocks[w][k] = nullptr;
		}
	}
}

void Map::LoadTiles()
{
	// Seed the random number generator with the current time to get different results each time
	srand(static_cast<unsigned>(time(0)));

	// Player 1 and Player 2 starting positions in terms of grid coordinates
	int p1_x = 96 / tileSize;  // Convert from pixel to grid coordinates
	int p1_y = 96 / tileSize;
	int p2_x = 864 / tileSize;
	int p2_y = 604 / tileSize;

	// Mark areas to be kept empty around the players
	for (int w = 0; w < 11; w++)
	{
		for (int k = 0; k < 15; k++)
		{
			// For Player 1: Keep 4 blocks to the right and 4 blocks down empty
			if (w >= p1_y && w <= p1_y  && k >= p1_x && k <= p1_x + 2) {
				Block* background = new Background{};
				blocks[w][k] = background;
				blocks[w][k]->SetPosition(sf::Vector2f(k * tileSize, w * tileSize));
				blocks[w][k]->SetUp();
				blocks[w][k]->type = backgroundBlock;
				continue;
			}

			// For Player 2: Keep 4 blocks to the left and 4 blocks up empty
			if (w >= p2_y  && w <= p2_y && k >= p2_x - 2 && k <= p2_x) {
				Block* background = new Background{};
				blocks[w][k] = background;
				blocks[w][k]->SetPosition(sf::Vector2f(k * tileSize, w * tileSize));
				blocks[w][k]->SetUp();
				blocks[w][k]->type = backgroundBlock;
				continue;
			}

			// First, check if the position is a blank space (background, i.e., gameMap[w][k] == 0)
			if (gameMap[w][k] == 0)
			{
				// Randomly decide whether to place a breakable block here
				if (rand() % 5 == 0)  // 1 in 5 chance for a breakable block to appear
				{
					Block* breakable = new BreakableWall{};
					blocks[w][k] = breakable;
					blocks[w][k]->SetPosition(sf::Vector2f(k * tileSize, w * tileSize));
					blocks[w][k]->SetUp();
					blocks[w][k]->type = breakableBlock;
				}
				else
				{
					// Otherwise, keep it as a background block
					Block* background = new Background{};
					blocks[w][k] = background;
					blocks[w][k]->SetPosition(sf::Vector2f(k * tileSize, w * tileSize));
					blocks[w][k]->SetUp();
					blocks[w][k]->type = backgroundBlock;
				}
			}
			else if (gameMap[w][k] == 2)
			{
				// Place solid wall
				Block* solid = new SolidWall{};
				blocks[w][k] = solid;
				blocks[w][k]->SetPosition(sf::Vector2f(k * tileSize, w * tileSize));
				blocks[w][k]->SetUp();
				blocks[w][k]->type = solidBlock;
			}
			else if (gameMap[w][k] == 1)
			{
				// If gameMap has '1', create a breakable wall (this condition can be removed if using randomness)
				Block* breakable = new BreakableWall{};
				blocks[w][k] = breakable;
				blocks[w][k]->SetPosition(sf::Vector2f(k * tileSize, w * tileSize));
				blocks[w][k]->SetUp();
				blocks[w][k]->type = breakableBlock;
			}
		}
	}
}


void Map::Update(const sf::Time deltaTime)
{
	for (int w = 0; w < 11; w++)
		for (int k = 0; k < 15; k++)
		{
			blocks[w][k]->Update(deltaTime);

			if (blocks[w][k]->IsDestroyed())
			{
				delete blocks[w][k];													

				Block * explosion1 = new Explosion{};
				blocks[w][k] = explosion1;												
				blocks[w][k]->SetPosition(sf::Vector2f(k * tileSize, w * tileSize));
				blocks[w][k]->SetUp();
				blocks[w][k]->type = explosionBlock;

				if (blocks[w - 1][k]->type != solidBlock)
				{
					delete blocks[w - 1][k];

					Block * explosion4 = new Explosion{};
					blocks[w - 1][k] = explosion4;											
					blocks[w - 1][k]->SetPosition(sf::Vector2f(k * tileSize, (w - 1) * tileSize));
					blocks[w - 1][k]->SetUp();
					blocks[w - 1][k]->type = explosionBlock;
				}
				if (blocks[w + 1][k]->type != solidBlock)
				{
					delete blocks[w + 1][k];

					Block * explosion5 = new Explosion{};
					blocks[w + 1][k] = explosion5;												
					blocks[w + 1][k]->SetPosition(sf::Vector2f(k * tileSize, (w + 1) * tileSize));
					blocks[w + 1][k]->SetUp();
					blocks[w + 1][k]->type = explosionBlock;
				}
				if (blocks[w][k - 1]->type != solidBlock)
				{
					delete blocks[w][k - 1];

					Block * explosion2 = new Explosion{};
					blocks[w][k - 1] = explosion2;											
					blocks[w][k - 1]->SetPosition(sf::Vector2f((k - 1) * tileSize, w * tileSize));
					blocks[w][k - 1]->SetUp();
					blocks[w][k - 1]->type = explosionBlock;
				}
				if (blocks[w][k + 1]->type != solidBlock)
				{
					delete blocks[w][k + 1];

					Block * explosion3 = new Explosion{};
					blocks[w][k + 1] = explosion3;												
					blocks[w][k + 1]->SetPosition(sf::Vector2f((k + 1) * tileSize, w * tileSize));
					blocks[w][k + 1]->SetUp();
					blocks[w][k + 1]->type = explosionBlock;
				}
			}

			if (blocks[w][k]->IsExploded())
			{
				delete blocks[w][k];

				Background * background = new Background{};								
				blocks[w][k] = background;												
				blocks[w][k]->SetPosition(sf::Vector2f(k * tileSize, w * tileSize));				
				blocks[w][k]->SetUp();
				blocks[w][k]->type = backgroundBlock;
			}
		}
}

void Map::Draw(sf::RenderWindow & window)
{
	for (int w = 0; w < 11; w++)			
		for (int k = 0; k < 15; k++)
			blocks[w][k]->Draw(window);
}

void Map::LoadFromFile()
{
	std::ifstream inputFile("res/map/map.txt");
	if (inputFile.is_open())
	{
		for (int w = 0; w < 11; w++)
			for (int k = 0; k < 15; k++)
			{
				inputFile >> gameMap[w][k];
			}
	}
}
