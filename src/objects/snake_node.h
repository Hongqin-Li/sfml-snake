#ifndef SRC_OBJECTS_SNAKE_NODE_H_
#define SRC_OBJECTS_SNAKE_NODE_H_

#include <SFML/Graphics.hpp>

class SnakeNode {
 public:
  explicit SnakeNode(sf::RenderWindow *window,
                     sf::Vector2f position,
                     const sf::Texture& texture);

  void setPosition(sf::Vector2f position) { sprite_.setPosition(position); }
  void setPosition(float x, float y) { sprite_.setPosition(x, y); }
  void setRotation(float angle) { sprite_.setRotation(angle); }

  sf::FloatRect getBounds() const { return sprite_.getGlobalBounds(); }
  sf::Vector2f  getPosition() const { return sprite_.getPosition(); }
  float         getRotation() const { return sprite_.getRotation(); }

  void move(float dx, float dy) { sprite_.move(dx, dy); }

  void render() { window_->draw(sprite_); }

  static const float Width;
  static const float Height;

 private:
  sf::Sprite sprite_;
  sf::RenderWindow *window_;
};

#endif  // SRC_OBJECTS_SNAKE_NODE_H_
