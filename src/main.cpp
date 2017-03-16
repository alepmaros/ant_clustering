/*
 * Alexandre Maros - 2017/1
 * Ant Clustering Algorithm
 *
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include <SFML/Graphics.hpp>

#include "ant.h"

std::vector<Ant> alive_ants;
std::vector<Ant> dead_ants;

/*****************
 * ANTS CONFIGS  *
 *****************/
// Numer of alive and dead ants
int         nAliveAnts  = 200;
int         nDeadAnts   = 1000;
// Radius that the ant can see
// If radius == 1 the ant can see the 8 adjacents spaces
// If radius == 2 the ant can see 8 + 16 spaces
// etc...
int         radius      = 3;
// Size of ants in pixels
int         antSize     = 5;


/******************
 * SCREEN CONFIG  *
 ******************/
// Screen size in the x and y positions
int         screenSize  = 800;


/***************
 * GRID CONFIG *
 ***************/
// Space available to put the ants (grid size)
int         spaceAvailable = (int) 800.0 / 5.0;

int main()
{
    std::srand(std::time(0));

    // Window setup
    sf::RenderWindow window(sf::VideoMode(800, 800), "Ants");

    // Vector to hold ants ID
    std::vector<std::vector<int> > aliveAntGrid;
    std::vector<std::vector<int> > deadAntGrid;
    
    for (int i = 0; i < spaceAvailable; i++)
    {
        aliveAntGrid.push_back(std::vector<int>());
        deadAntGrid.push_back(std::vector<int>());
        for (int j = 0; j < spaceAvailable; j++)
        {
            aliveAntGrid[i].push_back(-1);
            deadAntGrid[i].push_back(-1);
        }
    }
    // Since this is a simulation and not a game I will controll the speed using
    // the frame rate. This is not recomended, but for simplicity sake I will be
    // using this for now.
    window.setFramerateLimit(60);

    // Spawning the dead ants
    dead_ants.clear();
    for (int i = 0; i < nDeadAnts; i++)
    {
        int posX, posY;
        do
        {
            posX = std::rand() % spaceAvailable;
            posY = std::rand() % spaceAvailable;
        } while(deadAntGrid[posY][posX] != -1);

        //std::cout << posX << "-" << posY << "-" << dead_ants.size() << std::endl;
        Ant a(i, true, sf::Vector2i(posX, posY), radius, deadAntGrid, aliveAntGrid,
                dead_ants, alive_ants, antSize, spaceAvailable);
        dead_ants.push_back(a);
        deadAntGrid[posY][posX] = i;

        // Test to check if points is working
        //std::cout << dead_ants[i].mAntSize << "-";
        //aliveAntGrid[posY][posX]->mAntSize = 6;
        //std::cout << dead_ants[i].mAntSize << std::endl;
    }

    // Spawning Alive Ants
    for (int i = 0; i < nAliveAnts; i++)
    {
        int posX, posY;
        do
        {
            posX = std::rand() % spaceAvailable;
            posY = std::rand() % spaceAvailable;
        } while(aliveAntGrid[posY][posX] != -1);

        Ant a(i, false, sf::Vector2i(posX, posY), radius, deadAntGrid, aliveAntGrid,
               dead_ants, alive_ants, antSize, spaceAvailable);
        alive_ants.push_back(a);
        aliveAntGrid[posY][posX] = i;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Update Alive Ants
        for(std::vector<Ant>::iterator it = alive_ants.begin();
                it != alive_ants.end(); it++) 
        {
            it->update();
        }

        // Draw Dead Ants
        for(std::vector<Ant>::iterator it = dead_ants.begin();
                it != dead_ants.end(); ++it)
        {
            //std::cout << it->mGridPosition.x << "-" << it->mGridPosition.y << std::endl;
            //window.draw(it->mBody);
            it->draw(&window);
        }

        // Draw Alive Ants
        for(std::vector<Ant>::iterator it = alive_ants.begin();
                it != alive_ants.end(); it++) 
        {
            //window.draw(it->mBody);
            it->draw(&window);
        }

        window.display();
    }

    return 0;
}

int Ant::getAntId()
{
    return mAntId;
}
