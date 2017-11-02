//
// Created by Roman Hock on 02.11.17.
//

#ifndef PNC_ENGINE_HUD_H
#define PNC_ENGINE_HUD_H

#include <SFML/Graphics.hpp>
#include "Player.h"

namespace BRO{

    class PlayerIcon{
    public:
        bool isVisible, isActive;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::FloatRect maskF;
        sf::IntRect mask;
        sf::ConvexShape iconPoly;
        PlayerIcon(std::string texturePath, int y, sf::RenderWindow &window, int &resMultiplier);

        void setVisibility(bool trueFalse);
        void setActive(bool trueFalse);

        BRO::Player* linkedPlayer;
    };

    class Hud {
    public:
        std::vector<BRO::PlayerIcon*> playerIcons;

        void drawHud(sf::RenderWindow &window);
    };
}


#endif //PNC_ENGINE_HUD_H
