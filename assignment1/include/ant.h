/*
 * Alexandre Maros - 2017/1
 * Ant Clustering Algorithm
 *
 */

#ifndef ANT_H
#define ANT_H

#include <SFML/Graphics.hpp>

#include <vector>

class Ant
{

public:
    enum Direction
    {
        North,
        South,
        East,
        West,
        NorthEast,
        SouthEast,
        SouthWest,
        NorthWest
    };

    enum Status
    {
        Carrying,
        Moving,
        BeingCarried
    };

public:
                        Ant(int antId, bool isDead, sf::Vector2i position, int radius,
                                std::vector<std::vector<int> > &deadAntGrid,
                                std::vector<std::vector<int> > &aliveAntGrid,
                                std::vector<Ant> &deadAnts, std::vector<Ant> &aliveAnts,
                                int antSize,
                                int mGridSize);

    void                draw(sf::RenderWindow* window);

    // Only alive ants should call update
    void                update();

    // Function used for alive ants move dead ants
    void                move(sf::Vector2f position);

private:
    // Function to count dead ants around the ant
    int                 countDeadAnts();
    int                 getAntId();
    Direction           decideDirection();

private:
    int                 mAntId;
    sf::Vector2f        mPosition;
    sf::Vector2i        mGridPosition;
    bool                mIsDead;
    int                 mRadius;
    sf::Color           mColor;
    sf::RectangleShape  mBody;
    Direction           mLastDirectionMoved;
    Status              mCurrentStatus;
    std::vector<std::vector<int> > &mDeadAntGrid;
    std::vector<std::vector<int> > &mAliveAntGrid;
    std::vector<Ant>    &mDeadAnts;
    std::vector<Ant>    &mAliveAnts;
    int                 mAntSize;
    int                 mGridSize;
    int                 mCellsSeen;
    int                 mCooldown;

};


#endif
