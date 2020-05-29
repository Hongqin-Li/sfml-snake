#ifndef SRC_STATES_MENU_STATE_H_
#define SRC_STATES_MENU_STATE_H_

#include <SFML/Graphics.hpp>

#include "state.h"

enum {
  BACKGROUND_WHITE = 0,
  BACKGROUND_BLACK,
  BACKGROUND_BROWN,
  NUM_BACKGROUND_COLORS,
};

enum {
  MESH_NONE = 0,
  MESH_WHITE,
  MESH_BLACK,
  MESH_BROWN,
  NUM_MESH_COLORS,
};

using std::vector;
using sf::RenderWindow;
using sf::RectangleShape;
using sf::Color;
using sf::Vector2f;

class MenuState : public State
{
public:
  MenuState(sf::RenderWindow *window);
  ~MenuState();

  void handleInput() override;
  void update(sf::Time dt) override;
  void render(sf::RenderWindow *window = nullptr) override;

  vector<RectangleShape> getBackgroundTiles(int bg, int mc);


private:
  sf::RenderWindow *window_;

  sf::Text snakeText_;
  sf::Text text_;

  int background_;
  int mesh_;

  vector<RectangleShape> tiles_;

  void setTileFillColor(int b);
  void setTileOutlineColor(int b);

};

#endif  // SRC_STATES_MENU_STATE_H_
