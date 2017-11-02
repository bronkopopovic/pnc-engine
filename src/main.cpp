#include <iostream>
#include "Game.h"

using namespace std;

int main() {

    BRO::Game game;

    static sf::Event event;

    // Set default game resolution
    // 1 = 320x200
    // 2 = 640x400
    // 3 = 960x600
    // 4 = 1280x800
    // 5 = 1600x1000
    // 6 = 1920x1200
    // 7 = 2240x1400
    // 8 = 2560x1600
    // 9 = 2880x1800
    game.setResMultiplier(6);

    game.window.create(sf::VideoMode(320 * game.resMultiplier, 200 * game.resMultiplier, 32), "PNC Engine", sf::Style::Titlebar | sf::Style::Close);
    game.window.setFramerateLimit(60);
    game.window.setMouseCursorVisible(false);
    //BRO::World world;
    //world.initStudioRoom(game.resMultiplier);

    BRO::Cursor cursor;
    cursor.setScale(game.resMultiplier);

    #include "../characters/ch2.conf"
    #include "../characters/ch4.conf"

    ch2.sprite.setPosition(120 * game.resMultiplier, 100 * game.resMultiplier);
    ch2.sprite.setScale(game.resMultiplier, game.resMultiplier);
    ch2.setTarget(sf::Vector2f(120 * game.resMultiplier, 100 * game.resMultiplier));

    ch4.sprite.setPosition(190 * game.resMultiplier, 100 * game.resMultiplier);
    ch4.sprite.setScale(game.resMultiplier, game.resMultiplier);
    ch4.setTarget(sf::Vector2f(190 * game.resMultiplier, 100 * game.resMultiplier));

    BRO::Music track1("track2.ogg");
    track1.audio.setVolume(40);

    BRO::Pathfinder pathfinder;

    #include "../rooms/studio.conf"

    game.currentRoom = &studioRoom;
    game.currentRoom->player = &ch2;
    game.currentRoom->idlePlayers.push_back(&ch4);

    sf::Vertex cursorLine[2];
    cursorLine[0].color = sf::Color(255,255,255);
    cursorLine[1].color = sf::Color(255,255,255);

    while(game.window.isOpen()){
        while(game.window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                game.window.close();
            }
        }

        cursorLine[0].position = sf::Vector2f(game.currentRoom->player->sprite.getPosition().x, 0);
        cursorLine[1].position = cursor.sprite.getPosition();

        track1.loop();

        game.currentRoom->player->animate(game.resMultiplier, game.resMultiplierF);
        for (int i = 0; i < game.currentRoom->idlePlayers.size(); i++){
            game.currentRoom->idlePlayers[i]->animate(game.resMultiplier, game.resMultiplierF);
        }

        cursor.update(game.window.mapPixelToCoords(sf::Mouse::getPosition(game.window)));

        bool clickedInWindow (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            sf::Mouse::getPosition(game.window).x <= game.window.getSize().x &&
            sf::Mouse::getPosition(game.window).y <= game.window.getSize().y &&
            sf::Mouse::getPosition(game.window).x >= 0 &&
            sf::Mouse::getPosition(game.window).y >= 0);

        if(clickedInWindow){
            cout << "click" << endl;
            if (pathfinder.isInsidePolygon(navMesh, *game.currentRoom->player, game.window, cursor.sprite.getPosition()) != -1){
                game.currentRoom->player->setTarget(game.window.mapPixelToCoords(sf::Mouse::getPosition(game.window)));
            }
        }

        game.currentRoom->addDynamicObject(studio_pillar1.sprite);
        game.currentRoom->addDynamicObject(studio_pillar2.sprite);
        game.currentRoom->addDynamicObject(studio_pillar3.sprite);
        game.currentRoom->addDynamicObject(studio_pillar4.sprite);
        game.currentRoom->addDynamicObject(studio_pillar5.sprite);
        game.currentRoom->addDynamicObject(game.currentRoom->player->sprite);
        for (int i = 0; i < game.currentRoom->idlePlayers.size(); i++){
            game.currentRoom->addDynamicObject(game.currentRoom->idlePlayers[i]->sprite);
        }

        game.currentRoom->scrollHorizontal(game.currentRoom->player->sprite.getPosition().x, game.resMultiplier);
        game.currentRoom->view.reset(game.currentRoom->mask);

        game.currentRoom->drawRoom(game.window);

        //game.window.draw(cursorLine, 2, sf::Lines);

        game.currentRoom->drawDynamicObjects(*game.currentRoom, game.window);
        game.window.draw(game.currentRoom->foreground);

        /*for (int i = 0; i < navMesh.polyList.size(); i++){
            game.window.draw(navMesh.polyList[i].shape);
        }*/

        game.window.draw(cursor.sprite);

        game.window.display();
    }
    return 0;
}