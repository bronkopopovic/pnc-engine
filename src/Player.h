#ifndef PNR_Engine_PLAYER_H
#define PNR_Engine_PLAYER_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace BRO{

    struct PlayerAnimation {
        int animationID, top, startLeft, maxLeft, incrementLeft;
        float speed;
    };

    class Player {
    private:
        sf::Texture texture;

        void walk(int &resMultiplier, float &resMultiplierF);

        void idle();

    public:
        sf::IntRect mask;
        sf::Sprite sprite;

        sf::Clock clock, moveClock;

        sf::Vector2f moveTarget;
        sf::Vector2f direction;
        bool targetReached;

        std::vector<BRO::PlayerAnimation> spriteSheet;

        float positiveDirectionX, positiveDirectionY;

        Player(const std::string &filePath, int &resMultiplier);

        void addAnimationToSheet(BRO::PlayerAnimation &spriteAnimation);
        BRO::PlayerAnimation getAnimationFromSheet(std::vector<BRO::PlayerAnimation> &spriteSheet, int animationID);

        void iterateSprite(BRO::PlayerAnimation &spriteAnimation);

        void setTarget(sf::Vector2f coordinates);

        void animate(int &resMultiplier, float &resMultiplierF);

        int getPositionX();
    };
}

#endif //PNR_Engine_PLAYER_H