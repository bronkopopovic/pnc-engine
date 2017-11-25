#include <iostream>
#include "Game.h"

using namespace std;

//---------------
// TEST SCENE
//---------------
int main() {

    //-------------------------------
    // Basic Setup
    //-------------------------------
    BRO::Game game;

    static sf::Event event;

    // Set default game resolution
    // 1 = 320x200, 2 = 640x400, 3 = 960x600, 4 = 1280x800, 5 = 1600x1000, 6 = 1920x1200, 7 = 2240x1400, 8 = 2560x1600, 9 = 2880x1800
    game.setResMultiplier(6);

    //-------------------------------
    // Window
    //-------------------------------
    game.window.create(sf::VideoMode(320 * game.resMultiplier, 200 * game.resMultiplier, 32), "PNC Engine", sf::Style::Titlebar | sf::Style::Close);
    game.window.setFramerateLimit(60);
    game.window.setMouseCursorVisible(false);
    //BRO::World world;
    //world.initStudioRoom(game.resMultiplier);

    //-------------------------------
    // Cursor
    //-------------------------------
    BRO::Cursor cursor;
    cursor.setScale(game.resMultiplier);

    //-------------------------------
    // Player Configs
    //-------------------------------
    #include "../characters/ch2.conf"
    #include "../characters/ch4.conf"
    #include "../characters/chef.conf"

    //-------------------------------
    // Player Positions
    //-------------------------------
    ch2.sprite.setPosition(120 * game.resMultiplier, 100 * game.resMultiplier);
    ch2.sprite.setScale(game.resMultiplier, game.resMultiplier);
    ch2.setTarget(sf::Vector2f(120 * game.resMultiplier, 100 * game.resMultiplier));

    ch4.sprite.setPosition(190 * game.resMultiplier, 100 * game.resMultiplier);
    ch4.sprite.setScale(game.resMultiplier, game.resMultiplier);
    ch4.setTarget(sf::Vector2f(190 * game.resMultiplier, 100 * game.resMultiplier));

    chef.sprite.setPosition(390 * game.resMultiplier, 100 * game.resMultiplier);
    chef.sprite.setScale(game.resMultiplier, game.resMultiplier);
    chef.setTarget(sf::Vector2f(120 * game.resMultiplier, 100 * game.resMultiplier));

    //-------------------------------
    // Room Conf
    //-------------------------------
    #include "../rooms/studio.conf"

    //-------------------------------
    // Pathfinder
    //-------------------------------
    BRO::Pathfinder pathfinder;

    sf::Vertex cursorLine[2];
    cursorLine[0].color = sf::Color(255,255,255);
    cursorLine[1].color = sf::Color(255,255,255);

    //-------------------------------
    // HUD
    //-------------------------------
    BRO::Hud hud;

    BRO::PlayerIcon ch2Icon("ch2_ico.png", 4, game.window, game.resMultiplier);
    BRO::PlayerIcon ch4Icon("ch4_ico.png", 30, game.window, game.resMultiplier);

    hud.playerIcons.push_back(&ch2Icon);
    hud.playerIcons.push_back(&ch4Icon);

    ch2Icon.setActive(true);
    ch4Icon.setActive(false);

    ch2Icon.linkedPlayer = &ch2;
    ch4Icon.linkedPlayer = &ch4;

    //-------------------------------
    // Music
    //-------------------------------
    BRO::Music track1("track2.ogg");
    track1.audio.setVolume(40);

    //-------------------------------
    // set all the Pointers
    //-------------------------------
    game.currentRoom = &studioRoom;

    game.currentCursor = &cursor;

    game.currentHud = &hud;

    for (int i = 0; i < hud.playerIcons.size(); i++){
        if (hud.playerIcons[i]->isActive){
            game.currentPlayer = hud.playerIcons[i]->linkedPlayer;
        } else {
            game.idlePlayers.push_back(hud.playerIcons[i]->linkedPlayer);
        }
    }

    game.currentRoom->addDynamicObject(chef.sprite);

    game.currentRoom->addDynamicObject(game.currentPlayer->sprite);
    for (int i = 0; i < game.idlePlayers.size(); i++){
        game.currentRoom->addDynamicObject(game.idlePlayers[i]->sprite);
    }

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
            if (pathfinder.isInsidePolygon(navMesh, *game.currentPlayer, game.window, cursor.sprite.getPosition()) != -1){
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