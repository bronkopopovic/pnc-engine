#include "Cursor.h"

BRO::Cursor::Cursor(){
    texture.loadFromFile("cursor.png");
    sprite.setTexture(texture);
    sprite.setOrigin(8, 8);
    sprite.setPosition(400, 400);
}

void BRO::Cursor::setScale(int &resMultiplier){
    sprite.setScale(resMultiplier, resMultiplier);
}

void BRO::Cursor::update(sf::Vector2f coordinates){
    sprite.setPosition(coordinates);
}