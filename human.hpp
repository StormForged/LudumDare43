#pragma once

#include <SFML/Graphics.hpp>

class Human{
    public:
    sf::Sprite sprite;
    Human();
    Human(sf::Texture&);
    sf::Vector2f destination;
    sf::Vector2f direction;
    bool captured = false;
    bool interactable = true;
};