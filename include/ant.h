/*
 * Alexandre Maros - 2017/1
 * Ant Clustering Algorithm
 *
 */

#ifndef ANT_H
#define ANT_H

#include <SFML/Graphics.hpp>

class Ant
{

public:
                        Ant(bool isDead, sf::Vector2f position);

    void                draw(sf::RenderWindow* window);

    // Only alive ants should call update
    void                update();

    // Function used for alive ants move dead ants
    void                move(sf::Vector2i position);

public:
    sf::Vector2f        mPosition;
    bool                mIsDead;
    sf::Color           mColor;
    sf::RectangleShape  mBody;

};


#endif
