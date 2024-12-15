// Added comments for better understanding
#include <iostream>
#include <SFML/Graphics.hpp>

#include "bomb.hpp"
#include "explosion.hpp"

Bomb::Bomb() : explodeTime(2.f), type(bombBlock)
{
	sprite.setOrigin(-10, -10);
}

void Bomb::Update(const sf::Time deltaTime)
{
	sprite.setPosition(position);

	explodeTime -= deltaTime.asSeconds();
	if (explodeTime <= 0)
		this->Destroy();
}

void Bomb::SetUp()
{
	if (!bombTexture.loadFromFile("res/img/bomb.png"))
	{
		std::cout << "Load failed! " << std::endl;
		getchar();
	}
	LoadTexture(bombTexture);
}


    // Include necessary header for priority queue
    #include <queue>
    #include <functional>
    
    // Priority queue for bomb timers (for ordering bomb explosions)
    std::priority_queue<Bomb, std::vector<Bomb>, std::function<bool(Bomb, Bomb)>> bombQueue([](const Bomb& b1, const Bomb& b2) {
        return b1.getTimer() > b2.getTimer(); // Bomb with the shortest timer should have the highest priority
    });
    
    // Function to handle bomb placement and add to priority queue
    void placeBomb(Bomb bomb) {
        bombQueue.push(bomb); // Add bomb to the queue
    }

    // Function to handle bomb explosion based on the timer
    void handleBombs() {
        while (!bombQueue.empty() && bombQueue.top().getTimer() <= currentTime) {
            Bomb bomb = bombQueue.top();
            bombQueue.pop();
            bomb.explode();
        }
    }
    