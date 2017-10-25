#include "Pathfinder.h"

void BRO::Node::addAdjacency(Node &node) {

    adjacencyList.push_back(node);
}

void BRO::Node::setCoords(float xCoord, float yCoord) {
    x = xCoord;
    y = yCoord;
}

void BRO::Polygon::assign(sf::ConvexShape &_shape, BRO::Node &_node) {
    shape = _shape;
    node = _node;
}

void BRO::NavMesh::addPoly(BRO::Polygon &poly) {
    polyList.push_back(poly);
}

void BRO::NavMesh::addShape(sf::ConvexShape &shape){
    shapeList.push_back(shape);
};

int BRO::Pathfinder::orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
    // See http://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    float val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool BRO::Pathfinder::doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{
    // Find the four orientations
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    return false;
}

int BRO::Pathfinder::isInsidePolygon(BRO::NavMesh &navMesh, BRO::Player &player, sf::RenderWindow &window, sf::Vector2f checkedPoint) {
    lineIntersects = 0;
    for (int i = 0; i <= navMesh.shapeList.size(); i++){
        if (navMesh.shapeList[i].getGlobalBounds().contains(checkedPoint)){
            std::cout << "bounding" << std::endl;
            for (int n = 0; n < navMesh.shapeList[i].getPointCount(); n++){
                polyEdge.push_back(navMesh.shapeList[i].getPoint(n));
                if (n+2 > navMesh.shapeList[i].getPointCount()){
                    polyEdge.push_back(navMesh.shapeList[i].getPoint(0));
                } else {
                    polyEdge.push_back(navMesh.shapeList[i].getPoint(n+1));
                }
                if (BRO::Pathfinder::doIntersect(polyEdge[0], polyEdge[1], sf::Vector2f(player.sprite.getPosition().x,0), checkedPoint)){
                    lineIntersects += 1;
                }
                polyEdge.clear();
            }
            if (lineIntersects == 1){
                std::cout << "You clicked a valid Polygon" << std::endl;
                return i;
            }
        }
    }
    if (lineIntersects != 1){
        return -1;
    }
}

float BRO::Pathfinder::pointToPointDistance(BRO::Node &node1, BRO::Node &node2) {
    return std::sqrt(((node1.x - node2.x)*(node1.x - node2.x)) + ((node1.y - node2.y)*(node1.y - node2.y)));
}

float BRO::Pathfinder::calculateF(BRO::Node &startNode, BRO::Node &adjacentNode, BRO::Node &endNode){
    return pointToPointDistance(adjacentNode, endNode) + pointToPointDistance(startNode, adjacentNode);
}

void BRO::Pathfinder::getNodePath(BRO::NavMesh &navMesh, BRO::Player &player, BRO::Cursor &cursor, sf::RenderWindow &window){

    // Calculate start Node with playerPosition
    startNodeI = isInsidePolygon(navMesh, player, window, player.sprite.getPosition());
    startNode = navMesh.polyList[startNodeI].node;
    endNodeI = isInsidePolygon(navMesh, player, window, cursor.sprite.getPosition());
    endNode = navMesh.polyList[endNodeI].node;

    // Push startNode to open List
    openList.push_back(startNode);

    // Push adjacent Nodes of startNode to open List
    for (int i = 0; i < startNode.adjacencyList.size(); i++){
        openList.push_back(startNode.adjacencyList[i]);
        startNode.adjacencyList[i].parent = startNodeI;
    }

    // remove startNode from open List and push to closed List
    openList.erase(openList.begin());
    closedList.push_back(startNode);

    for (int i = 0; i < openList.size(); i++){
        openList[i].F = calculateF(startNode, openList[i], endNode);
    }
    //closedList.push_back(std::min_element(openList))
}