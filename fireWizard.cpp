#include "fireWizard.hpp"

FireWizard::FireWizard(sf::Texture& texture) : Wizard(texture){
}

void FireWizard::Walking(HUDObject& flame){
    if(moving){
        sprite.move(direction.x, direction.y);
        sf::Vector2i tmpPos;
        tmpPos.x = sprite.getPosition().x - destination.x;
        tmpPos.y = sprite.getPosition().y - destination.y;
        float cDistance = sqrt((tmpPos.x * tmpPos.x) + (tmpPos.y * tmpPos.y));
        if(fireClicked){
            if(cDistance < 100){
                moving = false;
                fireClicked = false;
                flame.sprite.setColor(sf::Color::White);
                if(mana >= 5){
                    fireCasting = true;
                    mana -= 5;
                }
            }
        }                
        if(cDistance < .1)
            moving = false;
        }    
}

void FireWizard::Casting(sf::Time deltaTime, std::vector<SpellsFire>& fireSpells){
    if(fireCasting){
        castTime += deltaTime;
        if(castTime > sf::seconds(2)){
            SpellsFire fireSpell(200, 100, 20, 150);
            fireSpell.area.setPosition(sf::Vector2f(destination.x, destination.y));
            fireSpells.push_back(fireSpell);                
            fireCasting = false;
            castTime = castTime - castTime;
        }
    }
}

void FireWizard::ReplenishMana(sf::Time deltaTime, SacrificeCircle* sacrificeCircle){
    if(sprite.getGlobalBounds().intersects(sacrificeCircle->sprite.getGlobalBounds())){
        lastTick += deltaTime;
        if(lastTick > sf::seconds(2)){
            if(sacrificeCircle->mana > 0){
                mana++;
                sacrificeCircle->mana--;
            }
            lastTick = lastTick - lastTick;
        }
    }
}