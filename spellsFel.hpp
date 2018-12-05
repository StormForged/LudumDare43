#pragma once
#include "spells.hpp"

class SpellsFel : public Spells{
    public:
        SpellsFel(int, int, int, int);
        sf::Time life;
};