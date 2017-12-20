#include "Room.h"

BRO::RoomObject::RoomObject(const std::string filePath, float positionX, float positionY, int originX, int originY,
                            int &resMultiplier) {
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
    sprite.setOrigin(originX, originY);
    sprite.scale(resMultiplier, resMultiplier);
    sprite.setPosition(positionX, positionY);
}

BRO::Door::Door(const std::string &texturePath, float positionX, float positionY, int &resMultiplier, BRO::Room &connectedRoom) {
    image.loadFromFile(texturePath);
    texture.loadFromImage(image);
    mask.width = texture.getSize().x / 2;
    mask.height = texture.getSize().y;
    mask.left = 0;
    sprite.setTexture(texture);
    sprite.setTextureRect(mask);
    sprite.setOrigin(0, texture.getSize().y);
    sprite.scale(resMultiplier, resMultiplier);
    sprite.setPosition(positionX * resMultiplier, positionY * resMultiplier);
    opened = false;
}

void BRO::Room::addDoor(BRO::Door &door) {
    doors.push_back(&door);
}

void BRO::Door::open() {
    opened = true;
    mask.left = 0;
}

void BRO::Door::close() {
    opened = false;
    mask.left = texture.getSize().x / 2;
}

bool BRO::Room::compareY(const sf::Sprite *sprite1, const sf::Sprite *sprite2) {
    return sprite1->getPosition().y < sprite2->getPosition().y;
}

BRO::Room::Room(const std::string &baseLayerTexturePath, const std::string &foregroundTexturePath, int &resMultiplier){
    mask.left = 0;
    mask.top = 0;
    mask.width = 320 * resMultiplier;
    mask.height = 200 * resMultiplier;
    view.reset(mask);
    baseLayerTexture.loadFromFile(baseLayerTexturePath);
    baseLayer.setTexture(baseLayerTexture);
    baseLayer.scale(resMultiplier, resMultiplier);
    foregroundTexture.loadFromFile(foregroundTexturePath);
    foreground.setTexture(foregroundTexture);
    foreground.setScale(resMultiplier, resMultiplier);
    //cout << "size is " << texture.getSize().x << endl;
    if (baseLayerTexture.getSize().x != mask.width || baseLayerTexture.getSize().y != mask.height){
        isScrollable = true;
    } else {
        isScrollable = false;
    }
}
BRO::Room::Room(const std::string &baseLayerTexturePath, int &resMultiplier){
    mask.left = 0;
    mask.top = 0;
    mask.width = 320 * resMultiplier;
    mask.height = 200 * resMultiplier;
    view.reset(mask);
    baseLayerTexture.loadFromFile(baseLayerTexturePath);
    baseLayer.setTexture(baseLayerTexture);
    baseLayer.scale(resMultiplier, resMultiplier);
    if (baseLayerTexture.getSize().x != mask.width || baseLayerTexture.getSize().y != mask.height){
        isScrollable = true;
    } else {
        isScrollable = false;
    }
}

void BRO::Room::scrollHorizontal(float playerPositionX, int &resMultiplier){
    if (isScrollable){
        if (playerPositionX > mask.width + mask.left - 100 * resMultiplier && (baseLayerTexture.getSize().x - 1) * resMultiplier > mask.width + mask.left){
            mask.left += 2.5f * resMultiplier;
            foreground.move(sf::Vector2f(- resMultiplier, 0));
        } else if (playerPositionX < mask.left + 100 * resMultiplier && mask.left > 0){
            mask.left -= 2.5f * resMultiplier;
            foreground.move(sf::Vector2f(resMultiplier, 0));
        }
    }
}

void BRO::Room::setNavMesh(BRO::NavMesh &navMesh){
    *linkedNavMesh = navMesh;
}

void BRO::Room::addDynamicObject(sf::Sprite &sprite) {
    dynamicObjects.push_back(&sprite);
}

void BRO::Room::drawRoom(sf::RenderWindow &window){
    window.setView(view);
    window.draw(baseLayer);

    // doors
    for (int i = 0; i < doors.size(); i++){
        window.draw(doors[i]->sprite);
    }
}

void BRO::Room::drawDynamicObjects(BRO::Room &room, sf::RenderWindow &window) {
    std::sort(dynamicObjects.begin(), room.dynamicObjects.end(), BRO::Room::compareY);
    for (int i = 0; i < dynamicObjects.size(); i++){
        window.draw(*dynamicObjects[i]);
    }
}
