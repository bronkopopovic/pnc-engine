#include <iostream>
#include "Game.h"

using namespace std;

int main() {

    //---------------
    // TEST SCENE
    //---------------

    #include "../configs/game.conf"

    #include "../assets/assets.lib"

    #include "../configs/test_room.conf"

    BRO::Door door1("studio_door1.png", 529, 161, game.resMultiplier, testRoom);
    studioRoom.addDoor(door1);

    //-------------------------------
    // Game LOOOOOOOOP
    //-------------------------------
    while(game.window.isOpen()){
        //-------------------------------
        // Close button closes game
        //-------------------------------
        while(game.window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                game.window.close();
            }
        }

        //-------------------------------
        // set cursor-line points
        //-------------------------------
        cursorLine[0].position = sf::Vector2f(game.currentRoom->currentPlayer->sprite.getPosition().x, 0);
        cursorLine[1].position = cursor.sprite.getPosition();

        //-------------------------------
        // music loop
        //-------------------------------
        track1.loop();

        //-------------------------------
        // handle room view
        //-------------------------------
        game.currentRoom->view.reset(game.currentRoom->mask);

        //-------------------------------
        // handle animations
        //-------------------------------
        game.currentRoom->currentPlayer->animate(game.resMultiplier, game.resMultiplierF);
        for (int i = 0; i < game.currentRoom->idlePlayers.size(); i++){
            game.currentRoom->idlePlayers[i]->animate(game.resMultiplier, game.resMultiplierF);
        }

        //-------------------------------
        // handle cursor
        //-------------------------------
        cursor.update(game.window.mapPixelToCoords(sf::Mouse::getPosition(game.window)));

        bool clickedInWindow (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            sf::Mouse::getPosition(game.window).x <= game.window.getSize().x &&
            sf::Mouse::getPosition(game.window).y <= game.window.getSize().y &&
            sf::Mouse::getPosition(game.window).x >= 0 &&
            sf::Mouse::getPosition(game.window).y >= 0);

        //-------------------------------
        // Click Events
        //-------------------------------
        game.mapCursor(game);

        if(clickedInWindow){
            // game.clicked = was some action performed on click? Initial value = false
            game.clickAction = false;
            game.playerSwitcher(game);

            // TO-DO: remove hard-coded stuff (studio_navMesh, cursor.sprite.getPos...)
            if (! game.clickAction){
                if (pathfinder.isInsidePolygon(corridor_studio_navMesh, *game.currentRoom->currentPlayer, game.window, cursor.sprite.getPosition()) != -1){
                    game.currentRoom->currentPlayer->setTarget(game.window.mapPixelToCoords(sf::Mouse::getPosition(game.window)));
                    game.clickAction = true;
                }
            }
        }

        //-------------------------------
        // draw all the stuff
        //-------------------------------

        game.currentRoom->drawRoom(game.window, game.resMultiplier);

        game.window.draw(game.currentRoom->foreground);

        game.window.setView(game.window.getDefaultView());

        hud.drawHud(game.window, game.mappedCursor);

        game.window.setView(game.currentRoom->view);
        game.window.draw(cursor.sprite);

        // cursor line
        //game.window.draw(cursorLine, 2, sf::Lines);

        // navMesh
        /*for (int i = 0; i < navMesh.polyList.size(); i++) {
            game.window.draw(navMesh.polyList[i].shape);
        }*/

        game.window.display();
    }
    return 0;
}