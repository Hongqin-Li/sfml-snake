#include "game_over_state.h"

#include <iostream>
#include "../game.h"
#include "game_state.h"
#include "../resource.h"

GameOverState::GameOverState(sf::RenderWindow *window, int score)
    : window_(window), score_(score)
{
  font_.loadFromFile("assets/fonts/main.ttf");

  auto& rm = ResourceManager::getInstance().fonts;
  rm.acquire("assets/fonts/main.ttf");

  text_.setFont(rm.get("assets/fonts/main.ttf"));
  text_.setString("Your score: " + std::to_string(score) + "!"
      "\n\nPress [SPACE] to retry"
      "\n\nPress [ESC] to quit");
  text_.setFillColor(sf::Color::Red);

  sf::FloatRect textBounds = text_.getLocalBounds();
  text_.setOrigin(textBounds.left + textBounds.width / 2,
      textBounds.top + textBounds.height / 2);
  text_.setPosition(Game::Width / 2, Game::Height / 2);

#ifdef DEBUG
  std::cout << "[GameOver] ctor" << std::endl;
#endif
}

GameOverState::~GameOverState()
{
  auto& rm = ResourceManager::getInstance().fonts;
  rm.release("assets/fonts/main.ttf");

#ifdef DEBUG
  std::cout << "[GameOver] dtor" << std::endl;
#endif
}

void GameOverState::handleInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    exitState(std::make_unique<GameState>(window_));
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    exitState();
}

void GameOverState::update(sf::Time dt)
{
}

void GameOverState::render(sf::RenderWindow *winow)
{
  window_->draw(text_);
}
