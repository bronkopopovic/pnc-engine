#ifndef PNR_Engine_PLAYER_H
#define PNR_Engine_PLAYER_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace BRO{
    class PlayerAnimation {
    public:
        int animationID;
        int top;
        int startLeft;
        int maxLeft;
        int incrementLeft;
        float speed;
    };

    class Player {
    private:
        sf::Texture texture;

    public:
        sf::IntRect mask;

        sf::Sprite sprite;
        sf::Clock clock;
        sf::Vector2f moveTarget;
        sf::Clock moveClock;

        std::vector<BRO::PlayerAnimation> spriteSheet;

        float positiveDirectionX;
        float positiveDirectionY;

        Player(const std::string &filePath, unsigned int &resMultiplier);

        void addAnimationToSheet(BRO::PlayerAnimation &spriteAnimation);
        BRO::PlayerAnimation getAnimationFromSheet(std::vector<BRO::PlayerAnimation> &spriteSheet, int animationID);

        void iterateSprite(BRO::PlayerAnimation &spriteAnimation);

        void setTarget(sf::Vector2f coordinates);

        void walk(unsigned int &resMultiplier, float &resMultiplierF, std::vector<BRO::PlayerAnimation> &spriteSheet);

        void idle();

        void animate(unsigned int &resMultiplier, float &resMultiplierF);

        int getPositionX();
    };
}

#endif //PNR_Engine_PLAYER_H