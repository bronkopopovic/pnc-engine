#ifndef PNC_ENGINE_PATHFINDER_H
#define PNC_ENGINE_PATHFINDER_H

#include <vector>
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Cursor.h"

namespace BRO{

    //-----------------
    // GRAPH-NODES
    //-----------------
    class Node {
    public:
        std::vector<BRO::Node> adjacencyList;

        // parent node represented as integer which will
        // index the corresponding node in the navMesh
        int parent;
        int currentNode;

        float x, y;
        float H, G, F;

        void addAdjacency(Node &node);

        void setCoords(float xCoord, float yCoord);
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
    // PATHFINDER
    //-----------------
    class Pathfinder {
    public:
        int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
        bool doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2);

        // check, if user clicked inside a polygon
        int lineIntersects;
        std::vector<sf::Vector2f> polyEdge;
        int isInsidePolygon(BRO::NavMesh &navMesh, BRO::Player &player, sf::RenderWindow &window, sf::Vector2f checkedPoint);

        // A-star algorithm for polygon preselection
        static float pointToPointDistance(BRO::Node &node1, BRO::Node &node2);
        float calculateF(BRO::Node &node, BRO::Node &adjacentNode, BRO::Node &endNode);

        std::vector<BRO::Node> openList;
        std::vector<BRO::Node> closedList;


        int startNodeI;
        BRO::Node startNode;
        int endNodeI;
        BRO::Node endNode;

        void getNodePath(BRO::NavMesh &navMesh, BRO::Player &player, BRO::Cursor &cursor, sf::RenderWindow &window);
    };
}

#endif //PNC_ENGINE_PATHFINDER_H
