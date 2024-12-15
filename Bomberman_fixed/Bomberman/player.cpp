// Added comments for better understanding
#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "bomb.hpp"
#include "map.hpp"
#include "enum.hpp"

#include "windows.h"


Player::Player(std::string arg_name)
	: bombCooldown(1.f), defaultVelocity(200.f, 200.f), playerState(stand), name(arg_name), bombPlaced(0)
{
	velocity = defaultVelocity;

	collisionBox.width = 48;
	collisionBox.height = 48;

	sprite.setOrigin(collisionBox.width / 2, collisionBox.height / 2);
}

void Player::MoveWSAD(const sf::Time & deltaTime, Map & map)
{
	timeSinceBomb -= deltaTime.asSeconds();

	CheckForCollisions(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		GoUp(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		GoDown(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		GoLeft(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		GoRight(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeSinceBomb <= 0)
	{
		timeSinceBomb = bombCooldown;

		Bomb * bomb = new Bomb{};
		bomb->SetUp();
		this->bombPlaced++;

		sf::Vector2f bombLocation = this->GetPosition();									
		bombLocation.x = ((int)bombLocation.x / 64) * 64;									
		bombLocation.y = ((int)bombLocation.y / 64) * 64;									

		bomb->SetPosition(bombLocation);
		
		delete map.blocks[(int)(this->position.y) / 64][(int)(this->position.x) / 64];
		map.blocks[(int)(this->position.y) / 64][(int)(this->position.x) / 64] = bomb;
		map.blocks[(int)(this->position.y) / 64][(int)(this->position.x) / 64]->type = bombBlock;
	}
}

void Player::MoveArrows(const sf::Time & deltaTime, Map & map)
{
	timeSinceBomb -= deltaTime.asSeconds();

	CheckForCollisions(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		GoUp(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		GoDown(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		GoLeft(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		GoRight(deltaTime, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && timeSinceBomb <= 0)
	{
		timeSinceBomb = bombCooldown;

		Bomb * bomb = new Bomb{};
		bomb->SetUp();
		this->bombPlaced++;

		sf::Vector2f bombLocation = this->GetPosition();									
		bombLocation.x = ((int)bombLocation.x / 64) * 64;									
		bombLocation.y = ((int)bombLocation.y / 64) * 64;									

		bomb->SetPosition(bombLocation);

		delete map.blocks[(int)(this->position.y) / 64][(int)(this->position.x) / 64];
		map.blocks[(int)(this->position.y) / 64][(int)(this->position.x) / 64] = bomb;
		map.blocks[(int)(this->position.y) / 64][(int)(this->position.x) / 64]->type = bombBlock;
	}
}

void Player::GoUp(const sf::Time & deltaTime, Map & map)
{
	if (canGoUp)
	{
		position.y -= int(velocity.y * deltaTime.asSeconds());
		playerState = movingUp;
	}
}

void Player::GoDown(const sf::Time & deltaTime, Map & map)
{
	if (canGoDown)
	{
		position.y += int(velocity.y * deltaTime.asSeconds());
		playerState = movingDown;
	}
}

void Player::GoLeft(const sf::Time & deltaTime, Map & map)
{
	if (canGoLeft)
	{
		position.x -= int(velocity.x * deltaTime.asSeconds());
		playerState = movingLeft;
	}
}

void Player::GoRight(const sf::Time & deltaTime, Map & map)

{
	if (canGoRight)
	{
		position.x += int(velocity.x * deltaTime.asSeconds());
		playerState = movingRight;
	}
}

void Player::Update(const sf::Time deltaTime)
{
	UpdateSprite();

	UpdateCollisionBox();

	sprite.setPosition(position);
}

void Player::UpdateSprite()
{
	switch (playerState)
	{
	case stand:
		sprite.setScale(1.f, 1.f);
		break;
	case movingLeft:
		sprite.setScale(-1.f, 1.f);
		break;
	case movingRight:
		sprite.setScale(1.f, 1.f);
		break;
	case movingUp:
		sprite.setScale(-1.f, 1.f);
	case movingDown:
		sprite.setScale(1.f, 1.f);
	}
}

void Player::UpdateCollisionBox()		
{
	collisionBox.left = position.x;
	collisionBox.top = position.y;
}

void Player::CheckForCollisions(const sf::Time & deltaTime, Map & map)
{
	float leftPlayerEdge = this->GetCollisionBox().left - collisionBox.width / 2;
	float rightPlayerEdge = this->GetCollisionBox().left + collisionBox.width / 2;
	float topPlayerEdge = this->GetCollisionBox().top - collisionBox.height / 2;
	float bottomPlayerEdge = this->GetCollisionBox().top + collisionBox.height / 2;

	sf::FloatRect playerCheck(sf::Vector2f(leftPlayerEdge / 64, topPlayerEdge / 64), sf::Vector2f(rightPlayerEdge / 64, bottomPlayerEdge / 64));

	if (map.blocks[(int)(this->GetPosition().y / 64)][(int)((this->GetPosition().x) / 64)]->type == explosionBlock
		&& map.blocks[(int)(this->GetPosition().y / 64)][(int)((this->GetPosition().x) / 64)]->GetCollisionBox().intersects(playerCheck))
	{
		this->Kill();
	}

	if (map.blocks[(int)(topPlayerEdge / 64)][(int)((leftPlayerEdge - 1) / 64)]->type == solidBlock
		|| map.blocks[(int)(topPlayerEdge / 64)][(int)((leftPlayerEdge - 1) / 64)]->type == breakableBlock
		|| map.blocks[(int)(bottomPlayerEdge / 64)][(int)((leftPlayerEdge - 1) / 64)]->type == solidBlock
		|| map.blocks[(int)(bottomPlayerEdge / 64)][(int)((leftPlayerEdge - 1) / 64)]->type == breakableBlock)
	{
		this->ForbidGoingLeft();
		position.x += 1;
	}
	else
		this->AllowGoingLeft();
	
	if (map.blocks[(int)(topPlayerEdge / 64)][(int)((rightPlayerEdge + 1) / 64)]->type == solidBlock
		|| map.blocks[(int)(topPlayerEdge / 64)][(int)((rightPlayerEdge + 1) / 64)]->type == breakableBlock
		|| map.blocks[(int)(bottomPlayerEdge / 64)][(int)((rightPlayerEdge + 1) / 64)]->type == solidBlock
		|| map.blocks[(int)(bottomPlayerEdge / 64)][(int)((rightPlayerEdge + 1) / 64)]->type == breakableBlock)
	{
		this->ForbidGoingRight();
		position.x -= 1;
	}
	else
		this->AllowGoingRight();

	if (map.blocks[(int)((topPlayerEdge - 1) / 64)][(int)(leftPlayerEdge / 64)]->type == solidBlock
		|| map.blocks[(int)((topPlayerEdge - 1) / 64)][(int)(leftPlayerEdge / 64)]->type == breakableBlock
		|| map.blocks[(int)((topPlayerEdge - 1) / 64)][(int)(rightPlayerEdge / 64)]->type == solidBlock
		|| map.blocks[(int)((topPlayerEdge - 1) / 64)][(int)(rightPlayerEdge / 64)]->type == breakableBlock)
	{
		this->ForbidGoingUp();
		position.y += 1;
	}
	else
		this->AllowGoingUp();

	if (map.blocks[(int)((bottomPlayerEdge + 1) / 64)][(int)(leftPlayerEdge / 64)]->type == solidBlock
		|| map.blocks[(int)((bottomPlayerEdge + 1) / 64)][(int)(leftPlayerEdge / 64)]->type == breakableBlock
		|| map.blocks[(int)((bottomPlayerEdge + 1) / 64)][(int)(rightPlayerEdge / 64)]->type == solidBlock
		|| map.blocks[(int)((bottomPlayerEdge + 1) / 64)][(int)(rightPlayerEdge / 64)]->type == breakableBlock)
	{
		this->ForbidGoingDown();
		position.y -= 1;
	}
	else
		this->AllowGoingDown();
}

void Player::SaveToFile(bool param)
{
	std::ofstream outputFile;

	outputFile.open("res/stats/statistics.txt", std::ios_base::app);

	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	if (param)
	{
		outputFile << "\n " << timeinfo.tm_mday << '.' << (timeinfo.tm_mon + 1) << '.' << (timeinfo.tm_year + 1900) << "\t\t"
			<< timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "\n";

		outputFile << "\t" << this->name << " wins!\n";
	}

	outputFile << "\t -" << this->name << " planted " << this->bombPlaced << " bomb(s)\n";
}
