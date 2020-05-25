#ifndef SRC_OBJECTS_FRUIT_H_
#define SRC_OBJECTS_FRUIT_H_

#include <SFML/Graphics.hpp>

class Fruit {
 public:
  Fruit(sf::RenderWindow *window, sf::Vector2f position = sf::Vector2f(0, 0),
        sf::Color color = sf::Color::Red, int energy = 0);
  ~Fruit();

  void render() { window_->draw(shape_); }

  sf::FloatRect getBounds() const { return shape_.getGlobalBounds(); }

  int getEnergy() const { return energy_; }

  static const float Radius;

 private:
  sf::RenderWindow *window_;
  sf::CircleShape shape_;

  int energy_;

};

#endif  // SRC_OBJECTS_FRUIT_H_
