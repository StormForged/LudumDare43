#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "healthyHuman.hpp"

class Spawnatorium{
    public:
        sf::Sprite sprite;
        sf::Time lastTick;
        Spawnatorium(sf::Texture&);
        int foodSupply = 0;
        std::vector<HealthyHuman*> spawned;
};