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
        int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
        bool doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2);

        int lineIntersects;
        std::vector<sf::Vector2f> polyEdge;
        bool validPolygon(BRO::NavMesh &navMesh, BRO::Player &player, BRO::Cursor &cursor, sf::RenderWindow &window);
    };
}

#endif //PNC_ENGINE_PATHFINDER_H
