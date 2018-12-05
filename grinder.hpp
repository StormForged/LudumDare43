#pragma once
#include <SFML/Graphics.hpp>

class Grinder{
    public:
        sf::Sprite sprite;
        sf::Time lastTick;
        int ungrindedMeat = 0;
        int foodSupply = 0;
        Grinder(sf::Texture&);
};