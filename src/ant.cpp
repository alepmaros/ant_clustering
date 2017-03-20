/*
 * Alexandre Maros - 2017/1
 * Ant Clustering Algorithm
 *
 */

#include "ant.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

Ant::Ant(int antId,
        bool isDead,
        sf::Vector2i position,
        int radius,
        std::vector<std::vector<int> > &deadAntGrid,
        std::vector<std::vector<int> > &aliveAntGrid, 
        std::vector<Ant> &deadAnts,
        std::vector<Ant> &aliveAnts,
        int antSize,
        int gridSize)
    : mAliveAntGrid(aliveAntGrid)
      , mDeadAntGrid(deadAntGrid)
      , mDeadAnts(deadAnts)
      , mAliveAnts(aliveAnts)
{
    this->mAntId = antId;
    this->mIsDead = isDead;
    this->mGridPosition = position;
    this->mPosition = sf::Vector2f(position.x * antSize, position.y * antSize);
    this->mRadius = radius;
    this->mCurrentStatus = Status::Moving;
    this->mAntSize = antSize;
    this->mGridSize = gridSize;
    this->mCooldown = 0;
    this->mLastDirectionMoved = static_cast<Direction>(std::rand() % 4);

    // This is how many cells the ant will see with radius x
    // Which is the sum from 1 to radius of 8 times i
    this->mCellsSeen = 1;
    for (int i = 1; i <= radius; i++)
    {
        this->mCellsSeen += 8 * i;
    }

    if (isDead)
    {
        this->mColor = sf::Color::Red;
    }
    else
    {
        this->mColor = sf::Color::Black;
    }

    // making the body
    this->mBody.setSize(sf::Vector2f(5,5));
    this->mBody.setFillColor(this->mColor);
    this->mBody.setPosition(this->mPosition);
}

void Ant::draw(sf::RenderWindow *window)
{
    if (this->mCurrentStatus == Status::Carrying)
    {
        this->mBody.setFillColor(sf::Color::Blue);
    }
    else if (!this->mIsDead)
    {
        this->mBody.setFillColor(sf::Color::Black);
    }
    window->draw(this->mBody); 

}

