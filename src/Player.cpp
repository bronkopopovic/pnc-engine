#include "Player.h"

//---------------------------
// Constructor
//---------------------------
BRO::Player::Player(const std::string &filePath, unsigned int &resMultiplier){
    mask.left = 0;
    mask.top = 0;
    mask.width = 64;
    mask.height = 80;
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
    sprite.setTextureRect(mask);
    sprite.setOrigin(32, 77);

    // scale sprite based on y-axis,
    // where y = 100 * game.resMultiplier results in a scale of 1 * game.resMultiplier
    sprite.setScale(0.01f * (sprite.getPosition().y / resMultiplier) * resMultiplier,
                    0.01f * (sprite.getPosition().y / resMultiplier) * resMultiplier);
}

//------------------------------------
// Sprite Animation System
//------------------------------------
void BRO::Player::addAnimationToSheet(BRO::PlayerAnimation &spriteAnimation) {
    spriteSheet.push_back(spriteAnimation);
}

BRO::PlayerAnimation BRO::Player::getAnimationFromSheet(std::vector<BRO::PlayerAnimation> &spriteSheet, int animationID) {
    for (int i = 0; i < spriteSheet.size(); i++){
        if (spriteSheet[i].animationID == animationID){
            return spriteSheet[i];
        }
    }
}

void BRO::Player:: iterateSprite(BRO::PlayerAnimation &playerAnimation){
    mask.top = playerAnimation.top;
    if (clock.getElapsedTime().asSeconds() > playerAnimation.speed){
        if (mask.left >= playerAnimation.maxLeft) {
            mask.left = playerAnimation.startLeft;
        }
        else {
            mask.left += playerAnimation.incrementLeft;
        }
        sprite.setTextureRect(mask);
        clock.restart();
    }
}

//---------------------------
// set Target
//---------------------------
void BRO::Player:: setTarget(sf::Vector2f coordinates){
    moveTarget = coordinates;
}

//----------------------------------------------
// walk-animations + sprite movement
//----------------------------------------------
void BRO::Player:: walk(unsigned int &resMultiplier, float &resMultiplierF, std::vector<BRO::PlayerAnimation> &spriteSheet){
    if (moveClock.getElapsedTime().asMilliseconds() > 10){
        sf::Vector2f direction = sf::Vector2f(moveTarget.x, moveTarget.y) - sprite.getPosition();
        float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
        sf::Vector2f unitVector((direction.x * 1.6f) / magnitude, direction.y / (magnitude * 1.6f));

        // player-movement
        sprite.move(unitVector * (sprite.getPosition().y / (resMultiplier * 130)) * resMultiplierF);

        // scale player based on y-axis
        sprite.setScale((0.01f * (sprite.getPosition().y / resMultiplier) * 0.999f) * resMultiplier,
                        (0.01f * (sprite.getPosition().y / resMultiplier) * 0.999f) * resMultiplier);

        // direction stuff
        if (direction.x < 0){
            positiveDirectionX = - direction.x;
        } else {
            positiveDirectionX = direction.x;
        }
        if (direction.y < 0){
            positiveDirectionY = - direction.y;
        } else {
            positiveDirectionY = direction.y;
        }

        // walk left
        if (direction.x < 0 && positiveDirectionX > positiveDirectionY){
            iterateSprite(spriteSheet[1]);
        }
            // walk right
        else if (direction.x > 0 && positiveDirectionX > positiveDirectionY){
            iterateSprite(spriteSheet[2]);
        }
            // walk front
        else if (positiveDirectionX < positiveDirectionY && direction.y > 0){
            iterateSprite(spriteSheet[3]);
        }
            // walk back
        else if (positiveDirectionX < positiveDirectionY && direction.y < 0){
            iterateSprite(spriteSheet[4]);
        }
        moveClock.restart();
    }
}

//---------------------------
// idle animation
//---------------------------
void BRO::Player::idle(){
    iterateSprite(spriteSheet[0]);
}

//------------------------------------
// handling all animations
//------------------------------------
void BRO::Player:: animate(unsigned int &resMultiplier, float &resMultiplierF){
    bool targetReached {round(moveTarget.x) + 1  > round(sprite.getPosition().x) - 1 &&
            round(moveTarget.x) - 1 < round(sprite.getPosition().x) + 1 &&
            round(moveTarget.y) + 1  > round(sprite.getPosition().y) - 1 &&
            round(moveTarget.y) - 1 < round(sprite.getPosition().y) + 1};

    if (! targetReached){
        walk(resMultiplier, resMultiplierF, spriteSheet);
    } else {
        idle();
    }
}

//-----------------------------
// get X-Coordinate
//-----------------------------
int BRO::Player::getPositionX(){
    float posF = sprite.getPosition().x;
    int posI = floor((posF * 100.0) + 0.5) / 100;
    return posI;
}