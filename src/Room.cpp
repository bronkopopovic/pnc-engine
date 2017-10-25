#include "Room.h"

BRO::RoomObject::RoomObject(const std::string filePath, float positionX, float positionY, int originX, int originY,
                            unsigned int &resMultiplier) {
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
    sprite.setOrigin(originX, originY);
    sprite.scale(resMultiplier, resMultiplier);
    sprite.setPosition(positionX, positionY);
}

bool BRO::Room::compareY(const sf::Sprite &sprite1, const sf::Sprite &sprite2) {
    return sprite1.getPosition().y < sprite2.getPosition().y;
}

BRO::Room::Room(const std::string &filePath, unsigned int &resMultiplier){
    mask.left = 0;
    mask.top = 0;
    mask.width = 320 * resMultiplier;
    mask.height = 200 * resMultiplier;
    view.reset(mask);
    texture.loadFromFile(filePath);
    baseLayer.setTexture(texture);
    baseLayer.scale(resMultiplier, resMultiplier);
    //cout << "size is " << texture.getSize().x << endl;
    if (texture.getSize().x != mask.width || texture.getSize().y != mask.height){
        isScrollable = true;
    } else {
        isScrollable = false;
    }
}

void BRO::Room::scrollHorizontal(float playerPositionX, unsigned int &resMultiplier){
    if (isScrollable){
        if (playerPositionX > mask.width + mask.left - 100 * resMultiplier && (texture.getSize().x - 1) * resMultiplier > mask.width + mask.left){
            mask.left += 1.5f * resMultiplier;
        } else if (playerPositionX < mask.left + 100 * resMultiplier && mask.left > 0){
            mask.left -= 1.5f * resMultiplier;
        }
    }
}

void BRO::Room::setNavMesh(const BRO::NavMesh &_navMesh){
    navMesh = _navMesh;
}

void BRO::Room::addDynamicObject(sf::Sprite &sprite) {
    dynamicObjects.push_back(sprite);
}

void BRO::Room::drawRoom(sf::RenderWindow &window){
    window.setView(view);
    window.draw(baseLayer);
}

void BRO::Room::drawDynamicObjects(BRO::Room &room, sf::Sprite &playerSprite, sf::RenderWindow &window, int resMultiplier) {
    std::sort(room.dynamicObjects.begin(), room.dynamicObjects.end(), BRO::Room::compareY);
    for (int i = 0; i < room.dynamicObjects.size(); i++){
        window.draw(room.dynamicObjects.at(i));
    }
    room.dynamicObjects.clear();
}
