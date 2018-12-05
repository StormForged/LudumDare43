#pragma once
#include <SFML/Graphics.hpp>

class HUDObject{
    public:
        sf::Sprite sprite;
        HUDObject(sf::Texture&);
        bool display = false;
};
