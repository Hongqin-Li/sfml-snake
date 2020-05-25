#ifndef SRC_OBJECTS_SNAKE_H_
#define SRC_OBJECTS_SNAKE_H_

#include <vector>

#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

#include "fruit.h"
#include "snake_node.h"

class Snake {
 public:
  Snake(sf::RenderWindow *window);

  void handleInput();
  void update(sf::Time delta);
  void render();

  void checkFruitCollisions(std::vector<Fruit> *fruits);

  bool hitSelf() const;

  unsigned getSize() const;

  static const float kStep;
  static const int InitialSize;

 private:
  void move();
  void grow(int cnt);
  void checkEdgeCollisions();
  void checkSelfCollisions();
  void initNodes();

  bool hitSelf_;

  sf::Vector2f position_;
  sf::Vector2f direction_;

  sf::Texture head_texture_;
  sf::Texture body_texture_;
  // sf::SoundBuffer pickupBuffer_;
  // sf::Sound pickupSound_;

  // sf::SoundBuffer dieBuffer_;
  // sf::Sound dieSound_;

  std::vector<SnakeNode> nodes_;

  sf::RenderWindow *window_;
};

#endif  // SRC_OBJECTS_SNAKE_H_
