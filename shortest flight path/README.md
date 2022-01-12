# CS225 Final Project: Flight Planer
#### Armaan Kumar, Aishani Sahoo, Daniel Keegan, Runqi Shi

## Introduction

In our final project, we are tring to find the shortest path for connecting flights using two datasets from [Open Flight](https://openflights.org/data.html).
We use the [Airports](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat) and [Routes](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat) datasets to build a graph with airports as vertices and routes as edges, with the distance between the two airports on a route as the weight of the edge. Dijkstra's Algorithm is used for finding the shortest path.
We also have a visualization function that generates a graphic output of the flight path for the users.

## Code, data, and results

- **'assets' folder**: The flight and route data as CSV files. Including the original data and two shortened simple versions for development and testing.
- **'cs225' folder**: The cs225 folder for graph visualization by using *cs225::HSLAPixel* and *cs225::PNG*.
- **'graph' folder**: All of our major code is in ***graph.h/.cpp***, including *graph constructor, BFS, Dijsktra* and *visualization*. The ***edge.h*** file contains the *airport class* and *edge class*.
- **'tests' folder**: Test cases.
- **worldMapWithAirports.png**: The graphical output of the program to visualize the graph on a world map with *airports*.
- **worldMapWithAirportsAndRoute.png**: The graphical output of the program to visualize the graph on a world map with *routes* and *airports*.
## How to run

The program can be run by: 
```
make
./final_proj
```

Then, the user is prompted to type in the departue and and destination codes for airports. If the inputs are not valid, the user will be asked to type in again.

The program should print out a path for the user, and generates two pictures. The first visualizes all the airports on the graph and is found in the final project folder with the name: **worldMapWithAirports.png**. The second visualizes their journey and is found in the final project folder with the name: **worldMapWithAirportsAndRoute.png**.

## How to test

To test the code, simply run:
```
make test
./test
```
Our tests will test the functionality of
- Graph construction
- BFS traversal
- Dijskra's algorithm
