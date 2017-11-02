#ifndef PNR_Engine_GAME_H
#define PNR_Engine_GAME_H

#include "Pathfinder.h"
#include "Cursor.h"
//#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Music.h"
#include "hud.h"

namespace BRO{
    class Game {
    public:
        int resMultiplier;
        float resMultiplierF;

        sf::RenderWindow window;

        void setResMultiplier(int multiplier);

        // pointers
        BRO::Room* currentRoom;
        BRO::Cursor* currentCursor;

        // player switching
        void playerSwitcher(BRO::Game &game, BRO::Hud &hud);

    };

    enum class GameStates{
        STATE_START = 1,
        STATE_MENU,
        STATE_OPTIONS,
        STATE_PLAYING
    };
}

#endif //PNR_Engine_GAME_H