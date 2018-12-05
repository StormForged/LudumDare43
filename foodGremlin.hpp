#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class FoodGremlin{
    public:
        sf::Sprite sprite;
        FoodGremlin();
        FoodGremlin(sf::Texture&);
        int food = 0;
        int maxFood = 10;
        bool moving = false;
        bool selected = false;
        sf::Time lastTick;
        sf::Vector2f direction;
        sf::Vector2i destination;
};