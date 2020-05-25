#include "fruit.h"

#include <iostream>
#include <SFML/Graphics.hpp>

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::RenderWindow *window, sf::Vector2f position,
             sf::Color color, int energy): energy_(energy), window_(window) {
    std::cout << "[Fruit] ctor " << std::endl;
    shape_.setPosition(position);
    shape_.setRadius(Fruit::Radius);
    shape_.setFillColor(color);
}

Fruit::~Fruit()
{
    std::cout << "[Fruit] dtor " << std::endl;
}
