#ifndef PNR_Engine_GAME_H
#define PNR_Engine_GAME_H

#include "Pathfinder.h"
#include "Cursor.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Music.h"

namespace BRO{
    class Game {
    public:
        unsigned int resMultiplier;
        float resMultiplierF;

        sf::RenderWindow window;

        void setResMultiplier(unsigned int multiplier);

    };

    enum class GameStates{
        STATE_START = 1,
        STATE_MENU,
        STATE_OPTIONS,
        STATE_PLAYING
    };
}

#endif //PNR_Engine_GAME_H