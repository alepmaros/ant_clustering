/*
 * Alexandre Maros - 2017/1
 * Ant Clustering Algorithm
 *
 */

#include "ant.h"

Ant::Ant(bool isDead, sf::Vector2f position) 
{
    this->mIsDead = isDead;
    this->mPosition = position;

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
    this->mBody.setPosition(position);
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

}


