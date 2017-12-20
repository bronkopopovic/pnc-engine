#include "hud.h"

// TO-DO: build verbs interface (look at, walk to, pick up, use, push, pull, etc)

BRO::PlayerIcon::PlayerIcon(std::string texturePath, int y, sf::RenderWindow &window, int &resMultiplier) {
    texture.loadFromFile(texturePath);
    mask.width = 24;
    mask.height = 24;
    isActive = false;
    isVisible = false;
    sprite.setTexture(texture);
    sprite.setTextureRect(mask);
    sprite.setScale(resMultiplier, resMultiplier);
    sprite.setPosition(window.mapPixelToCoords(sf::Vector2i(293 * resMultiplier, y * resMultiplier)));
}

void BRO::PlayerIcon::setVisibility(bool trueFalse) {
    isVisible = trueFalse;
}

void BRO::PlayerIcon::setActive(bool trueFalse) {
    isActive = trueFalse;
    if (trueFalse){
        mask.left = 0;
        sprite.setTextureRect(mask);
    } else {
        mask.left = 24;
        sprite.setTextureRect(mask);
    }
}

void BRO::Hud::init(sf::RenderWindow &window, int resMultiplier){
    loaded = true;
    bottom.width = window.getSize().x;
    bottom.height = window.getSize().y / 4 + 10;
    bottom.background.setSize(sf::Vector2f(bottom.width, bottom.height));
    bottom.background.setFillColor(sf::Color(0, 0, 0, 255));
    bottom.background.setPosition(0, window.getSize().y - bottom.height);


    // VERBS MENU
    if (!menuFont.loadFromFile("menu.ttf"))
    {
        std::cout<<"could not load menu font"<<std::endl;
    }

    give.text.setFont(menuFont);
    give.text.setString("give");
    give.text.setCharacterSize(8 * resMultiplier);
    give.text.setFillColor(sf::Color(181,167,92,255));
    give.text.setPosition(sf::Vector2f(6 * resMultiplier, window.getSize().y - 38 * resMultiplier));
    allVerbs.push_back(&give);

    open.text.setFont(menuFont);
    open.text.setString("open");
    open.text.setCharacterSize(8 * resMultiplier);
    open.text.setFillColor(sf::Color(181,167,92,255));
    open.text.setPosition(sf::Vector2f(6 * resMultiplier, window.getSize().y - 26 * resMultiplier));
    allVerbs.push_back(&open);

    close.text.setFont(menuFont);
    close.text.setString("close");
    close.text.setCharacterSize(8 * resMultiplier);
    close.text.setFillColor(sf::Color(181,167,92,255));
    close.text.setPosition(sf::Vector2f(6 * resMultiplier, window.getSize().y - 14 * resMultiplier));
    allVerbs.push_back(&close);

    pickUp.text.setFont(menuFont);
    pickUp.text.setString("pick up");
    pickUp.text.setCharacterSize(8 * resMultiplier);
    pickUp.text.setFillColor(sf::Color(181,167,92,255));
    pickUp.text.setPosition(sf::Vector2f(50 * resMultiplier, window.getSize().y - 38 * resMultiplier));
    allVerbs.push_back(&pickUp);

    talkTo.text.setFont(menuFont);
    talkTo.text.setString("talk to");
    talkTo.text.setCharacterSize(8 * resMultiplier);
    talkTo.text.setFillColor(sf::Color(181,167,92,255));
    talkTo.text.setPosition(sf::Vector2f(50 * resMultiplier, window.getSize().y - 26 * resMultiplier));
    allVerbs.push_back(&talkTo);

    lookAt.text.setFont(menuFont);
    lookAt.text.setString("look at");
    lookAt.text.setCharacterSize(8 * resMultiplier);
    lookAt.text.setFillColor(sf::Color(181,167,92,255));
    lookAt.text.setPosition(sf::Vector2f(50 * resMultiplier, window.getSize().y - 14 * resMultiplier));
    allVerbs.push_back(&lookAt);

    use.text.setFont(menuFont);
    use.text.setString("use");
    use.text.setCharacterSize(8 * resMultiplier);
    use.text.setFillColor(sf::Color(181,167,92,255));
    use.text.setPosition(sf::Vector2f(110 * resMultiplier, window.getSize().y - 38 * resMultiplier));
    allVerbs.push_back(&use);

    push.text.setFont(menuFont);
    push.text.setString("push");
    push.text.setCharacterSize(8 * resMultiplier);
    push.text.setFillColor(sf::Color(181,167,92,255));
    push.text.setPosition(sf::Vector2f(110 * resMultiplier, window.getSize().y - 26 * resMultiplier));
    allVerbs.push_back(&push);

    pull.text.setFont(menuFont);
    pull.text.setString("pull");
    pull.text.setCharacterSize(8 * resMultiplier);
    pull.text.setFillColor(sf::Color(181,167,92,255));
    pull.text.setPosition(sf::Vector2f(110 * resMultiplier, window.getSize().y - 14 * resMultiplier));
    allVerbs.push_back(&pull);


    // ITEM GRID


    // MOUSE OVER INFO
    mouseOver.text.setFont(menuFont);
    //mouseOver.text.setString("Use stuff with other stuff");
    mouseOver.text.setCharacterSize(8 * resMultiplier);
    mouseOver.text.setFillColor(sf::Color(64, 180, 180, 255));
    mouseOver.text.setPosition(sf::Vector2f(6 * resMultiplier, window.getSize().y - 50 * resMultiplier));


    // INTERACTION

}

std::string BRO::Hud::buildMouseOver() {
    if (hovC == 0 && selC == 0){
        return "";
    }
    if (hovC == 1 && selC == 0){
        return hoveredVerb;
    }
    if (hovC == 1 && selC == 1){
        return hoveredVerb;
    }
    if (hovC == 0 && selC == 1){
        return selectedVerb;
    }
}

void BRO::Hud::drawHud(sf::RenderWindow &window, sf::Vector2f &mappedCursor) {
    if (loaded){
        // player switcher UI
        for (int i = 0; i < playerIcons.size(); i++){
            window.draw(playerIcons[i]->sprite);
        }

        // verbs UI
        hovC = 0;
        for (int i = 0; i < allVerbs.size(); i++){
            // cursor on verb
            if (allVerbs[i]->text.getGlobalBounds().contains(mappedCursor)){
                hovC += 1;
                hoveredVerb = allVerbs[i]->text.getString();
                // if clicked
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    selC = 1;
                    selectedVerb = hoveredVerb;
                }
            }
            // cursor not on verb
            else if (hovC == 0) {
                hoveredVerb = "";
                // if clicked
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    selC = 0;
                    selectedVerb = hoveredVerb;
                }
            }
        }

        mouseOver.text.setString(buildMouseOver());

        // bottom menu
        window.draw(bottom.background);
        window.draw(give.text);
        window.draw(open.text);
        window.draw(close.text);
        window.draw(pickUp.text);
        window.draw(talkTo.text);
        window.draw(lookAt.text);
        window.draw(use.text);
        window.draw(push.text);
        window.draw(pull.text);
        window.draw(mouseOver.text);

    }
}