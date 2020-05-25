#include "menu_state.h"

#include <iostream>

#include "game_state.h"
#include "../game.h"
#include "../resource.h"

MenuState::MenuState(sf::RenderWindow *window) : window_(window)
{
  font_.loadFromFile("assets/fonts/pokemon_pixel_font.ttf");

  text_.setFont(font_);
  text_.setString(
      "\n\n\n\n\n\n\nPress [SPACE] to play\n"
      "Press [ESC] to quit\n"
      "we're here, honey!");
  text_.setStyle(sf::Text::Bold);
  text_.setCharacterSize(32);
  text_.setFillColor(sf::Color(70, 70, 70));

  snakeText_.setFont(font_);
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
  std::cout << "[MenuState] ctor" << std::endl;
}
MenuState::~MenuState()
{
  std::cout << "[MenuState] dtor" << std::endl;
}

void MenuState::handleInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    exitState();
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    pushState(std::make_unique<GameState>(window_));
}

void MenuState::update(sf::Time dt)
{

}

void MenuState::render(sf::RenderWindow *window)
{
  sf::RenderWindow *p = window == nullptr ? window_: window;
  p->draw(text_);
  p->draw(snakeText_);
}
