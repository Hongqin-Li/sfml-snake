#include "menu_state.h"

#include <iostream>

#include "game_state.h"
#include "../game.h"
#include "../resource.h"
#include "../objects/snake_node.h"


MenuState::MenuState(sf::RenderWindow *window) : window_(window), background_(BACKGROUND_WHITE), mesh_(MESH_NONE)
{
  auto& rm = ResourceManager::getInstance().fonts;
  rm.acquire("assets/fonts/main.ttf");

  text_.setFont(rm.get("assets/fonts/main.ttf"));
  text_.setString(
      "\n\n\n\n\n\n\nPress [SPACE] to play\n"
      "[ESC]: quit\n"
      "[b]: change background\n"
      "[m]: change mesh");
  text_.setStyle(sf::Text::Bold);
  text_.setCharacterSize(26);
  text_.setFillColor(sf::Color(70, 70, 70));

  snakeText_.setFont(rm.get("assets/fonts/main.ttf"));
  snakeText_.setString("Snake!");
  snakeText_.setFillColor(sf::Color::Green);
  snakeText_.setCharacterSize(64);
  snakeText_.setStyle(sf::Text::Bold);

  sf::FloatRect textBounds = text_.getLocalBounds();
  text_.setOrigin(textBounds.left + textBounds.width / 2,
                  textBounds.top + textBounds.height / 2);
  text_.setPosition(Game::Width / 2, Game::Height / 2);

  sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
  snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
                       snakeTextBounds.top + snakeTextBounds.height / 2);
  snakeText_.setPosition(Game::Width / 2, Game::Height / 4);

  tiles_ = getBackgroundTiles(background_, mesh_);

#ifdef DEBUG
  std::cout << "[MenuState] ctor" << std::endl;
#endif
}

MenuState::~MenuState()
{
  auto& rm = ResourceManager::getInstance().fonts;
  rm.release("assets/fonts/main.ttf");
#ifdef DEBUG
  std::cout << "[MenuState] dtor" << std::endl;
#endif
}

vector<RectangleShape> MenuState::getBackgroundTiles(int background_color, int mesh_color)
{
  vector<RectangleShape> tiles;
  float size = SnakeNode::Width;

  for (int i = 0; i < Game::Height / size; i++) {
    for (int j = 0; j < Game::Width / size; j++) {
			RectangleShape square;
			square.setSize(Vector2f(size, size));
			square.setPosition(Vector2f(j*size, i*size));
			tiles.push_back(square);
		}
  }
  setTileFillColor(background_color);
  setTileOutlineColor(mesh_color);

  return tiles;
}

void MenuState::setTileFillColor(int background_color)
{
  switch (background_color) {
  case BACKGROUND_WHITE:
    for (auto& tile: tiles_) { tile.setFillColor(sf::Color::White); }
    break;
  case BACKGROUND_BLACK:
    for (auto& tile: tiles_) { tile.setFillColor(sf::Color(0, 0, 0, 255*0.8)); }
    break;
  case BACKGROUND_BROWN:
    for (auto& tile: tiles_) { tile.setFillColor(sf::Color(150, 75, 0)); }
    break;
  default:
    assert(false);
  }
}

void MenuState::setTileOutlineColor(int mesh_color)
{
  switch (mesh_color) {
  case MESH_NONE:
    for (auto& tile: tiles_) {
			tile.setOutlineThickness(0);
    }
    break;
  case MESH_WHITE:
    for (auto& tile: tiles_) {
			tile.setOutlineThickness(-1.f);
      tile.setOutlineColor(sf::Color::White);
    }
    break;
  case MESH_BLACK:
    for (auto& tile: tiles_) {
			tile.setOutlineThickness(-1.f);
      tile.setOutlineColor(sf::Color(0, 0, 0, 255*0.8));
    }
    break;
  case MESH_BROWN:
    for (auto& tile: tiles_) {
			tile.setOutlineThickness(-1.f);
      tile.setOutlineColor(sf::Color(150, 75, 0));
    }
    break;
  default: assert(false);
  }
}

void MenuState::handleInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    exitState();
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
    background_ = (background_ + 1) % NUM_BACKGROUND_COLORS;
    setTileFillColor(background_);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
    mesh_ = (mesh_ + 1) % NUM_MESH_COLORS;
    setTileOutlineColor(mesh_);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    pushState(std::make_unique<GameState>(window_, tiles_));
}

void MenuState::update(sf::Time dt)
{
}

void MenuState::render(sf::RenderWindow *window)
{
  sf::RenderWindow *p = window == nullptr ? window_: window;
  for (auto& tile: tiles_)
      p->draw(tile);

  p->draw(snakeText_);
  p->draw(text_);

}
