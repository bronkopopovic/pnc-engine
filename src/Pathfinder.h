#ifndef PNC_ENGINE_PATHFINDER_H
#define PNC_ENGINE_PATHFINDER_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Cursor.h"

namespace BRO{

    //-----------------
    // GRAPH-NODES
    //-----------------
    class Node {
    public:
        std::vector<Node> adjacencyList;

        void addAdjacent(const Node &node);
    };

    //-------------------------
    // POLYGONS (shape + node)
    //-------------------------
    class Polygon {
    public:
        sf::ConvexShape shape;
        BRO::Node node;

        void assign(sf::ConvexShape &_shape, BRO::Node &_node);
    };

    //-----------------
    // NAV-MESH
    //-----------------
    class NavMesh {
    public:
        std::vector<BRO::Polygon> polyList;
        std::vector<sf::ConvexShape> shapeList;

        void addPoly(BRO::Polygon &poly);
        void addShape(sf::ConvexShape &shape);
    };

    //-----------------
    // LINES etc
    //-----------------
    class Pathfinder {
    public:
        bool CCW(const std::vector<sf::Vector2f>& points);

        // vector of (2) lines. line is a vector of (2) vector2fs (the points of the line).
        // i.e. { { line1.x, line.y }, { line2.x, line2.y } }
        bool doLinesIntersect(const std::vector<std::vector<sf::Vector2f>>& lines);

        int lineIntersects;
        std::vector<sf::Vector2f> polyEdge;
        std::vector<sf::Vector2f> playerCursorLine;
        std::vector<std::vector<sf::Vector2f>> lines;
        bool validPolygon(BRO::NavMesh &navMesh, BRO::Player &player, BRO::Cursor &cursor, sf::RenderWindow &window);
    };
}

#endif //PNC_ENGINE_PATHFINDER_H
