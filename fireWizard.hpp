#pragma once
#include "wizard.hpp"
#include "hudObject.hpp"
#include "sacrificeCircle.hpp"
#include "spellsFire.hpp"
#include <math.h>

class FireWizard : public Wizard{
    public:
        FireWizard(sf::Texture&);
        void Walking(HUDObject&);
        void ReplenishMana(sf::Time, SacrificeCircle*);
        void Casting(sf::Time, std::vector<SpellsFire>&);
        int mana = 0;
        bool fireClicked = false;
        bool fireCasting = false;
};
