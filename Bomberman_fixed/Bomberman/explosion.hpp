// Added comments for better understanding
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "block.hpp"

class Explosion : public Block
{
	int type;										
	float flameTime;								
	sf::Texture explosionTexture;					
        int fireCount;

public:
	Explosion();

	void Update(const sf::Time deltaTime) override;

	virtual void SetUp() override;
        int getFireCount() const { return fireCount; }
};
    //// Explosion class and fire sprite stack declaration
    //class Explosion {
    //private:
    //public:
    //};
    