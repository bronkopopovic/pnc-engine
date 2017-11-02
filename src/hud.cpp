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

    iconPoly.setPointCount(4);
    iconPoly.setPoint(0, sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
    iconPoly.setPoint(1, sf::Vector2f(sprite.getPosition().x + (24 * resMultiplier), sprite.getPosition().y));
    iconPoly.setPoint(2, sf::Vector2f(sprite.getPosition().x + (24 * resMultiplier), sprite.getPosition().y + (24 * resMultiplier)));
    iconPoly.setPoint(3, sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + (24 * resMultiplier)));
    iconPoly.setFillColor(sf::Color(0,255,255,1));
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

void BRO::Hud::drawHud(sf::RenderWindow &window) {
    for (int i = 0; i < playerIcons.size(); i++){
        window.draw(playerIcons[i]->sprite);
    }
}