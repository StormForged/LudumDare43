#include "spells.hpp"

Spells::Spells(int r, int g, int b, int a){
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    area.setPointCount(6);
    area.setPoint(0, sf::Vector2f(0, 0));
    area.setPoint(1, sf::Vector2f(100, 50));
    area.setPoint(2, sf::Vector2f(100, 100));
    area.setPoint(3, sf::Vector2f(0, 150));
    area.setPoint(4, sf::Vector2f(-100, 100));
    area.setPoint(5, sf::Vector2f(-100, 50));
    area.setFillColor(color);
    area.setOrigin(sf::Vector2f(0, 75));
}