#pragma once
#include <SFML/Graphics.hpp>

class Baddy{
    public:
        sf::Sprite sprite;
        Baddy(sf::Texture&);
        float speed = 50.0f;
        bool frosty = false;
        sf::Vector2f destination;
        sf::Vector2f direction;
};
