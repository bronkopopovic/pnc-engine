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
        sf::IntRect mask;
        PlayerIcon(std::string texturePath, int y, sf::RenderWindow &window, int &resMultiplier);

        void setVisibility(bool trueFalse);
        void setActive(bool trueFalse);

        BRO::Player* linkedPlayer;
    };

    class Hud {
    public:

        bool loaded;

        void init();


        std::vector<BRO::PlayerIcon*> playerIcons;

        void drawHud(sf::RenderWindow &window);
    };
}

#endif //PNC_ENGINE_HUD_H