#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "healthyHuman.hpp"
#include "sickHuman.hpp"

class Collector{
    public:
        sf::Sprite sprite;
        Collector(sf::Texture&);
        int healthyPrisonerCount = 0;
        int sickPrisonerCount = 0;
        int maxPrisoners = 10;
        bool moving = false;
        sf::Vector2f direction;
        sf::Vector2i destination;
        std::list<HealthyHuman*> healthyPrisoners;
        std::list<SickHuman*> sickPrisoners;
};