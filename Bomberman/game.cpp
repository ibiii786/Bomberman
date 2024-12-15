// Added comments for better understanding
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "game.hpp"
#include "player.hpp"
#include "map.hpp"
#include "solid_wall.hpp"
#include "breakable_wall.hpp"
#include "bomb.hpp"
#include "end_game_screen.hpp"

Game::Game()
{
	windowSize.x = 960;
	windowSize.y = 700;
	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Bomberman");

	window.setFramerateLimit(60);

	player1.SetPosition(sf::Vector2f( 96, 96));
	player2.SetPosition(sf::Vector2f( 864, 604));

	isOver = false;
}

void Game::Update(const sf::Time deltaTime)
{
	map.Update(deltaTime);
	player1.Update(deltaTime);
	player2.Update(deltaTime);
}

void Game::Draw()
{
	map.Draw(window);
	player1.Draw(window);
	player2.Draw(window);

	if (isOver)
		endGameScreen.Draw(window);
}
void Game::Play()
{
    // Background music setup
    if (!backgroundMusic.openFromFile("res/sound/game.wav")) {
        std::cerr << "Error: Could not load background music!" << std::endl;
        return;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(50);
    backgroundMusic.play();

    // Play the music when the game starts.
    if (!backgroundMusic.getStatus() == sf::Music::Playing) {
        backgroundMusic.play();
    }

    // Sound effect setup for player death
    sf::SoundBuffer deathSoundBuffer;
    if (!deathSoundBuffer.loadFromFile("res/sound/hurt.wav")) {
        std::cerr << "Error: Could not load death sound effect!" << std::endl;
        return;
    }
    sf::Sound deathSound;
    deathSound.setBuffer(deathSoundBuffer);

    sf::Clock clock;
    sf::Time time;

    if (!font.loadFromFile("res/fonts/Cat.ttf")) {
        std::cout << "Load failed!" << std::endl;
        getchar();
        return;
    } else {
        endGameScreen.LoadFont(font);
    }

    // Player 1 setup
    if (!player1.texture_p1.loadFromFile("res/img/bomberman1.png")) {
        std::cout << "Load failed!" << std::endl;
        getchar();
        return;
    }
    // Player 2 setup
    if (!player2.texture_p2.loadFromFile("res/img/bomberman2.png")) {
        std::cout << "Load failed!" << std::endl;
        getchar();
        return;
    }


    player1.LoadTexture(player1.texture_p1);
    player2.LoadTexture(player2.texture_p2);
    map.LoadFromFile();
    map.LoadTiles();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                window.close();

            if (isOver) {
                if (player2.IsKilled() && once) {
                    //deathSound.play(); // Play death sound effect
                    player1.SaveToFile(true);
                    player2.SaveToFile(false);
                } else if (player1.IsKilled() && once) {
                    //deathSound.play(); // Play death sound effect
                    
                    player2.SaveToFile(true);
                    player1.SaveToFile(false);
                }

                once = false;

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    PlayAgain(); backgroundMusic.play();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color::Black);
        time = clock.restart();

        if (!isOver) {
            player1.MoveWSAD(time, map);
            player2.MoveArrows(time, map);

            if (player1.IsKilled()) {
                isOver = true;
                backgroundMusic.pause();
                deathSound.play(); // Play death sound effect
                endGameScreen.DisplayPlayer1Win(false);
            } else if (player2.IsKilled()) {
                isOver = true;
                backgroundMusic.pause();
                deathSound.play(); // Play death sound effect
                endGameScreen.DisplayPlayer1Win(true);
            }
        }

        Update(time);
        Draw();
        window.display();
    }
}

void Game::PlayAgain()
{


	isOver = false;
   

	map.LoadFromFile();
	map.LoadTiles();

	player1.SetPosition(sf::Vector2f(96, 96));
	player2.SetPosition(sf::Vector2f(864, 604));

	player1.killed = false;
	player2.killed = false;

	player1.bombPlaced = 0;
	player2.bombPlaced = 0;
    

	once = true;
}

    // Include necessary header for queue
    #include <queue>
    
    // Queue to manage player events like bomb placement, explosion, etc.
    std::queue<PlayerEvent> eventQueue;
    
    // Function to handle event processing (space, right shift, bomb placement, etc.)
    void processEvents() {
        while (!eventQueue.empty()) {
            PlayerEvent event = eventQueue.front();
            eventQueue.pop();
            handleEvent(event);
        }
    }
    
    void handleEvent(const PlayerEvent& event) {
        switch (event.type) {
            case PlayerEvent::BOMB_PLACEMENT:
                placeBomb(event.bomb);
                break;
            case PlayerEvent::BOMB_EXPLOSION:
                handleBombs();
                break;
            case PlayerEvent::PLAYER_DEATH:
                handlePlayerDeath(event.player);
                break;
            // Other events can be handled here
        }
    }
    