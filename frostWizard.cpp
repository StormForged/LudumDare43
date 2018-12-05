#include "frostWizard.hpp"

FrostWizard::FrostWizard(sf::Texture& texture) : Wizard(texture){
}

void FrostWizard::Walking(HUDObject& freeze){
    if(moving){
        sprite.move(direction.x, direction.y);
        sf::Vector2i tmpPos;
        tmpPos.x = sprite.getPosition().x - destination.x;
        tmpPos.y = sprite.getPosition().y - destination.y;
        float cDistance = sqrt((tmpPos.x * tmpPos.x) + (tmpPos.y * tmpPos.y));
        if(freezeClicked){
            if(cDistance < .1){
                moving = false;
                freezeClicked = false;
                freeze.sprite.setColor(sf::Color::White);
                if(mana >= 6){
                    freezeCasting = true;
                    mana -= 6;
                }
            }
        }                
        if(cDistance < .1)
            moving = false;
    }
}

void FrostWizard::ReplenishMana(sf::Time deltaTime, SacrificeCircle* sacrificeCircle){
    if(sprite.getGlobalBounds().intersects(sacrificeCircle->sprite.getGlobalBounds())){
        lastTick += deltaTime;
        if(lastTick > sf::seconds(1)){
            if(sacrificeCircle->mana > 0){
                mana++;
                sacrificeCircle->mana--;
            }
            lastTick = lastTick - lastTick;
        }
    }
}

void FrostWizard::Casting(sf::Time deltaTime, std::vector<SpellsFreeze>& freezeSpells){
    if(freezeCasting){
        castTime += deltaTime;
        if(castTime > sf::seconds(2)){
            SpellsFreeze freezeSpell(25, 100, 200, 50);
            freezeSpell.area.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
            freezeSpells.push_back(freezeSpell);
            freezeCasting = false;
            castTime = castTime - castTime;
        } 
    }
}