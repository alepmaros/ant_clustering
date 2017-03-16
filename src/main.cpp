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
int         nAliveAnts  = 50;
int         nDeadAnts   = 1000;
// Radius that the ant can see
// If radius == 1 the ant can see the 8 adjacents spaces
// If radius == 2 the ant can see 8 + 16 spaces
// etc...
int         radius      = 2;
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

    // Hurray for pointer to pointer to pointer
    Ant ***aliveAntGrid = (Ant***) malloc(sizeof(Ant**) * spaceAvailable);
    for (int i = 0; i < spaceAvailable; i++)
    {
        aliveAntGrid[i] = (Ant**) malloc(sizeof(Ant*) * spaceAvailable);
        for (int j = 0; j < spaceAvailable; j++)
        {
            aliveAntGrid[i][j] = nullptr;
        }
    }

    Ant ***deadAntGrid = (Ant***) malloc(sizeof(Ant**) * spaceAvailable);
    for (int i = 0; i < spaceAvailable; i++)
    {
        deadAntGrid[i] = (Ant**) malloc(sizeof(Ant*) * spaceAvailable);
        for (int j = 0; j < spaceAvailable; j++)
        {
            deadAntGrid[i][j] = nullptr;
        }
    }

    //char **antGrid = (char**) malloc(sizeof(char*) * spaceAvailable);
    //for (int i = 0; i < spaceAvailable; i++)
    //{
        //antGrid[i] = (char*) malloc(sizeof(char) * spaceAvailable);
        //memset(antGrid[i], 'n', sizeof(char) * spaceAvailable);
    //}

    // Window setup
    sf::RenderWindow window(sf::VideoMode(800, 800), "Ants");
    
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
        } while(deadAntGrid[posY][posX] != nullptr);

        //std::cout << posX << "-" << posY << "-" << dead_ants.size() << std::endl;
        Ant a(true, sf::Vector2i(posX, posY), radius, nullptr, nullptr, antSize, spaceAvailable);
        dead_ants.push_back(a);
        deadAntGrid[posY][posX] = &(dead_ants[i]);

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
        } while(aliveAntGrid[posY][posX] != nullptr);

        Ant a(false, sf::Vector2i(posX, posY), radius, deadAntGrid, aliveAntGrid, antSize, spaceAvailable);
        alive_ants.push_back(a);
        aliveAntGrid[posY][posX] = &(alive_ants[i]);
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
            window.draw(it->mBody);
        }

        // Draw Alive Ants
        for(std::vector<Ant>::iterator it = alive_ants.begin();
                it != alive_ants.end(); it++) 
        {
            window.draw(it->mBody);
        }

        window.display();
    }

    return 0;
}
