#pragma once

// Prevent double decleration.
#ifndef Game_H
#define Game_H

#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
	private:

		// Vars.
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;

		// Mouse pos
		sf::Vector2i mousePosWin; 
		// View pos captured as floats
		sf::Vector2f mousePosView; 

		// Game logic.
		// never negative
		unsigned points;
		int health;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		int maxEnemies;
		bool mouseHeld;
		bool endGame;

		// Game objects.
		std::vector<sf::RectangleShape> enemies;
		sf::RectangleShape enemy;

		// Private functions.
		void intializeVars();
		void intializeWin();
		void intializeEnemy();

	public:
		// Constructor, Destruction
		Game();
		virtual ~Game();

		// Accessor
		const bool running() const;
		const bool getEndGame() const;


		// Functions.
		void pollEvents();
		void updateMousePos();
		void spawnEnemy();
		void updateEnemies();
		void renderEnemies();
		void update();
		void render();

};

#endif