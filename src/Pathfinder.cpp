#include "Pathfinder.h"

void BRO::Node::addAdjacent(const Node &node) {
    adjacencyList.push_back(node);
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

bool BRO::Pathfinder::validPolygon(BRO::NavMesh &navMesh, BRO::Player &player, BRO::Cursor &cursor, sf::RenderWindow &window) {
    lineIntersects = 0;
    for (int i = 0; i < navMesh.shapeList.size(); i++){
        if (navMesh.shapeList[i].getGlobalBounds().contains(cursor.sprite.getPosition())){
            for (int n = 0; n < navMesh.shapeList[i].getPointCount(); n++){
                polyEdge.push_back(navMesh.shapeList[i].getPoint(n));
                polyEdge.push_back(navMesh.shapeList[i].getPoint(n+1));
                if (BRO::Pathfinder::doIntersect(polyEdge[0], polyEdge[1], sf::Vector2f(0,0), cursor.sprite.getPosition())){
                    lineIntersects += 1;
                }
                polyEdge.clear();
            }
            if (lineIntersects == 1){
                std::cout << "You clicked a valid Polygon" << std::endl;
                return true;
            }
        }
    }
    if (lineIntersects != 1){
        return false;
    }
}