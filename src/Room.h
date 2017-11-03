#ifndef PNR_Engine_ROOM_H
#define PNR_Engine_ROOM_H

#include <SFML/Graphics.hpp>
#include "Pathfinder.h"

namespace BRO{
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
    // ROOMS
    //--------------------
    class Room{
    private:
        sf::Texture baseLayerTexture;
        sf::Texture foregroundTexture;
        bool isScrollable;

    public:
        sf::View view;
        sf::FloatRect mask;

        // textures and objects
        sf::Sprite baseLayer;
        sf::Sprite foreground;
        std::vector<sf::Sprite*> dynamicObjects;

        // idle player pointers
        std::vector<BRO::Player*> idlePlayers;

        // Nav Mesh stuff
        BRO::NavMesh navMesh;
        static bool compareY(const sf::Sprite *sprite1, const sf::Sprite *sprite2);

        // constructor
        Room(const std::string &baseLayerTexturePath, const std::string &foregroundTexturePath, int &resMultiplier);

        void scrollHorizontal(float playerPositionX, int &resMultiplier);

        void setNavMesh(const BRO::NavMesh &_navMesh);

        void addDynamicObject(sf::Sprite &sprite);

        void drawRoom(sf::RenderWindow &window);

        void drawDynamicObjects(BRO::Room &room, sf::RenderWindow &window);
    };
}

#endif //PNR_Engine_ROOM_H
