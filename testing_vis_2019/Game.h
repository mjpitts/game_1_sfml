#pragma once

// Prevent double decleration.
#ifndef Game_H
#define Game_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
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

		// Resources 
		sf::Font font;

		// Text
		sf::Text uiText;

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
		void intializeFonts();
		void intializeText();

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
		void renderEnemies(sf::RenderTarget& target);

		void renderText(sf::RenderTarget& target);
		void updateText();

		void update();
		void render();

};

#endif