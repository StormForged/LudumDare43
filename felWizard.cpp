#include "felWizard.hpp"

FelWizard::FelWizard(sf::Texture& texture) : Wizard(texture){
}

void FelWizard::Walking(HUDObject& felBomb){
    if(moving){
        sprite.move(direction.x, direction.y);
        sf::Vector2i tmpPos;
        tmpPos.x = sprite.getPosition().x - destination.x;
        tmpPos.y = sprite.getPosition().y - destination.y;
        float cDistance = sqrt((tmpPos.x * tmpPos.x) + (tmpPos.y * tmpPos.y));
        if(felBombClicked){
            if(cDistance < 100){
                moving = false;
                felBombClicked = false;
                felBomb.sprite.setColor(sf::Color::White);
                if(felBombs >= 1){
                    felBombCasting = true;
                    felBombs -= 1;
                }
            }
        } 

    if(cDistance < .1)
        moving = false;
    }
}

void FelWizard::ReplenishBombs(sf::Time deltaTime, FelLab* felLab){
    if(sprite.getGlobalBounds().intersects(felLab->sprite.getGlobalBounds())){
        lastTick += deltaTime;
        if(lastTick > sf::seconds(3)){
            if(felLab->felBombs > 0){
                felBombs++;
                felLab->felBombs--;
            }
            lastTick = lastTick - lastTick;
        }
    }
}

void FelWizard::Casting(sf::Time deltaTime, std::vector<SpellsFel>& felSpells){
    if(felBombCasting){
        castTime += deltaTime;
        if(castTime > sf::seconds(1)){
            SpellsFel felSpell(50, 200, 50, 150);
            felSpell.area.setPosition(sf::Vector2f(destination.x, destination.y));
            felSpells.push_back(felSpell);
            felBombCasting = false;
            castTime = castTime - castTime;
        }
    }    
}