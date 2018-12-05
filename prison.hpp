#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "healthyHuman.hpp"

class Prison{
    public:
        sf::Sprite sprite;
        Prison(sf::Texture&);
        int prisonerCount = 0;
        std::list<HealthyHuman*> prisoners;
};