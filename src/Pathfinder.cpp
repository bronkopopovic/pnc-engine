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

bool BRO::Pathfinder::CCW(const std::vector<sf::Vector2f>& points){
    if (points.size() != 3)
        return false;

    return (points[2].y - points[0].y) * (points[1].x - points[0].x) > (points[1].y - points[0].y) * (points[2].x - points[0].x);
}

bool BRO::Pathfinder::doLinesIntersect(const std::vector<std::vector<sf::Vector2f>>& lines)
{
    if (lines.size() != 2)
        return false;
    if ((lines[0].size() != 2) || (lines[1].size() != 2))
        return false;

    return	(CCW({ lines[0][0], lines[1][0], lines[1][1] }) != CCW({ lines[0][1], lines[1][0], lines[1][1] })) &&
              (CCW({ lines[0][0], lines[0][1], lines[1][0] }) != CCW({ lines[0][0], lines[0][1], lines[1][1] }));
}

void BRO::Pathfinder::validPolygon(BRO::NavMesh &navMesh, BRO::Player &player, BRO::Cursor &cursor) {

    for (int i = 0; i < navMesh.shapeList.size(); i++){
        int lineCrosses = 0;
        std::vector<sf::Vector2f> line;
        std::vector<sf::Vector2f> playerCursorLine;
        std::vector<std::vector<sf::Vector2f>> lines;
        if (navMesh.shapeList[i].getGlobalBounds().contains(cursor.sprite.getPosition())){
            //bool validPoly = false;
            for (int n = 1; n < navMesh.shapeList[i].getPointCount(); n++){
                line.push_back(navMesh.shapeList[i].getPoint(n));
                line.push_back(navMesh.shapeList[i].getPoint(n+1));
                playerCursorLine.push_back(sf::Vector2f(0,0));
                playerCursorLine.push_back(cursor.sprite.getPosition());
                lines.push_back(line);
                lines.push_back(playerCursorLine);
                if (BRO::Pathfinder::doLinesIntersect(lines)){
                    lineCrosses += 1;
                }
                line.clear();
                playerCursorLine.clear();
                lines.clear();
            }
            if (lineCrosses == 1){
                std::cout << "You clicked a valid Polygon" << std::endl;
            }
        }
    }

}