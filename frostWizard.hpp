#pragma once
#include "wizard.hpp"
#include "spellsFreeze.hpp"
#include "hudObject.hpp"
#include "sacrificeCircle.hpp"
#include <math.h>

class FrostWizard : public Wizard{
    public:
        FrostWizard(sf::Texture&);        
        void Walking(HUDObject&);
        void ReplenishMana(sf::Time, SacrificeCircle*);
        void Casting(sf::Time, std::vector<SpellsFreeze>&);
        int mana = 0;
        bool freezeClicked = false;
        bool freezeCasting = false;
};