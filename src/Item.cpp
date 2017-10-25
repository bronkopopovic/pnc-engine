#include "Item.h"

BRO::Item::Item(const std::string filePath, float positionX, float positionY, int &resMultiplier){
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
    sprite.scale(resMultiplier, resMultiplier);
    sprite.setPosition(positionX, positionY);
}