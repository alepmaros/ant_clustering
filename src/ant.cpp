/*
 * Alexandre Maros - 2017/1
 * Ant Clustering Algorithm
 *
 */

#include "ant.h"
#include <iostream>

Ant::Ant(bool isDead, sf::Vector2i position, int radius, Ant*** antGrid, int antSize,
        int gridSize)
{
    this->mIsDead = isDead;
    this->mGridPosition = position;
    this->mPosition = sf::Vector2f(position.x * antSize, position.y * antSize);;
    this->mRadius = radius;
    this->deadAntGrid = antGrid;
    this->mCurrentStatus = Status::Moving;
    this->mAntSize = antSize;
    this->mGridSize = gridSize;

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
    //while(window->isOpen())
    //{
    window->draw(this->mBody); 

    //}
}

// Only alive ants should call this.
void Ant::update()
{
    if (this->mCurrentStatus == Status::Moving)
    {
        // Find another direction to move to
        // Check piles etc
        int deadAntCount = 0;
        int posY, posX;
        for (int i = -mRadius; i <= mRadius; i++)
        {
            for (int j = -mRadius; j <= mRadius; j++) 
            {
                posY = mGridPosition.y + i;
                posX = mGridPosition.x + j;
                if (posY >= 0 && posX >= 0 && posY < mGridSize && posX < mGridSize)
                {
                    if (deadAntGrid[posY][posX] != nullptr)
                    {
                        deadAntCount++;
                    }
                }
            }
        }
        //std::cout << "There is x dead ants around me: " << deadAntCount << std::endl;
    }
    else
    {
        // Check nearby bodies etc
    }
}


