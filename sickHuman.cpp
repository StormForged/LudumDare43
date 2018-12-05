#include "sickHuman.hpp"

SickHuman::SickHuman(sf::Texture& texture) : Human(texture){
    sprite.setTexture(texture);
}