#include "game.h"

#include <iostream>
#include <cassert>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "states/menu_state.h"
#include "resource.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

Game::Game() : window_(sf::VideoMode(Game::Width, Game::Height), "SFML Game")
{
  std::cout << sf::VideoMode::getDesktopMode().width << ", "
            << sf::VideoMode::getDesktopMode().height;
  // snake_body_texture.loadFromFile("assets/textures/snake_body.png");
  // snake_head_texture.loadFromFile("assets/textures/snake_head.png");
  // bgMusic_.openFromFile("Music/bg_music.wav");
  // bgMusic_.setLoop(true);
  // bgMusic_.play();
  states_.push(std::make_unique<MenuState>(&window_));
}

void Game::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  clock.restart();
  while (window_.isOpen()) {
    sf::Time delta = clock.restart();
    timeSinceLastUpdate += delta;

    while (timeSinceLastUpdate > Game::TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      if (!states_.empty())
        handleInput();

      if (!states_.empty())
        update(TimePerFrame);
    }
    if (!states_.empty())
      render();
    else 
      break;
  }
}

std::unique_ptr<State>& Game::current_state()
{
  assert(!states_.empty());
  return states_.top();
}

// The State Machine
void Game::swtch()
{
  auto& this_state = states_.top();
  auto s = this_state->getState();
  assert(s != STATE_RUNNING);

  switch (s) {
  case STATE_PAUSE:
    assert(this_state->getNext());
    states_.push(std::move(this_state->getNext()));
    break;

  case STATE_EXIT:
    if (this_state->getNext()) {
      auto next = std::move(this_state->getNext());
      assert(next->getState() == STATE_RUNNING);
      states_.pop();
      states_.push(std::move(next));
    }
    else {
      states_.pop();
      std::cout << "state exit, #left: " << states_.size() << std::endl;
      if (!states_.empty()) {
        auto& prev_state = states_.top();
        assert(prev_state->getState() == STATE_PAUSE);
        prev_state->resume();
      }
    }
    break;

  default:
    std::cout << this_state->getState() << std::endl;
    assert(false);
  }
}

void Game::handleInput()
{
  sf::Event event;

  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window_.close();
  }

  auto& this_state = states_.top();
  this_state->handleInput();

  if (this_state->getState() != STATE_RUNNING)
    swtch();
}



void Game::update(sf::Time dt)
{
  auto& this_state = states_.top();
  this_state->update(dt);

  if (this_state->getState() != STATE_RUNNING)
    swtch();
}

void Game::render()
{
  window_.clear(sf::Color(241, 241, 241));
  auto& this_state = states_.top();
  this_state->render();
  window_.display();

  if (this_state->getState() != STATE_RUNNING)
    swtch();
}
