#pragma once
#include "human.hpp"

class SickHuman : public Human{
    public:
        sf::Sprite sprite;
        SickHuman(sf::Texture&);
};