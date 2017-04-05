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
        int gridSize,
        sf::Vector2f dataPosition,
        int antType,
        sf::Font &font)
    : mAliveAntGrid(aliveAntGrid)
      , mDeadAntGrid(deadAntGrid)
      , mDeadAnts(deadAnts)
      , mAliveAnts(aliveAnts)
      , font(font)
{
    this->mAntId = antId;
    this->mIsDead = isDead;
    this->mGridPosition = position;
    this->mPosition = sf::Vector2f(position.x * antSize, position.y * antSize);
    this->mRadius = radius;
    this->mCurrentStatus = Status::Moving;
    this->mAntSize = antSize;
    this->mGridSize = gridSize;
    this->mDataPosition = dataPosition;
    this->mAntType = antType;
    this->mDestination = sf::Vector2i(std::rand() % gridSize, std::rand() % gridSize);

    // This is how many cells the ant will see with radius x
    // Which is the sum from 1 to radius of 8 times i
    this->mCellsSeen = 0;
    for (int i = 1; i <= radius; i++)
    {
        this->mCellsSeen += 8 * i;
    }
    this->mCellsSeenSquared = mCellsSeen * mCellsSeen;

    if (isDead)
    {
        if (mAntType == 1)
            this->mColor = sf::Color::Red;
        else if (mAntType == 2)
            this->mColor = sf::Color::Green;
        else if (mAntType == 3)
            this->mColor = sf::Color::Blue;
        else if (mAntType == 4)
            this->mColor = sf::Color::Magenta;
        else if (mAntType == 5)
            this->mColor = sf::Color(255,128,0);
        else if (mAntType == 6)
            this->mColor = sf::Color(128, 255, 0);
        else if (mAntType == 7)
            this->mColor = sf::Color(255,128,0);
        else if (mAntType == 8)
            this->mColor = sf::Color(255, 255, 0);
        else if (mAntType == 9)
            this->mColor = sf::Color(128, 255, 0);
        else if (mAntType == 10)
            this->mColor = sf::Color(127, 255, 0);
        else if (mAntType == 11)
            this->mColor = sf::Color(255,0,127);
        else if (mAntType == 12)
            this->mColor = sf::Color(128, 128, 128);
        else if (mAntType == 13)
            this->mColor = sf::Color(0, 153, 153);
        else if (mAntType == 14)
            this->mColor = sf::Color(0, 153, 0);
        else
            this->mColor = sf::Color(153, 76, 0);

    }
    else
    {
        this->mColor = sf::Color::Black;
    }

    // making the body
    this->mBody.setSize(sf::Vector2f(antSize,antSize));
    this->mBody.setFillColor(this->mColor);
    this->mBody.setPosition(this->mPosition);
}

void Ant::draw(sf::RenderWindow *window)
{
    //sf::Text numero(std::to_string(mAntType), font);

    //numero.setCharacterSize(mAntSize);
    //numero.setPosition(mGridPosition.x * mAntSize, mGridPosition.y * mAntSize);
    //numero.setFillColor(sf::Color::Black);

    if (this->mCurrentStatus == Status::Carrying)
    {
        this->mBody.setFillColor(sf::Color::Cyan);
    }
    else if (!this->mIsDead)
    {
        this->mBody.setFillColor(sf::Color::Black);
    }
    window->draw(this->mBody); 
    //window->draw(numero);

}

