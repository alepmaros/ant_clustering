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

    // The antGrid is only used to check if there is an ent in an space.
    // 'n' -- No ant
    // 'a' -- Alive ant
    // 'd' -- Dead ant
    char **antGrid = (char**) malloc(sizeof(char*) * spaceAvailable);
    for (int i = 0; i < spaceAvailable; i++)
    {
        antGrid[i] = (char*) malloc(sizeof(char) * spaceAvailable);
        memset(antGrid[i], 'n', sizeof(char) * spaceAvailable);
    }

    // Window setup
    sf::RenderWindow window(sf::VideoMode(800, 800), "Ants");
    
    // Since this is a simulation and not a game I will controll the speed using
    // the frame rate. This is not recomended, but for simplicity sake I will be
    // using this for now.
    window.setFramerateLimit(5);


    // Spawning the dead ants
    dead_ants.clear();
    for (int i = 0; i < nDeadAnts; i++)
    {
        int posX, posY;
        do {
            posX = std::rand() % spaceAvailable;
            posY = std::rand() % spaceAvailable;
        } while(antGrid[posY][posX] != 'n');

        //std::cout << posX << "-" << posY << "-" << dead_ants.size() << std::endl;
        Ant a(true, sf::Vector2f(posX * antSize, posY * antSize), radius);
        antGrid[posY][posX] = 'd';
        dead_ants.push_back(a);
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

        for(std::vector<Ant>::iterator it = dead_ants.begin();
                it != dead_ants.end(); ++it)
        {
            it->draw(&window);
        }

        window.display();
    }

    return 0;
}
