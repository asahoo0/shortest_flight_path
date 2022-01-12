/**
 * @file graph.h
 */

#pragma once

#include "edge.h"
#include "../cs225/PNG.h"

#include <unordered_map>
#include <vector>
#include <stdlib.h>
#include <map>
#include <math.h>

using namespace std;
using cs225::PNG;
using cs225::HSLAPixel;


/**
 * A class to construct a Graph
 */
class Graph {
    public:
    
    /**
     * Constructors
     */
    Graph();
    Graph(string airport_path, string route_path);
    
    /**
     * Member functions
     */
    bool edgeExists(Vertex source, Vertex target);
    bool vertexExists(Vertex vertex);
    void insertEdge(Vertex source, Vertex target, double weight);
    void readAirportCSV(string airport_path);
    vector<vector<double>> readRouteCSV(string route_path);
    double getDistance(Vertex source, Vertex dest);
    void printGraph();
    vector<Airport> BFS(int source);

    /*
    Helper function for Dijkstra's Algorithm.
        @param algo : current map from Dijkstra's Algorith.
            The key represents an airport vertex.  The value is a pair.
                The first value of that pair is the shortest path from our source airport that was 
                initially passed to Dijkstra's.  The second value is the Vertex of the previous airport
                in that shortest path.
        @param unvisited : a vector storing all unvisited verticies from Dijkstra's Algortihm

        Returns the vertex amongst the unvisited that contains the shortest distance to the source
        vertex parameter in Dijkstra's Algorithm
    */
    Vertex minDist(std::map<Vertex, pair<int, Vertex>> algo, vector<Vertex> unvisited);

    /*
    Main function for Dijkstra's Algorithm
        @param source : initial vertex

        Returns a map
            The key represents an airport vertex.  The value is a pair.
                The first value of that pair is the shortest path distance from our source parameter.
                The second value is the Vertex of the previous airport in that shortest path.

        let distance of start vertex from start vertex = 0
        let distance of all other vertices from start = infinity
        repeat until all verticies visited
            1) visit the unvisited vertex with the smallest known distance from the start vertex
            2) for the current vertex, examine its unvisited neighbors
            3) for the current vertex, calculate distance of each neighbor from the start vertex
            4) if the calculated distance of a vertex is less than the known distance, update the shortest distance
            5) update the previous vertex for each of the updated distances
            6) add the current vertex to the list of vistied vertices
    */
    std::map<Vertex, pair<int, Vertex>> dijkstra(Vertex source);

    void printDijkstraMap(std::map<Vertex, pair<int, Vertex>> algo);
    vector<float> getXYCoord(float lat, float lng, double width, double height);
    vector<Vertex> findPath(Vertex source, Vertex destination);
    void findPath(Vertex source, Vertex destination, vector<Vertex>& path);
    vector<int> print(unordered_map<int, int> dist, int n, unordered_map<int, int> parent, vector<Vertex> vertices, Vertex source, Vertex dest, vector<int> populate_path);
    vector<int> recursivePath(unordered_map<int, int> parent, Vertex j, vector<int> populate_path);
    void graphAirportVisualization();
    void graphAirportAndRouteVisualization(Vertex source, Vertex destination);
    void printPath(Vertex source, Vertex destination);
    /**
     * Getters
     */
    vector<Vertex> getIncoming(Vertex vertex);
    vector<Vertex> getOutgoing(Vertex vertex);
    int getVerticeCount() { return verticeCount; }
    int getEdgeCount() { return edgeCount; }

    private:
    int verticeCount = 0, edgeCount = 0;
    unordered_map<int, Airport> airport_list;
    unordered_map<int, pair<vector<Edge>, vector<Edge>>> adjacency_list;

    double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
    double deg2rad(double deg);
    double rad2deg(double rad);
};
