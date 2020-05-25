#ifndef SRC_GAME_STATE_H_
#define SRC_GAME_STATE_H_

#include <vector>

#include <SFML/Graphics.hpp>

#include "state.h"
#include "../objects/snake.h"

class GameState : public State
{
public:
  GameState(sf::RenderWindow *window);
  ~GameState();

  void handleInput() override;
  void update(sf::Time dt) override;
  void render(sf::RenderWindow *window = nullptr) override;

  void generateFruit();

private:
  sf::RenderWindow *window_;

  Snake snake_;
  std::vector<Fruit> fruit_;
  
};

#endif  // SRC_GAME_STATE_H_
