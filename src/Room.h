#ifndef PNR_Engine_ROOM_H
#define PNR_Engine_ROOM_H

#include <SFML/Graphics.hpp>
#include "Pathfinder.h"

namespace BRO{
    class RoomObject{
    private:
        sf::Texture texture;

    public:
        sf::Sprite sprite;
        RoomObject(const std::string filePath, float positionX, float positionY, int originX, int originY, unsigned int &resMultiplier);
    };

    class Room{
    private:
        sf::Texture texture;
        bool isScrollable;

    public:
        sf::View view;
        sf::FloatRect mask;

        sf::Sprite baseLayer;
        std::vector<sf::Sprite> objects;
        sf::Sprite foreground1;
        sf::Sprite foreground2;

        BRO::NavMesh navMesh;

        std::vector<sf::Sprite> dynamicObjects;
        static bool compareY(const sf::Sprite &sprite1, const sf::Sprite &sprite2);

        // constructor
        Room(const std::string &filePath, unsigned int &resMultiplier);

        void scrollHorizontal(float playerPositionX, unsigned int &resMultiplier);

        void setNavMesh(const BRO::NavMesh &_navMesh);

        void addDynamicObject(sf::Sprite &sprite);

        void drawRoom(sf::RenderWindow &window);

        void drawDynamicObjects(BRO::Room &room, sf::RenderWindow &window);
    };
}

#endif //PNR_Engine_ROOM_H
