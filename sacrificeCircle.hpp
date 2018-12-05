#pragma once
#include <SFML/Graphics.hpp>

class SacrificeCircle{
    public:
        sf::Sprite sprite;
        sf::Time lastTick;
        int mana = 0;
        SacrificeCircle(sf::Texture&);
};
