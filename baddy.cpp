#include "baddy.hpp"

Baddy::Baddy(sf::Texture& texture){
    sprite.setTexture(texture);
    sprite.setOrigin(8,8);
}