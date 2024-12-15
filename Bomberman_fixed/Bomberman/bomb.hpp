#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "block.hpp"

class Bomb : public Block
{
	int type;									
	float explodeTime;							
	sf::Texture bombTexture;					
    int timer; // Timer for bomb explosion

public:
	Bomb();

	virtual void Update (const sf::Time deltaTime) override;

        int getTimer() const { return timer; }
        void explode() {
            // Explosion logic here
        }
	virtual void SetUp() override;
};
    //// Bomb class declaration for managing timers
    //class Bomb {
    //private:
    //public:
    //};
    //