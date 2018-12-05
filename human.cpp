#include "human.hpp"

Human::Human(sf::Texture& texture){
    sprite.setTexture(texture);
    sprite.setOrigin(8,8);
}