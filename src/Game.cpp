#include "Game.h"

void BRO::Game::setResMultiplier(int multiplier) {
    resMultiplier = multiplier;
    resMultiplierF = resMultiplier;
}

void BRO::Game::playerSwitcher() {
    hitCounter = 0;
    idlePlayers.clear();
    float x, y;
    x = currentCursor->sprite.getPosition().x - currentRoom->mask.left;
    y = currentCursor->sprite.getPosition().y - currentRoom->mask.top;
    for (int i = 0; i < currentHud->playerIcons.size(); i++){
        if ( currentHud->playerIcons[i]->sprite.getGlobalBounds().contains(sf::Vector2f(x,y)) ){
            hitCounter++;
        }
    }
    for (int i = 0; i < currentHud->playerIcons.size(); i++){
        if ( currentHud->playerIcons[i]->sprite.getGlobalBounds().contains(sf::Vector2f(x,y)) ||
                (!(currentHud->playerIcons[i]->sprite.getGlobalBounds().contains(sf::Vector2f(x,y))) &&
                 currentHud->playerIcons[i]->isActive && hitCounter == 0) )
        {
            currentHud->playerIcons[i]->setActive(true);
            currentPlayer = currentHud->playerIcons[i]->linkedPlayer;
        } else {
            idlePlayers.push_back(currentHud->playerIcons[i]->linkedPlayer);
            currentHud->playerIcons[i]->setActive(false);
        }
    }
}