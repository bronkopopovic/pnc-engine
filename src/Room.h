#ifndef PNR_Engine_ROOM_H
#define PNR_Engine_ROOM_H

#include <SFML/Graphics.hpp>
#include "Pathfinder.h"
#include "Player.h"
#include "Item.h"

namespace BRO{

    class Room; // forward declaration for use in class Door

    //--------------------
    // ROOM OBJECTS
    //--------------------
    class RoomObject{
    private:
        sf::Texture texture;

    public:
        sf::Sprite sprite;
        RoomObject(const std::string filePath, float positionX, float positionY, int originX, int originY, int &resMultiplier);
    };


    //--------------------
    // DOORS
    //--------------------
    class Door{
    private:
        sf::Texture texture;

    public:

        sf::Image image;
        sf::Sprite sprite;
        sf::IntRect mask;

        BRO::Room* connectedRoom;

        bool opened;

        Door(const std::string &texturePath, float positionX, float positionY, int &resMultiplier, BRO::Room &connectedRoom);
        void open();
        void close();
    };


    //--------------------
    // ROOMS
    //--------------------
    class Room{
    private:
        sf::Texture baseLayerTexture;
        sf::Texture foregroundTexture;
        bool isScrollable;

        void drawDynamicObjects(sf::RenderWindow &window);

        void scrollHorizontal(int &resMultiplier);

    public:
        // constructor
        Room(const std::string &baseLayerTexturePath, const std::string &foregroundTexturePath, int &resMultiplier);
        Room(const std::string &baseLayerTexturePath, int &resMultiplier);

        sf::View view;
        sf::FloatRect mask;

        // textures and objects
        sf::Sprite baseLayer;
        sf::Sprite foreground;

        // Doors and Objects
        std::vector<BRO::Door*> doors;
        std::vector<sf::Sprite*> dynamicObjects;

        // Pointers
        std::vector<Item*> items;
        BRO::Player* currentPlayer;

        std::vector<BRO::Player*> idlePlayers;
        // Nav Mesh stuff
        BRO::NavMesh* linkedNavMesh;

        static bool compareY(const sf::Sprite *sprite1, const sf::Sprite *sprite2);

        void setNavMesh(BRO::NavMesh &navMesh);

        void addDynamicObject(sf::Sprite &sprite);

        void addDoor(BRO::Door &door);

        void drawRoom(sf::RenderWindow &window, int &resMultiplier);
    };
}

#endif //PNR_Engine_ROOM_H