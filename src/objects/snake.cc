#include "snake.h"

#include <cmath>
#include <cassert>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "../game.h"
#include "snake_node.h"
#include "fruit.h"

const int Snake::InitialSize = 5;
const float Snake::kStep = 0.8;

static constexpr float pi() { return std::atan(1) * 4; }

Snake::Snake(sf::RenderWindow *window)
    : direction_(0, Snake::kStep * SnakeNode::Height), hitSelf_(false), window_(window)
{
  assert(head_texture_.loadFromFile("assets/textures/snake_head.png"));
  assert(body_texture_.loadFromFile("assets/textures/snake_body.png"));

  initNodes();

  std::cout << "[Snake] ctor" << std::endl;

  // pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
  // pickupSound_.setBuffer(pickupBuffer_);
  // pickupSound_.setVolume(30);

  // dieBuffer_.loadFromFile("Sounds/die.wav");
  // dieSound_.setBuffer(dieBuffer_);
  // dieSound_.setVolume(50);
}

void Snake::initNodes()
{
  for (int i = 0; i < Snake::InitialSize; ++i) {
    nodes_.push_back(
        SnakeNode(window_, 
                  sf::Vector2f(Game::Width / 2 - SnakeNode::Width / 2,
                               Game::Height / 2 - (SnakeNode::Height / 2) +
                                   (SnakeNode::Height * i)),
                  i == 0 ? head_texture_: body_texture_));
  }
}

void Snake::handleInput()
{
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    auto head_pos = nodes_[0].getPosition();
    auto mouse_pos = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
    // https://stackoverflow.com/questions/29201727/mouse-position-relative-to-sfview

    direction_.x = mouse_pos.x - head_pos.x;
    direction_.y = -mouse_pos.y + head_pos.y;

    std::cout << "head: " << head_pos.x << ", " << head_pos.y
              << std::endl;
    std::cout << "mouse: " << mouse_pos.x << ", " << mouse_pos.y
              << std::endl;

    direction_ /= static_cast<float>(
        sqrt(direction_.x * direction_.x + direction_.y * direction_.y));
    direction_ *= Snake::kStep * SnakeNode::Height;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    direction_.x = 0;
    direction_.y = Snake::kStep * SnakeNode::Height;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    direction_.x = 0;
    direction_.y = -Snake::kStep * SnakeNode::Height;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    direction_.x = -Snake::kStep * SnakeNode::Height;
    direction_.y = 0;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    direction_.x = Snake::kStep * SnakeNode::Height;
    direction_.y = 0;
  }
  // std::cout << "direction_: " << direction_.x << ", " << direction_.y <<
  // std::endl;
}

void Snake::update(sf::Time delta)
{
  move();
  checkEdgeCollisions();
  checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit> *fruits)
{
  auto headBound = nodes_[0].getBounds();

  for (auto it = fruits->begin(); it != fruits->end(); ++it) {
    if (it->getBounds().intersects(headBound)) {
      // pickupSound_.play();
      grow(it->getEnergy());
      fruits->erase(it);
      break;
    }
  }
}

void Snake::grow(int cnt)
{
  std::cout << "[Snake] grow " << cnt << std::endl;
  for (int i = 0; i < cnt; i++) {
    nodes_.push_back(SnakeNode(window_, 
                               sf::Vector2f(nodes_.back().getPosition().x,
                                            nodes_.back().getPosition().y),
                               body_texture_));
  }
}

unsigned Snake::getSize() const { return nodes_.size(); }

bool Snake::hitSelf() const { return hitSelf_; }

void Snake::checkSelfCollisions()
{
  SnakeNode &headNode = nodes_[0];

  const auto headBound = headNode.getBounds();

  // Omit the first 3
  for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i) {
    if (headBound.intersects(nodes_[i].getBounds())) {
      // dieSound_.play();
      // sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
      hitSelf_ = true;
    }
  }
}

void Snake::checkEdgeCollisions()
{
  SnakeNode &headNode = nodes_[0];

  if (headNode.getPosition().x <= 0)
    headNode.setPosition(Game::Width, headNode.getPosition().y);
  else if (headNode.getPosition().x >= Game::Width)
    headNode.setPosition(0, headNode.getPosition().y);
  else if (headNode.getPosition().y <= 0)
    headNode.setPosition(headNode.getPosition().x, Game::Height);
  else if (headNode.getPosition().y >= Game::Height)
    headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
  for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i) {
    nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
    nodes_[i].setRotation(nodes_.at(i - 1).getRotation());
  }
  nodes_[0].move(direction_.x, -direction_.y);
  nodes_[0].setRotation(90 -
                        std::atan2(direction_.y, direction_.x) * 180 / pi());
}

void Snake::render()
{
  for (auto& node : nodes_)
    node.render();
}
