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

#include <SFML/Graphics.hpp>

#include "ant.h"

std::vector<Ant> alive_ants;
std::vector<Ant> dead_ants;

int         nAliveAnts  = 50;
int         nDeadAnts   = 500;

int main()
{
    std::srand(std::time(0));

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
        int posX = std::rand() % 800;
        int posY = std::rand() % 800;
        //std::cout << posX << "-" << posY << "-" << dead_ants.size() << std::endl;
        Ant a(true, sf::Vector2f(posX, posY));
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
