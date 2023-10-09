#include "Game.h"

// Private functions.

void Game::intializeVars() {
	// Dynamic allocation.
	this->window = nullptr;

    // Game logic.
    this->points = 0;
    this->enemySpawnTimerMax = 50.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->health = 5;
    this->endGame = false;

}

void Game::intializeWin() {
	// init video mode
	this->videoMode.height = 640;
	this->videoMode.width = 480;

	this->window = new sf::RenderWindow(this->videoMode, "window", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::intializeEnemy() {
    // Properties of enemy.
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Blue);
    this->enemy.setOutlineThickness(1.5f);
}

void Game::intializeFonts() {
    // Set font
    this->font.loadFromFile("Fonts/PixelifySans-Bold.ttf");
        

}

void Game::intializeText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(25);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("TEST");
}

// Constructor / Destructor.

Game::Game() {
	// Order matters.
    this->intializeFonts();
    this->intializeText();
	this->intializeVars();
	this->intializeWin();
    this->intializeEnemy();
}

Game::~Game() {
	delete this->window;
}

// Accessors.
const bool Game::running() const {
	return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}


// Public Functions.

void Game::spawnEnemy() {
    /*
        @return void

        Spawns enemy and sets positions.
    */

    this->enemy.setPosition(
        static_cast<float>(rand()% static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
    );

    // Spawns enemy
    this->enemies.push_back(this->enemy);
}

void Game::renderEnemies(sf::RenderTarget& target) {

    for (auto& e : this->enemies) {
        target.draw(e);
    }
}

void Game::updateEnemies() {

    if (this->enemies.size() < this->maxEnemies) {

        if (this->enemySpawnTimer > this->enemySpawnTimerMax) {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else {
            this->enemySpawnTimer += 1.f;
        }

    }

    // Move and update enemies
    for (int i = 0; i < this->enemies.size(); i++) {

        // Deleted status flag
        bool deleted = false;

        // Move enemies down.
        this->enemies[i].move(0.f, 5.f);

        // Check if clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {    
            if (this->enemies[i].getGlobalBounds().contains(this->mousePosView) && this->mouseHeld == false) {
                deleted = true;
                //increment score
                this->points += 1.f;
            }
            this->mouseHeld = true;
        }
        else {
            this->mouseHeld = false;
        }

        if (this->enemies[i].getPosition().y > this->window->getSize().y && !deleted) {
            deleted = true;
            this->health -= 1;
            
        }

        if (deleted) {
            // Remove enemy
            this->enemies.erase(this->enemies.begin() + i);
        }

    }
}

void Game::pollEvents() {
    // Event polling.
    while (this->window->pollEvent(this->ev)) {
        switch (ev.type) {

            // Listen for close, either escape or close button.
            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;

        }
    }
}

void Game::updateMousePos() {
    /*
        @return void

        Update mouse position.
    */

    this->mousePosWin = sf::Mouse::getPosition(*this->window);
    // Converts mousePosWin to float
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWin);
}

void Game::renderText(sf::RenderTarget& target) {

    target.draw(this->uiText);

}

void Game::updateText() {

    std::stringstream ss;

    ss << "Points: " << this->points << "\n"
        << "Health: " << this->health;

    this->uiText.setString(ss.str());

}

void Game::update() {
    this->pollEvents();

    // If game hasn't ended
    if (!this->endGame) {
        this->updateMousePos();

        this->updateText();

        this->updateEnemies();
    }

    // Check if game has ended.
    if (health <= 0) {
        this->endGame = true;
    }
}

void Game::render() {
    /*
        @return void

        -clear old frame
        - render objects
        -display frame in window

        Renders the game objects.
    */

    this->window->clear();

    // Draw game.
    this->renderEnemies(*this->window);

    // Render text.
    this->renderText(*this->window);
    
    this->window->display();
}