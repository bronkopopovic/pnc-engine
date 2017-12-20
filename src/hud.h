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

        sf::Font menuFont;

        void init(sf::RenderWindow &window, int resMultiplier);

        std::vector<BRO::PlayerIcon*> playerIcons;

        // black box for bottom HUD
        struct bottom{
            int width;
            int height;
            sf::RectangleShape background;
        } bottom;

        // Verbs
        struct verb{
            sf::Text text;
        } give, open, close, pickUp, talkTo, lookAt, use, push, pull;

        std::vector<BRO::Hud::verb*> allVerbs;

        // info line to show mouse over and verbs stuff
        struct mouseOver{
            sf::Text text;
        } mouseOver;

        std::string fullMouseOver;
        int hovC, selC = 0;

        std::string selectedVerb;
        std::string hoveredVerb;

        std::string constMouseOver();

        void drawHud(sf::RenderWindow &window, sf::Vector2f &mappedCursor);
    };
}

#endif //PNC_ENGINE_HUD_H