#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <memory>
#include <stack>

#include <SFML/Graphics.hpp>

#include "game.h"
#include "states/state.h"

class Game {
public:
  Game();
  void run();

  void render();
  void update(sf::Time dt);
  void handleInput();

  // State Machine
  void swtch();
  std::unique_ptr<State>& current_state();

  sf::RenderWindow& getWindow() { return window_; }

  static const int Width = 640;
  static const int Height = 480;
  static const sf::Time TimePerFrame;

private:
  std::stack<std::unique_ptr<State>> states_;
  sf::RenderWindow window_;

};

#endif  // SRC_GAME_H_
