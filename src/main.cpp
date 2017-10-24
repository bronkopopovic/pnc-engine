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
    BRO::Room studioRoom("studio.png", game.resMultiplier);

    BRO::Cursor cursor;
    cursor.setScale(game.resMultiplier);

    //#include "../characters/ch2.conf"
    #include "../characters/ch4.conf"

    player.sprite.setPosition(120 * game.resMultiplier, 120 * game.resMultiplier);
    player.sprite.setScale(game.resMultiplier, game.resMultiplier);
    player.setTarget(sf::Vector2f(120 * game.resMultiplier, 100 * game.resMultiplier));

    BRO::Room currentRoom = studioRoom;
    BRO::Player currentPlayer = player;

    BRO::Music track1("track2.ogg");
    track1.audio.setVolume(40);

    BRO::Pathfinder pathfinder;

    #include "../rooms/studio.conf"

    sf::Vertex cursorLine[2];
    cursorLine[0].color = sf::Color(255,255,255);
    cursorLine[1].color = sf::Color(255,255,255);

    while(game.window.isOpen()){
        while(game.window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                game.window.close();
            }
        }

        cursorLine[0].position = sf::Vector2f(player.sprite.getPosition().x, 0);
        cursorLine[1].position = cursor.sprite.getPosition();

        track1.loop();

        player.animate(game.resMultiplier, game.resMultiplierF);

        cursor.update(game.window.mapPixelToCoords(sf::Mouse::getPosition(game.window)));

        bool clickedInWindow (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            sf::Mouse::getPosition(game.window).x <= game.window.getSize().x &&
            sf::Mouse::getPosition(game.window).y <= game.window.getSize().y &&
            sf::Mouse::getPosition(game.window).x >= 0 &&
            sf::Mouse::getPosition(game.window).y >= 0);

        if(clickedInWindow){
            cout << "click" << endl;
            if (pathfinder.isInsidePolygon(navMesh, player, game.window, cursor.sprite.getPosition()) != -1){
                player.setTarget(game.window.mapPixelToCoords(sf::Mouse::getPosition(game.window)));
            }
        }

        currentRoom.scrollHorizontal(player.sprite.getPosition().x, game.resMultiplier);
        currentRoom.view.reset(currentRoom.mask);

        game.window.clear(sf::Color::Black);

        currentRoom.drawRoom(game.window);

        /*for (int i = 0; i < navMesh.polyList.size(); i++){
            game.window.draw(navMesh.polyList[i].shape);
        }*/

        game.window.draw(player.sprite);
        //game.window.draw(cursorLine, 2, sf::Lines);
        game.window.draw(cursor.sprite);

        game.window.display();
    }
    return 0;
}