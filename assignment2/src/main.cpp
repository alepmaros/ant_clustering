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
#include <fstream>

#include <SFML/Graphics.hpp>

#include "ant.h"

std::vector<Ant> alive_ants;
std::vector<Ant> dead_ants;

/*****************
 * ANTS CONFIGS  *
 *****************/
// Numer of alive and dead ants
int         nAliveAnts  = 50;
// The number of dead ants depends on the file passed on execution
int         nDeadAnts   = 0;
// Radius that the ant can see
// If radius == 1 the ant can see the 8 adjacents spaces
// If radius == 2 the ant can see 8 + 16 spaces
// etc...
int         radius      = 1;
// Size of ants in pixels
int         antSize     = 10;

/******************
 * SCREEN CONFIG  *
 ******************/
// Screen size in the x and y positions
int         screenSize  = 770;

// How many iterations should it calculated before drawing to the screen.
int         drawIterations = 2000;

// nIterations == how many iterations it already did
// maxIterations == the number max of iterations to do
unsigned long nIterations   = 0;
unsigned long maxIterations = 1000000;

// Variable to hold how many time has passed since the simulation begun
float         elapsedTime   = 0.0;

bool          breakPoint    = true;

/***************
 * GRID CONFIG *
 ***************/
// Space available to put the ants (grid size)
int         spaceAvailable = (int) screenSize / antSize;

// Varaible to hold text to draw on the screen
char c[20];

int main()
{
    std::srand(std::time(0));

    sf::Clock clock;
    sf::Clock stopwatch;
    float lastTime;

    sf::Font font;
    font.loadFromFile("fonts/Roboto-Black.ttf");

    // Window setup
    sf::RenderWindow window(sf::VideoMode(screenSize, screenSize), "Ants");

    // Since this is a simulation and not a game I will controll the speed using
    // the frame rate. This is not recomended, but for simplicity sake I will be
    // using this for now.
    //window.setFramerateLimit(5);

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

    // Spawning the dead ants
    dead_ants.clear();
    std::ifstream infile("data1.txt");
    //std::ifstream infile("r15.txt");
    if (!infile.is_open())
    {
        std::cout << "Error opening file." << std::endl;
        return 0;
    }

    float dataPosX, dataPosY;
    int antType;
    while (infile >> dataPosX >> dataPosY >> antType)
    {
        int posX, posY;
        do
        {
            posX = std::rand() % spaceAvailable;
            posY = std::rand() % spaceAvailable;
        } while(deadAntGrid[posY][posX] != -1);

        //std::cout << posX << "-" << posY << "-" << dead_ants.size() << std::endl;
        Ant a(nDeadAnts, true, sf::Vector2i(posX, posY), radius, deadAntGrid, aliveAntGrid,
                dead_ants, alive_ants, antSize, spaceAvailable, sf::Vector2f(dataPosX, dataPosY),
                antType, font);
        dead_ants.push_back(a);
        deadAntGrid[posY][posX] = nDeadAnts++;

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
               dead_ants, alive_ants, antSize, spaceAvailable, sf::Vector2f(0,0), 0, font);
        alive_ants.push_back(a);
        aliveAntGrid[posY][posX] = i;
    }

    stopwatch.restart();
    while (window.isOpen())
    {

        if ( ! breakPoint )
        {
            for (int i = 0; i < drawIterations && window.isOpen(); i++)
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    if (event.type == sf::Event::KeyPressed 
                            && event.key.code == sf::Keyboard::Space )
                    {
                        breakPoint = !breakPoint;
                    }
                }

                for(std::vector<Ant>::iterator it = alive_ants.begin();
                        it != alive_ants.end(); it++) 
                {
                    it->update(nIterations, maxIterations);
                }

                if (nIterations < maxIterations)
                {
                    nIterations++;
                }
            }
        }

        // Useful when testing and making the report to show middle execution
        //if (nIterations == 50000 || nIterations == 200000)
            //breakPoint = true;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed 
                    && event.key.code == sf::Keyboard::Space )
            {
                breakPoint = !breakPoint;
            }
        }
                
        window.clear(sf::Color::Black);

        // Draw Grid Lines
        //for (int i = 0; i < spaceAvailable; i++)
        //{
            //sf::RectangleShape line(sf::Vector2f(800, 1));
            //sf::RectangleShape line2(sf::Vector2f(800,1));

            //line.setFillColor(sf::Color::Black);
            //line.setPosition(sf::Vector2f(0, i * antSize));

            //line2.rotate(90);
            //line2.setFillColor(sf::Color::Black);
            //line2.setPosition(sf::Vector2f(i * antSize, 0));

            //window.draw(line);
            //window.draw(line2);
        //}

        // Draw Dead Ants
        for(std::vector<Ant>::iterator it = dead_ants.begin();
                it != dead_ants.end(); ++it)
        {
            it->draw(&window);
        }

        if ( !breakPoint)
        {
            // Draw Alive Ants
            if (nIterations < maxIterations)
            {
                for(std::vector<Ant>::iterator it = alive_ants.begin();
                        it != alive_ants.end(); it++) 
                {
                    it->draw(&window);
                }
            }
        }
        

        // Frames per second calculation
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / lastTime;
        lastTime = currentTime;

        // How many time has passed since the simulation has begun
        float aditionalTime = stopwatch.restart().asSeconds();
        if ( nIterations < maxIterations)
        {
            if (!breakPoint)
                elapsedTime += aditionalTime;
        }

        // Draw the FPS
        sprintf(c, "Time: %fs", elapsedTime);
        std::string string(c);
        sf::String str(string);
        sf::Text text(str, font);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(25);
        window.draw(text);

        // Draw how many iterations already happened
        sprintf(c, "Iteration: %lu", nIterations);
        std::string string2(c);
        sf::String str2(string2);
        sf::Text text2(str2, font);
        text2.setFillColor(sf::Color::White);
        text2.setCharacterSize(25);
        text2.setPosition(0,30);
        window.draw(text2);


        window.display();
    }

    return 0;
}


