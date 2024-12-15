// Added comments for better understanding
#include <iostream>
#include <SFML/Graphics.hpp>

#include "explosion.hpp"

Explosion::Explosion() : flameTime(1.f)
{
	collisionBox.top = this->GetPosition().y;
	collisionBox.left = this->GetPosition().x;
	collisionBox.width = 64;
	collisionBox.height = 64;

	sprite.setOrigin(-10, -10);
}

void Explosion::Update(const sf::Time deltaTime)
{
	sprite.setPosition(position);

	flameTime -= deltaTime.asSeconds();
	if (flameTime <= 0)
		this->Explode();
}

void Explosion::SetUp()
{
	if (!explosionTexture.loadFromFile("res/img/flame.png"))
	{
		std::cout << "Load failed! " << std::endl;
		getchar();
	}

	LoadTexture(explosionTexture);
}

    // Include necessary header for stack
    #include <stack>
    
    // Stack to store fire sprites during explosion
    std::stack<sf::Sprite> fireSprites;
    
void createFireSprite()
{
    // Logic to generate fire sprites for explosions
    // Placeholder implementation with comments explaining each step
    std::cout << "Creating fire sprites for explosions" << std::endl;
}
    void startExplosion(const Explosion& explosion) {
        // Create fire sprites and push onto the stack
        for (int i = 0; i < explosion.getFireCount(); i++) {
            sf::Sprite fireSprite = createFireSprite();
            fireSprites.push(fireSprite);
        }
    }
    
    // Function to handle explosion sprite clearing
    void clearExplosionSprites() {
        while (!fireSprites.empty()) {
            fireSprites.pop(); // Remove each sprite after explosion
        }
    }
    
#include "explosion.hpp"

// Function to create fire sprites (placeholder example)
