#include "foodGremlin.hpp"
FoodGremlin::FoodGremlin(){};

FoodGremlin::FoodGremlin(sf::Texture& texture){
    sprite.setTexture(texture);
    sprite.setOrigin(8,8);
}