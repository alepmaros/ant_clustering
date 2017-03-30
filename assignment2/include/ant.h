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
                                int mGridSize,
                                sf::Vector2f dataPosition,
                                int antType,
                                sf::Font &font);

    void                draw(sf::RenderWindow* window);

    // Only alive ants should call update
    void                update();

    // Function used for alive ants move dead ants
    void                move(sf::Vector2f position);

    // Funciton used for alive ant to move in the board
    void                move();

private:
    int                 getAntId();
    sf::Vector2f        getDataPosition();
    sf::Vector2i        decideDirection();
    void                chooseOtherDestination();

    float               calculateSimilarity();
    float               getProbabilityPickup();
    float               getProbabilityDrop(); 

    int                 getAntType();

private:
    int                 mAntId;
    sf::Vector2f        mPosition;
    sf::Vector2i        mGridPosition;
    bool                mIsDead;
    int                 mRadius;
    sf::Color           mColor;
    sf::RectangleShape  mBody;
    Status              mCurrentStatus;
    std::vector<std::vector<int> > &mDeadAntGrid;
    std::vector<std::vector<int> > &mAliveAntGrid;
    std::vector<Ant>    &mDeadAnts;
    std::vector<Ant>    &mAliveAnts;
    int                 mAntSize;
    int                 mGridSize;
    int                 mCellsSeen;
    int                 mCellsSeenSquared;

    // This is the parameter passed in the file. The Data position
    // This is used to calculate how similar an ant is to another
    sf::Vector2f        mDataPosition;
    int                 mAntType;

    sf::Vector2i        mDestination;
    sf::Font            &font;
};


#endif
