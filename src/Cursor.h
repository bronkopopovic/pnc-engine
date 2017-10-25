#ifndef PNR_Engine_CURSOR_H
#define PNR_Engine_CURSOR_H

#include <SFML/Graphics.hpp>

namespace BRO{
    class Cursor {
    private:
        sf::Texture texture;
    public:
        sf::Sprite sprite;

        Cursor();

        void setScale(int &resMultiplier);

        void update(sf::Vector2f coordinates);

    };
}

#endif //PNR_Engine_CURSOR_H
