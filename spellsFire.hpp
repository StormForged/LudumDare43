#pragma once
#include "spells.hpp"

class SpellsFire : public Spells{
    public:
        SpellsFire(int, int, int, int);
        sf::Time life;
        int phase = 1;
        sf::Vector2f phase2Scale;
        sf::Vector2f phase3Scale;
};