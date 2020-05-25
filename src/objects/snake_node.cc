#include "snake_node.h"

#include <iostream>
#include <SFML/Graphics.hpp>

const float SnakeNode::Width = 20.f;
const float SnakeNode::Height = 20.f;

SnakeNode::SnakeNode(sf::RenderWindow *window, sf::Vector2f position, const sf::Texture& texture)
    : window_(window)
{
  sprite_.setTexture(texture);

  auto bound = sprite_.getGlobalBounds();
  sprite_.setOrigin(bound.width / 2, bound.height / 2);

  float ratio = SnakeNode::Height / bound.height;
  sprite_.setScale(sf::Vector2f(ratio, ratio));

  // sprite_.setTextureRect(sf::IntRect(0, 0, SnakeNode::Width, 32));
  // sprite_.setScale();

  // sprite_.setRadius(0.5 * SnakeNode::Width);
  // sprite_.setFillColor(sf::Color(255, 225, 21));

  sprite_.setPosition(position);
  std::cout << "[SnakeNode] ctor" << getBounds().width << " " << getBounds().height << std::endl;
}
