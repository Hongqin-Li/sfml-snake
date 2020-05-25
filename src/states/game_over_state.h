#ifndef SRC_STATES_GAME_OVER_STATE_H_
#define SRC_STATES_GAME_OVER_STATE_H_

#include <SFML/Graphics.hpp>

#include "state.h"

class GameOverState : public State
{
 public:
  GameOverState(sf::RenderWindow *window, int score);
  ~GameOverState();

  void handleInput() override;
  void update(sf::Time dt) override;
  void render(sf::RenderWindow *window) override;

 private:
  sf::RenderWindow *window_;
  sf::Font font_;
  sf::Text text_;

  int score_;
};

#endif  // SRC_STATES_GAME_OVER_STATE_H_
