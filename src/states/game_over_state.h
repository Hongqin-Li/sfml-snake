#ifndef SRC_STATES_GAME_OVER_STATE_H_
#define SRC_STATES_GAME_OVER_STATE_H_

#include <SFML/Graphics.hpp>

#include "state.h"

class GameOverState : public State
{
 public:
  GameOverState(sf::RenderWindow *window, int score, std::vector<sf::RectangleShape> tiles);
  ~GameOverState();

  void handleInput() override;
  void update(sf::Time dt) override;
  void render(sf::RenderWindow *window) override;

 private:
  sf::RenderWindow *window_;
  sf::Text text_;
  std::vector<sf::RectangleShape> tiles_;

  int score_;
};

#endif  // SRC_STATES_GAME_OVER_STATE_H_
