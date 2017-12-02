//
// Created by Roman Hock on 02.11.17.
//

#include "hud.h"

BRO::PlayerIcon::PlayerIcon(std::string texturePath, int y, sf::RenderWindow &window, int &resMultiplier) {
    texture.loadFromFile(texturePath);
    mask.width = 24;
    mask.height = 24;
    isActive = false;
    isVisible = false;
    sprite.setTexture(texture);
    sprite.setTextureRect(mask);
    sprite.setScale(resMultiplier, resMultiplier);
    sprite.setPosition(window.mapPixelToCoords(sf::Vector2i(293 * resMultiplier, y * resMultiplier)));
}

void BRO::PlayerIcon::setVisibility(bool trueFalse) {
    isVisible = trueFalse;
}

void BRO::PlayerIcon::setActive(bool trueFalse) {
    isActive = trueFalse;
    if (trueFalse){
        mask.left = 0;
        sprite.setTextureRect(mask);
    } else {
        mask.left = 24;
        sprite.setTextureRect(mask);
    }
}

void BRO::Hud::init(){
    loaded = true;

}

void BRO::Hud::drawHud(sf::RenderWindow &window) {
    if (loaded){
        for (int i = 0; i < playerIcons.size(); i++){
            window.draw(playerIcons[i]->sprite);
        }
    }
}