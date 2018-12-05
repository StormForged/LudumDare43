#pragma once
#include "human.hpp"

class HealthyHuman : public Human {
    public:
        HealthyHuman(sf::Texture&);
        float speed = 50.0f;
        bool frosty = false;
        bool running = true;
        bool prison = false;
        bool spawnatorium = false;
};