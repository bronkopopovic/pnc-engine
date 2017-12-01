#ifndef PNR_Engine_GAME_H
#define PNR_Engine_GAME_H

#include "Pathfinder.h"
#include "Cursor.h"
#include "Player.h"
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
        BRO::Hud* currentHud;

        // player switching
        int clickCounter;
        sf::Vector2f mappedCursor;
        void playerSwitcher(BRO::Game &game);

    };

    enum class GameStates{
        STATE_START = 1,
        STATE_MENU,
        STATE_OPTIONS,
        STATE_PLAYING
    };
}

#endif //PNR_Engine_GAME_H