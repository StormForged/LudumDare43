#pragma once
#include <SFML/Graphics.hpp>

class FelLab{
    public:
        sf::Sprite sprite;
        sf::Time lastTick;
        int bodies = 0;
        int felBombs = 0;
        FelLab(sf::Texture&);

};