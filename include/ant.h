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
    enum Direction
    {
        North,
        South,
        East,
        West
    };

    enum Status
    {
        Carrying,
        Moving,
        BeingCarried
    };

public:
                        Ant(bool isDead, sf::Vector2i position, int radius,
                                Ant*** deadAntGrid, Ant*** aliveAntGrid, int antSize,
                                int mGridSize);

    void                draw(sf::RenderWindow* window);

    // Only alive ants should call update
    void                update();

    // Function used for alive ants move dead ants
    void                move(sf::Vector2f position);

private:
    // Function to count dead ants around the ant
    int                 countDeadAnts();

public:
    sf::Vector2f        mPosition;
    sf::Vector2i        mGridPosition;
    bool                mIsDead;
    int                 mRadius;
    sf::Color           mColor;
    sf::RectangleShape  mBody;
    Direction           mLastDirectionMoved;
    Status              mCurrentStatus;
    Ant***              deadAntGrid;
    Ant***              aliveAntGrid;
    int                 mAntSize;
    int                 mGridSize;
    int                 mCellsSeen;

};


#endif
