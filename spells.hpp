#pragma once
#include <SFML/Graphics.hpp>

class Spells{
    public:
        sf::ConvexShape area;
        sf::Color color;
        Spells(int, int, int, int);
};