// Only alive ants should call this.
void Ant::update()
{
    if (this->mCurrentStatus == Status::Moving)
    {
        // Find another direction to move to
        // Check piles etc
        //std::cout << "There is x dead ants around me: " << deadAntCount << std::endl;

        if (mDeadAntGrid[mGridPosition.y][mGridPosition.x] !=  -1)
        {
            int deadAntCount = this->countDeadAnts();
            // How the chance of carrying an ant is calculated:
            //  The ant will carry a dead ant if it thinks that ant does not belong to a pile.
            //  To get that chance you just divide the emptyCells around the ant by the total
            //  number of cells.
            int chanceOfCarryingAnt = std::pow((mCellsSeen - deadAntCount) / ((double) mCellsSeen), 2) * 100;

            if (chanceOfCarryingAnt == 0)
            {
                chanceOfCarryingAnt = 1;
            }
            else if (chanceOfCarryingAnt == 100)
            {
                chanceOfCarryingAnt = 99;
            }
            //std::cout << "There is a x% chance of carrying this ant: " << chanceOfCarryingAnt << std::endl;

            if( (std::rand() % 101) <= chanceOfCarryingAnt)
            {
                //std::cout << "I am starting to carry an ant at position " << 
                    //mGridPosition.y << " - " << mGridPosition.x << std::endl;
                this->mCurrentStatus = Status::Carrying;
            } 

        }
    }
    else
    {
        if (mDeadAntGrid[mGridPosition.y][mGridPosition.x] != -1)
        {
            int deadAntCount = this->countDeadAnts();

            //std::cout << (double) deadAntCount / mCellsSeen << std::endl;

            // deadAntCount = how many dead ants in the ants FOV
            // mCellsSeen = how many cells can the ant see
            // ( deadAntCount / mCellsSeen ) ^ 2
            int chanceOfDroppingAnt = (int) (std::pow( ((double) deadAntCount / mCellsSeen), 2 ) * 100);
            //std::cout << mCellsSeen << "-" << deadAntCount << "-" << chanceOfDroppingAnt << std::endl;
            
            if (chanceOfDroppingAnt == 0)
            {
                chanceOfDroppingAnt = 1;
            }
            else if (chanceOfDroppingAnt == 100)
            {
                chanceOfDroppingAnt = 99;
            }

            if ( (std::rand() % 101) <= chanceOfDroppingAnt )
            {
                //std::cout << "I dropped ant with " << chanceOfDroppingAnt << std::endl;
                this->mCurrentStatus = Status::Moving;
            }
        }
    }

    // Perform Movement

    Direction whereToMove = static_cast<Direction>(std::rand() % 8);

    int nextPosY = mGridPosition.y;
    int nextPosX = mGridPosition.x;
    switch(whereToMove)
    {
        case Direction::North:
            nextPosY--;
            break;
        case Direction::South:
            nextPosY++;
            break;
        case Direction::East:
            nextPosX++;
            break;
        case Direction::West:
            nextPosX--;
            break;
        case Direction::NorthEast:
            nextPosY--;
            nextPosX++;
            break;
        case Direction::SouthEast:
            nextPosY++;
            nextPosX++;
            break;
        case Direction::SouthWest:
            nextPosY++;
            nextPosX--;
            break;
        case Direction::NorthWest:
            nextPosY--;
            nextPosX--;
            break;
    }


    // This is to remove border limitations for the ants. They will loop back now.
    if (nextPosY < 0)
        nextPosY = mGridSize + nextPosY;
    if (nextPosY >= mGridSize)
        nextPosY = nextPosY - mGridSize;
    if (nextPosX < 0)
        nextPosX = mGridSize + nextPosX;
    if (nextPosX >= mGridSize)
        nextPosX = nextPosX - mGridSize;


    // If there is an Alive ant in the next position, do nothing.
    if (mAliveAntGrid[nextPosY][nextPosX] != -1)
    {
        return;
    }
    if (this->mCurrentStatus == Status::Carrying)
    {
        // If I am carrying a dead ant and there is a dead ant in the next space
        // do nothing.
        if (mDeadAntGrid[nextPosY][nextPosX] != -1)
        {
            return;
        }
    }

    // When implementing with multithread, lock this area.
    //
    // Switch the position of the alive ant to the new position
    mAliveAntGrid[nextPosY][nextPosX] = mAliveAntGrid[mGridPosition.y][mGridPosition.x];
    mAliveAntGrid[mGridPosition.y][mGridPosition.x] = -1;

    // If the ant is carrying another one, switch the position of the dead ant as well
    if (this->mCurrentStatus == Status::Carrying)
    {
        mDeadAntGrid[nextPosY][nextPosX] = mDeadAntGrid[mGridPosition.y][mGridPosition.x];
        mDeadAntGrid[mGridPosition.y][mGridPosition.x] = -1;
        mDeadAnts[mDeadAntGrid[nextPosY][nextPosX]].move(sf::Vector2f(nextPosX,nextPosY));
    }

    this->move(sf::Vector2f(nextPosX,nextPosY));
}

void Ant::move(sf::Vector2f nextPos)
{
    mGridPosition.x = (int) nextPos.x;
    mGridPosition.y = (int) nextPos.y;
    mBody.setPosition(sf::Vector2f(nextPos.x * mAntSize, nextPos.y * mAntSize));
}

int Ant::countDeadAnts()
{
    int deadAntCount = 0;
    int posX, posY;
    for (int i = -mRadius; i <= mRadius; i++)
    {
        for (int j = -mRadius; j <= mRadius; j++) 
        {
            posY = mGridPosition.y + i;
            posX = mGridPosition.x + j;

            // This is to remove border limitations for the ants. They will loop back now.
            if (posY < 0)
                posY = mGridSize + posY;
            if (posY >= mGridSize)
                posY = posY - mGridSize;
            if (posX < 0)
                posX = mGridSize + posX;
            if (posX >= mGridSize)
                posX = posX - mGridSize;

            if (mDeadAntGrid[posY][posX] != -1)
            {
                deadAntCount++;
            }
        }
    }
    return deadAntCount;
}
int Ant::getAntId()
{
    return mAntId;
}
