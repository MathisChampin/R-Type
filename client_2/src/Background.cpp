#include "../include/Background.hpp"
#include <iostream>

void Background::initMoveParallax(Sprite &obj, Sprite &objDuplicate, float x)
{
    obj._sprite.move(x, 0);
    objDuplicate._sprite.move(x, 0);
}

void Background::reloadParallax(Sprite &obj, Sprite &objDuplicate, float textureWidth)
{
    sf::Vector2f pos = obj._sprite.getPosition();
    sf::Vector2f posDuplicate = objDuplicate._sprite.getPosition();

    if (pos.x + textureWidth <= 0) {
        obj._sprite.setPosition(posDuplicate.x + textureWidth, pos.y);
    }

    if (posDuplicate.x + textureWidth <= 0) {
        objDuplicate._sprite.setPosition(pos.x + textureWidth, posDuplicate.y);
    }
}


void Background::moveParallax()
{
    float textureWidth1 = _oneBack._sprite.getTexture()->getSize().x;
    float textureWidth2 = _twoBack._sprite.getTexture()->getSize().x;
    float textureWidth3 = _threeBack._sprite.getTexture()->getSize().x;
    float textureWidth4 = _fourBack._sprite.getTexture()->getSize().x;
    float textureWidth5 = _fiveBack._sprite.getTexture()->getSize().x;

    initMoveParallax(_oneBack, _oneBackDuplicate, -0.5f);
    initMoveParallax(_twoBack, _twoBackDuplicate, -1.0f);
    initMoveParallax(_threeBack, _threeBackDuplicate, -1.5f);
    initMoveParallax(_fourBack, _fourBackDuplicate, -2.0f);
    initMoveParallax(_fiveBack, _fiveBackDuplicate, -4.0f);

    reloadParallax(_oneBack, _oneBackDuplicate, textureWidth1);
    reloadParallax(_twoBack, _twoBackDuplicate, textureWidth2);
    reloadParallax(_threeBack, _threeBackDuplicate, textureWidth3);
    reloadParallax(_fourBack, _fourBackDuplicate, textureWidth4);
    reloadParallax(_fiveBack, _fiveBackDuplicate, textureWidth5);
}

void Background::drawParallax(sf::RenderWindow &w)
{
    _oneBack.drawSprite(w);
    _oneBackDuplicate.drawSprite(w);

    _twoBack.drawSprite(w);
    _twoBackDuplicate.drawSprite(w);

    _threeBack.drawSprite(w);
    _threeBackDuplicate.drawSprite(w);

    _fourBack.drawSprite(w);
    _fourBackDuplicate.drawSprite(w);

    _fiveBack.drawSprite(w);
    _fiveBackDuplicate.drawSprite(w);
}
