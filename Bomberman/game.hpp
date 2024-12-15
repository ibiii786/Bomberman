// Added comments for better understanding
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 

#include "player.hpp"
#include "map.hpp"
#include "end_game_screen.hpp"
using namespace std;

class Game
{
	sf::RenderWindow window;										
	sf::Vector2f windowSize;										
	Player player1{"Player 1"};										
	Player player2{"Player 2"};										
	Map map;														
	EndGameScreen endGameScreen;									
	sf::Font font;					
	sf::Music backgroundMusic;
	bool isOver;													
	bool once = true;												

public:
	Game();

	void Update(const sf::Time deltaTime);

	void Draw();

	void Play();

	void PlayAgain();
};
    // Player event structure to represent different actions
    struct PlayerEvent {
        enum EventType {
            BOMB_PLACEMENT,
            BOMB_EXPLOSION,
            PLAYER_DEATH
            // Add more event types as needed
        } type;
        Bomb bomb;
        Player player;
    };
    