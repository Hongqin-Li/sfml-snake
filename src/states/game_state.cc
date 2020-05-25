#include "game_state.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <random>

#include <SFML/Graphics.hpp>

#include "../game.h"
#include "game_over_state.h"

GameState::GameState(sf::RenderWindow *window) : snake_(window), window_(window)
{
#ifdef DEBUG
  std::cout << "[GameState] ctor" << std::endl;
#endif
}
GameState::~GameState()
{
#ifdef DEBUG
  std::cout << "[GameState] dtor" << std::endl;
#endif
}

void GameState::handleInput()
{
  snake_.handleInput();
}

void GameState::update(sf::Time delta)
{
  if (fruit_.size() == 0) generateFruit();

  snake_.update(delta);
  snake_.checkFruitCollisions(&fruit_);

  if (snake_.hitSelf()) {
    std::cout << "[Game] snake hit self!" << std::endl;
    exitState(std::make_unique<GameOverState>(window_, snake_.getSize()));
  }
}

void GameState::render(sf::RenderWindow *window)
{
  snake_.render();
  for (auto& fruit : fruit_) fruit.render();
}

void GameState::generateFruit()
{
  static std::default_random_engine engine(time(NULL));

  static std::uniform_int_distribution<int> xDistribution(
      0, Game::Width - SnakeNode::Width),
      yDistribution(0, Game::Height - SnakeNode::Height),
      typeDistribution(0, 7);

  int energy;
  sf::Color color;
  switch (typeDistribution(engine)) {
    case 0:
      energy = 0;
      color = sf::Color::Black;
      break;
    case 1:
      energy = 0;
      color = sf::Color::Magenta;
      break;
    case 2:
    case 3:
      energy = 1;
      color = sf::Color::Green;
      break;
    case 4:
    case 5:
      energy = 2;
      color = sf::Color::Blue;
      break;
    case 6:
    case 7:
      energy = 3;
      color = sf::Color::Red;
      break;
    default:
      assert(false);
  }

  fruit_.push_back(
      Fruit(window_, 
            sf::Vector2f(xDistribution(engine), yDistribution(engine)),
            color,
            energy));
}
