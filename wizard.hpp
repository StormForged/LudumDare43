#pragma once
#include <SFML/Graphics.hpp>

class Wizard{
    public:
        sf::Sprite sprite;
        Wizard(sf::Texture&);
        bool moving = false;
        sf::Time castTime;
        sf::Time lastTick;
        sf::Vector2f direction;
        sf::Vector2f destination;
};