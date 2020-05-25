#ifndef SRC_MENU_STATE_H_
#define SRC_MENU_STATE_H_

#include <SFML/Graphics.hpp>

#include "state.h"

class MenuState : public State
{
public:
  MenuState(sf::RenderWindow *window);
  ~MenuState();

  void handleInput() override;
  void update(sf::Time dt) override;
  void render(sf::RenderWindow *window = nullptr) override;

private:
  sf::RenderWindow *window_;
  sf::Font font_;
  sf::Text snakeText_;
  sf::Text text_;
  
};

#endif  /* !SRC_MENU_STATE_H_ */