// Only alive ants should call this.
void Ant::update(int nIteration, int nMaxIteration)
{
    // If the iteration ends, the ant will keep going until it drops the one its carrying
    if (this->mCurrentStatus == Status::Moving && nIteration < nMaxIteration)
    {
        // Find another direction to move to
        // Check piles etc
        //std::cout << "There is x dead ants around me: " << deadAntCount << std::endl;

        if (mDeadAntGrid[mGridPosition.y][mGridPosition.x] !=  -1)
        {
            //int deadAntCount = this->countDeadAnts();
            //int chanceOfCarryingAnt = std::pow((mCellsSeen - deadAntCount) / ((double) mCellsSeen), 2) * 100;

            int chanceOfCarryingAnt = (int) (this->getProbabilityPickup() * 10000);

            if (chanceOfCarryingAnt <= 0)
            {
                chanceOfCarryingAnt = 5;
            }
            else if (chanceOfCarryingAnt >= 10000)
            {
                chanceOfCarryingAnt = 9995;
            }

            //std::cout << "There is a x% chance of carrying this ant: " << chanceOfCarryingAnt << std::endl;

            if( (std::rand() % 10001) <= chanceOfCarryingAnt)
            {
                //std::cout << "I am starting to carry an ant at position " << 
                    //mGridPosition.y << " - " << mGridPosition.x << std::endl;
                this->mCurrentStatus = Status::Carrying;
            } 
        }
    }
    else if (this->mCurrentStatus == Status::Carrying)
    {
        if (mDeadAntGrid[mGridPosition.y][mGridPosition.x] != -1)
        {
            //int deadAntCount = this->countDeadAnts();
            //int chanceOfDroppingAnt = (int) (std::pow( ((double) deadAntCount / mCellsSeen), 2 ) * 100);
        
            int chanceOfDroppingAnt = (int) (this->getProbabilityDrop() * 10000);
            
            if (chanceOfDroppingAnt <= 0)
            {
                chanceOfDroppingAnt = 5;
            }
            else if (chanceOfDroppingAnt >= 10000)
            {
                chanceOfDroppingAnt = 9995;
            }

            //std::cout << "There is a x% chance of dropping tis ant: " << chanceOfDroppingAnt << std::endl;
            if ( (std::rand() % 10001) <= chanceOfDroppingAnt )
            {
                //std::cout << "I dropped ant with " << chanceOfDroppingAnt << std::endl;
                this->mCurrentStatus = Status::Moving;
            }
        }
    }

    // Perform Movement

    //Direction whereToMove = static_cast<Direction>(std::rand() % 8);
    sf::Vector2i whereToMove = decideDirection();

    int nextPosY = mGridPosition.y + whereToMove.y;
    int nextPosX = mGridPosition.x + whereToMove.x;
    
    // This is to remove border limitations for the ants. They will loop back now.
    if (nextPosY < 0)
        nextPosY = mGridSize + nextPosY;
    if (nextPosY >= mGridSize)
        nextPosY = nextPosY - mGridSize;
    if (nextPosX < 0)
        nextPosX = mGridSize + nextPosX;
    if (nextPosX >= mGridSize)
        nextPosX = nextPosX - mGridSize;


    // If there is an Alive ant in the next position, choose another destination to move
    if (mAliveAntGrid[nextPosY][nextPosX] != -1)
    {
        chooseOtherDestination();
        return;
    }
    if (this->mCurrentStatus == Status::Carrying)
    {
        // If I am carrying a dead ant and there is a dead ant in the next space
        // choose other destination to move
        if (mDeadAntGrid[nextPosY][nextPosX] != -1)
        {
            chooseOtherDestination();
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

sf::Vector2i Ant::decideDirection()
{
    // If I am at my destination - chose another one
    if ( mGridPosition == mDestination )
    {
        chooseOtherDestination();
    }

    int y = mDestination.y - mGridPosition.y;
    int x = mDestination.x - mGridPosition.x;
    int gridBy2 = mGridSize / 2;

    // if the distance the distance is greater then the grid divided by 2 its easier to loop around
    if ( y > 0 )
        y = 1;
    else if ( y < 0)
        y = -1;

    if ( std::abs(mDestination.y - mGridPosition.y) > gridBy2 )
        y = -y;

    if (x > 0)
        x = 1;
    else if ( x < 0 )
        x = -1;

    if ( std::abs(mDestination.x - mGridPosition.x) > gridBy2 )
        x = -x;

    return sf::Vector2i(x,y);
}

void Ant::chooseOtherDestination()
{
    do {
        mDestination = sf::Vector2i(std::rand() % mGridSize, std::rand() % mGridSize);
    } while(mDestination == mGridPosition);
}

void Ant::move(sf::Vector2f nextPos)
{
    mGridPosition.x = (int) nextPos.x;
    mGridPosition.y = (int) nextPos.y;
    mBody.setPosition(sf::Vector2f(nextPos.x * mAntSize, nextPos.y * mAntSize));
}

int Ant::getAntId()
{
    return mAntId;
}

sf::Vector2f Ant::getDataPosition()
{
    return mDataPosition;
}

float Ant::calculateSimilarity()
{
    float alpha = 10;
    float similarity = 0;
    float distanceX, distanceY, distance;
    int posX, posY;
    int deadAntCount = 0;

    sf::Vector2f deadAntDataPosition = mDeadAnts[mDeadAntGrid[mGridPosition.y][mGridPosition.x]].getDataPosition();
    for (int i = -mRadius; i <= mRadius; i++)
    {
        for (int j = -mRadius; j <= mRadius; j++) 
        {
            posY = mGridPosition.y + i;
            posX = mGridPosition.x + j;

            if (posY == mGridPosition.y && posX == mGridPosition.x)
                continue;

            // This is to remove border limitations for the ants. They will loop back now.
            if (posY < 0)
            {
                posY = mGridSize + posY;
            }
            else if (posY >= mGridSize)
            {
                posY = posY - mGridSize;
            }

            if (posX < 0)
            {
                posX = mGridSize + posX;
            }
            else if (posX >= mGridSize)
            {
                posX = posX - mGridSize;
            }

            if (mDeadAntGrid[posY][posX] != -1)
            {
                sf::Vector2f deadAntDataPos_j = mDeadAnts[mDeadAntGrid[posY][posX]].getDataPosition();
                distanceX = deadAntDataPos_j.x - deadAntDataPosition.x;
                distanceY = deadAntDataPos_j.y - deadAntDataPosition.y;
                distance = std::sqrt( (distanceX * distanceX) + (distanceY * distanceY));
                distance = 1 - (distance/alpha);

                if (distance < 0.f)
                    return 0.f;

                deadAntCount++;

                similarity += distance;
            }
        }
    }

    similarity = (1.0 / std::pow((mCellsSeen+1) - deadAntCount, 2)) * similarity;
    
    // if similarity < 0 return 0 else return similarity
    return similarity < 0 ? 0 : similarity;
}

float Ant::getProbabilityPickup()
{
    float k1 = 0.02;
    float similarity = this->calculateSimilarity();
    float pp = k1 / (k1 + similarity);
    //std::cout << similarity << " @ pp:" << pp * pp << " @ k1: " << k1 << std::endl;
    return pp * pp;
}

float Ant::getProbabilityDrop()
{
    float k2 = 0.03;
    float similarity = this->calculateSimilarity();
    float pd = similarity / (k2 + similarity);
    //std::cout << similarity << " @ " << k2 << std::endl;
    return pd * pd;
}

int Ant::getAntType()
{
    return mAntType;
}
