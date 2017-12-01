#include <iostream>
#include "Game.h"

using namespace std;

//---------------
// TEST SCENE
//---------------
int main() {

    #include "../configs/game.conf"

    #include "../assets/assets.lib"

    #include "../configs/test_room.conf"

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
        cursorLine[0].position = sf::Vector2f(game.currentPlayer->sprite.getPosition().x, 0);
        cursorLine[1].position = cursor.sprite.getPosition();

        //-------------------------------
        // music loop
        //-------------------------------
        track1.loop();

        //-------------------------------
        // handle room view
        //-------------------------------
        game.currentRoom->scrollHorizontal(game.currentPlayer->sprite.getPosition().x, game.resMultiplier);
        game.currentRoom->view.reset(game.currentRoom->mask);

        //-------------------------------
        // handle animations
        //-------------------------------
        game.currentPlayer->animate(game.resMultiplier, game.resMultiplierF);
        for (int i = 0; i < game.idlePlayers.size(); i++){
            game.idlePlayers[i]->animate(game.resMultiplier, game.resMultiplierF);
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
        if(clickedInWindow){
            game.playerSwitcher();
            if (pathfinder.isInsidePolygon(studio_navMesh, *game.currentPlayer, game.window, cursor.sprite.getPosition()) != -1){
                game.currentPlayer->setTarget(game.window.mapPixelToCoords(sf::Mouse::getPosition(game.window)));
            }
        }

        //-------------------------------
        // draw all the stuff
        //-------------------------------
        game.currentRoom->drawRoom(game.window);

        // cursor line
        //game.window.draw(cursorLine, 2, sf::Lines);

        // navMesh
        /*for (int i = 0; i < navMesh.polyList.size(); i++) {
            game.window.draw(navMesh.polyList[i].shape);
        }*/

        game.currentRoom->drawDynamicObjects(*game.currentRoom, game.window);
        game.window.draw(game.currentRoom->foreground);


        game.window.setView(game.window.getDefaultView());
        hud.drawHud(game.window);

        game.window.setView(game.currentRoom->view);
        game.window.draw(cursor.sprite);


        game.window.display();
    }
    return 0;
}