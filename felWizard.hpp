#pragma once
#include "wizard.hpp"
#include "spellsFel.hpp"
#include "hudObject.hpp"
#include "felLab.hpp"
#include <math.h>

class FelWizard : public Wizard{
    public:
        FelWizard(sf::Texture&);
        void Walking(HUDObject&);
        void ReplenishBombs(sf::Time, FelLab*);
        void Casting(sf::Time, std::vector<SpellsFel>&);        
        int felBombs = 0;
        bool felBombClicked = false;
        bool felBombCasting = false;
};