# Ant Clustering Algorithm/visualisation

This is a class project for my Artificial Intelligence course.

# The Basic Idea

In an ambient with Alive and Dead ants, the Alive ones tend to agroup the dead
ones, thus making more space available for movement. This a simple behaviour that
can be used in real life to organise documents, for example.

# Implementation

Most of the implementation is done using C++ and SFML

# Assignments

The algorithm got more complicated each assignment, adding more stuff for the ants to do
so I separated them into folders.

# Assignment 1

Here is the most basic Ant Clustering Algorithm. You can check the report in /assignment1/report/report.pdf
(it is in Brazilian Portuguese but there are some valuable formulas there).

Here the ants have no weigth and all the probability is calculated through some basic formulas.

Here is an example of the agroupation done by the ants:

Variables: 6000 dead ants, 100 alive ants, 4 milion iterations, 160x160 grid

![Example assignment1](/assignment1/report/figuras/ants_seed1.png)

(a): Initial Board
(b): Radius 1
(c): Radius 5
(d): Radius 10
