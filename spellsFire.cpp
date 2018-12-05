#include "spellsFire.hpp"

SpellsFire::SpellsFire(int r, int g, int b, int a) : Spells(r, g, b, a){
    phase2Scale = sf::Vector2f(area.getScale().x / 2, area.getScale().y / 2);
    phase3Scale = sf::Vector2f(area.getScale().x / 4, area.getScale().y / 4);
}