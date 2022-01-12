#include "graph.h"

#include <math.h>
#include <cmath> 
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <queue>
#include <map>

#define earthRadiusKm 6371.0

using namespace std;


/**
 * Default Graph constructor
 */
Graph::Graph() { }


/**
 * Construct a graph given two paths to two CSV files
 * @param airport_path path to the Airport CSV file
 * @param route_path path to the Route CSV file
 */
Graph::Graph(string airport_path, string route_path) {
    // Read the airport CSV and initialize vertexes
    readAirportCSV(airport_path);

    // Read route CSV and create edges between vertexes
    for (auto i : readRouteCSV(route_path)) insertEdge((int) i[0], (int) i[1], i[2]);    
}

/**
 * Reads from a CSV file containing a database of airports 
 * Parses the data and stores relevant information using the Airport class
 * Populates a list of airports with their Code as an index and the Airport object as a value
 * @param airport_path path to the Airport CSV file
 */
void Graph::readAirportCSV(string airport_path) {
    // Open airport file for reading
    std::ifstream data(airport_path);
    string line;

    if (data.is_open()) {
        // Get a line from the file and store it in line
        while(getline(data, line)) {
            
            stringstream stream(line);
            string line2;
            auto temp = vector<string>();

            // Parse the line by commas
            while (getline(stream, line2, ',')) temp.push_back(line2);

            // Populate airport list
            airport_list[stoi(temp[0])] = Airport(temp[1], temp[2], temp[3], temp[4], temp[5], stod(temp[6]), stod(temp[7]), stoi(temp[0]));

            // Initialize empty value in adjacency list for the current airport
            adjacency_list[stoi(temp[0])] = pair<vector<Edge>, vector<Edge>>();
            verticeCount++;
        }
    } else throw std::invalid_argument("Incorrect filepath");

    data.close();
}

/**
 * Reads from a CSV file containing a database of routes 
 * @param route_path path to the Route CSV file
 * @return a vector containing a vector of doubles where the first argument is the first airport's code, the second argument is the second airport's code, and the third argument is the distance between the two airports
 */
vector<vector<double>> Graph::readRouteCSV(string route_path) {
    // Open route file for reading
    ifstream data(route_path);
    string line;

    auto toRet = vector<vector<double>>();

    if (data.is_open()) {
        // Get a line from the file and store it in line
        while(getline(data, line)) {
            stringstream stream(line);
            string line2;

            auto temp = vector<string>();

            // Parse the line by commas
            while (getline(stream, line2, ',')) temp.push_back(line2);

            // Makes sure no rogue data breaks the code
            if (temp[3] == "\\N" || temp[5] == "\\N") continue;  

            auto row = vector<double>();

            // Store airport codes
            auto airport1 = stod(temp[3]);
            auto airport2 = stod(temp[5]);

            // Push back codes to current row
            row.push_back(airport1);
            row.push_back(airport2);

            // Find distance, or weight, between the two airports
            // Taken from https://stackoverflow.com/questions/10198985/calculating-the-distance-between-2-latitudes-and-longitudes-that-are-saved-in-a
            double dist = distanceEarth(airport_list[airport1].getLatitude(), airport_list[airport1].getLongitude(), airport_list[airport2].getLatitude(), airport_list[airport2].getLongitude());

            // Push back distance to current row
            row.push_back(dist);

            // Push back row to vector we will return
            toRet.push_back(row);
        }
    } else throw invalid_argument("Incorrect filepath"); // Handle incorrect filepaths

    data.close();
    return toRet;
}

// This function converts decimal degrees to radians
double Graph::deg2rad(double deg) {
  return (deg * M_PI / 180);
}

//  This function converts radians to decimal degrees
double Graph::rad2deg(double rad) {
  return (rad * 180 / M_PI);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double Graph::distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

/**
 * Creates an edge between a source and target Vertex with distance as weight
 * @param source Source airport code
 * @param target Target airport code
 * @param rating Rating of the weight, in this case distance between the airports
 */
void Graph::insertEdge(Vertex source, Vertex target, double rating) {

    // Insert the edge to the index of the source airport
    adjacency_list[source].first.emplace_back(Edge(source, target, rating));

    // Insert the edge to the index of the destination airport
    adjacency_list[target].second.emplace_back(Edge(source, target, rating));

    // Increase the edge count
    edgeCount++;
}

/**
 * Checks whether a Vertex exists within our graph
 * @param vertex The code of the Airport to check
 * @return true if present, else false
 */
bool Graph::vertexExists(Vertex vertex) { return adjacency_list.count(vertex); }

/**
 * Checks whether an edge exists between a source and target Vertex in the graph
 * @param source Source airport code
 * @param target Target airport code
 * @return true if edge exists, else false
 */
bool Graph::edgeExists(Vertex source, Vertex target) {
    // Create a temporary edge between the source and target
    auto e = Edge(source, target);

    // Iterate through edges of the source in our adjacency list
    for (auto& edge : adjacency_list.at(source).first) {
        // Check if temp edge is equal to an edge we find in our list, if so return true
        if (edge == e) return true;
    }

    // If no edges are foumnd, return false
    return false;
}

/**
 * Get all incoming edges to a specific vertex
 * @param vertex The code of the airport to check
 * @return a vector of vertex's containing the codes of all airports for which there is an incoming edge to the passed vertex
 */
vector<Vertex> Graph::getIncoming(Vertex vertex) {
    // Create an empty vector of vertexes to store incoming vertexes
    auto adjacent = vector<Vertex>();

    // Iterate through incoming edges to vertex in adjacency list
    for (auto& edge : adjacency_list.at(vertex).second) adjacent.push_back(edge.source); // Add all edges to our adjacent vertex

    return adjacent;
}

/**
 * Get all outgoing edges to a specific vertex
 * @param vertex The code of the airport to check
 * @return a vector of vertex's containing the codes of all airports for which there is an outgoing edge to the passed vertex
 */
vector<Vertex> Graph::getOutgoing(Vertex vertex) {
    // Create an empty vector of vertexes to store outgoing vertexes
    auto adjacent = vector<Vertex>();

    // Iterate through outgoing edges to vertex in adjacency list
    for (auto& edge : adjacency_list.at(vertex).first) adjacent.push_back(edge.target); // Add all edges to our adjacent vertex

    return adjacent;
}

/**
 * Find the distance between a source and destination vertex
 * @param source Source vertex
 * @param dest Destination vertex
 * @return double distance between the two vertex's
 */
double Graph::getDistance(Vertex source, Vertex dest) {
    // Creates a temp edge between the source and destination
    auto e = Edge(source, dest);

    // Iterate through connected edges of the source vertex in adjacency list
    for (auto& edge : adjacency_list.at(source).first)
        if (e == edge) return edge.getWeight(); // Return weight of edge if a match is found

    // If no match is found, return weight of temp edge
    return e.getWeight();
}

/**
 * Print all the entries in the graph
 */
void Graph::printGraph() {
    for (auto entry : adjacency_list) {
        for (auto f : entry.second.first) cout << f << endl;
        cout << endl;

        for (auto f : entry.second.second) cout << f << endl;
        cout << endl << endl;
    }

    cout << endl << "Created graph with " << verticeCount << " vertices and " << edgeCount << " edges." << endl;
}

/**
 * BFS traversal of the graph from a source vertex
 * @param source Source vertex
 * @return a vector of airports that are connected to the source airport
 */
vector<Airport> Graph::BFS(Vertex source) {
    if (!vertexExists(source)) throw invalid_argument("Source does not exist"); // Check if source exists
    
    // Initialize a queue of vertexes to iterate through
	queue<Vertex> q;

    // Initialize a map from ints to bools to store the vertexes we have visited
	unordered_map<int, bool> visited(false);

    // Initialize a vector of Airports to store the route from the traversal
	vector<Airport> route;

    // Visit source
    visited[source] = true;

    // Add source to the queue
	q.push(source);

	while (!q.empty()) {
        // Add current vertex to the front of the queue
		Vertex current = q.front();

        // Add current airport to the route
        route.push_back(airport_list[current]);

        // Pop current vertex from the queue
		q.pop();
        
        // Iterate through vertexes of outgoing edges of the source vertex
		for (auto& r : getOutgoing(source)) {
            // If we haven't visited the vertex, then visit the vertex
            if (!visited[r]) {
                visited[r] = true;
                q.push(r);
            }
		}
	}
	return route;
}

Vertex Graph::minDist(map<Vertex, pair<int, Vertex>> algo, vector<Vertex> unvisited) { 
    int currentMinDistance = INT_MAX;
    int currentMinVertex = -1;

    //every vertex that is in unvisited must be in algo
    for (Vertex x : unvisited) {
        if (algo[x].first <= currentMinDistance) {
            currentMinDistance = algo[x].first;
            currentMinVertex = x;
        }
    }

    //for testing purposes.  This should never happen if dijsktras is working correctly
    if (currentMinVertex == -1) {
        std::cout << "???" << std::endl;
    }
    return currentMinVertex;
}

vector<int> Graph::recursivePath(unordered_map<int, int> parentMap, int curr, vector<int> populate_path) 
{ 
  
  if (parentMap[curr] == -1) 
    return populate_path;
  populate_path.push_back(curr);
  return recursivePath(parentMap, parentMap[curr], populate_path); 
  
  cout << curr << endl; 
} 

vector<int> Graph::print(unordered_map<int, int> dist, int n, unordered_map<int, int> parent, vector<Vertex> vertices, Vertex source, Vertex dest, vector<int> populate_path){
  for (int i = 1; i < n; i++) 
  { 
    if (vertices[i] == dest) {
      std::cout << "Your Flight Information: \n" << std::endl;
      
      cout << source << " -> " << vertices[i] << "   Total Distance: " <<  dist[vertices[i]]
           << "km \n" << endl;
    }
  }
  vector<int> ret = recursivePath(parent, dest, populate_path);
  return ret; 
}


map<Vertex, pair<int, Vertex>> Graph::dijkstra(Vertex source) 
{
    map<Vertex, pair<int, Vertex>> toReturn;
    vector<Vertex> visited;
    vector<Vertex> unvisited;

    //let distance of start vertex from start vertex = 0
    unvisited.push_back(source);
    toReturn.insert(pair<int, pair<int, Vertex>>(source, pair<int, Vertex>(0, source)));

    //let distance of all other vertices from start = infinity
    //go through each airport that is indirectly or directly connected to our source
        //get the neighbors of each airport we already know is connected to the source
        //loop back through all our known airports we need to visit and check if the neighbors are
        //already known to be connected.  if they are not known, add the vertex to both unvisited
        //and our map so we know it is connected
    for (auto it = toReturn.begin(); it != toReturn.end(); it++) {
        vector<Vertex> neighbors = getOutgoing(it->first);
        vector<Vertex> tempNeighbors = getIncoming(it->first);
        for (Vertex incoming: tempNeighbors) {
            bool alreadyAccountedFor = false;
            for (Vertex outbound : neighbors) {
                if (incoming == outbound) {
                    alreadyAccountedFor = true;
                    break;
                }
            }
            if (!alreadyAccountedFor) {
                neighbors.push_back(incoming);
            }
        }
        for (Vertex vert : neighbors) {
            bool ah = false;
            for (auto it2 = toReturn.begin(); it2 != toReturn.end(); it2++) {
                if (it2->first == vert) {
                    ah = true;
                }
            }
            if (!ah) {
                toReturn.insert(pair<int, pair<int, Vertex>>(vert, pair<int, Vertex>(999999, -999999)));
                unvisited.push_back(vert);
            }
        }
    }
    while(!unvisited.empty()) {
        //1) visit the unvisited vertex with the smallest known distance from the start vertex
        Vertex current = minDist(toReturn, unvisited);
        //2) for the current vertex, examine its unvisited neighbors
        vector<Vertex> neighbors = getOutgoing(current);
        for (Vertex neighbor : neighbors) {
            bool temp = false;
            for (Vertex unvisitedVertex : unvisited) {
                if (unvisitedVertex == neighbor) {
                    temp = true;
                    break;
                }
            }
            if (!temp) {
                neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), neighbor), neighbors.end());
            }
        }

        //3) for the current vertex, calculate distance of each neighbor from the start vertex
        //4) if the calculated distance of a vertex is less than the known distance, update the shortest distance
        //5) update the previous vertex for each of the updated distances
        for (Vertex neighbor : neighbors) {
            //toReturn[current].first + getDistance(current, neighbor)
            int newDistance = toReturn[current].first + getDistance(current, neighbor);
            if (toReturn[neighbor].first > newDistance) {
                toReturn[neighbor].first = newDistance;
                toReturn[neighbor].second = current;
            }
        }

        //6) add the current vertex to the list of vistied vertices
        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), current), unvisited.end());
        visited.push_back(current);
    }
    //until all vertices visited
    return toReturn;
}

void Graph::printDijkstraMap(std::map<Vertex, pair<int, Vertex>> algo) {
    for (auto it = algo.begin(); it != algo.end(); it++) {
        if (airport_list[it->first].getName() != "" && airport_list[(it->second).second].getName() != "") {
            std::cout << "Deperature Airport : " << airport_list[it->first].getName();
            std::cout << " | Shortest Distance : " << (it->second).first;
            std::cout << " | Previous Airport : " << airport_list[(it->second).second].getName() << std::endl;
        }
    }
}

/**
 * @brief Prints the path from a source to a destination vertex
 * 
 * @param source 
 * @param destination 
 */
void Graph::printPath(Vertex source, Vertex destination) {
    auto path = findPath(source, destination);
    for (unsigned i = 0; i < path.size(); i++) {
        auto curr = airport_list[path[i]];
        if (i == 0) cout << "\nSource Airport Name: " << curr.getName() << " | Source Airport Code: " << curr.getCode() << endl;
        else {
            auto prev = airport_list[path[i - 1]];
            if (i == path.size() - 1) cout << "\nDestination Airport Name: " << curr.getName() << " | Destination Airport Code: " << curr.getCode();
            else cout << "\nCurrent Airport Name: " << curr.getName() << " | Current Airport Code: " << curr.getCode();
            cout << " | Distance from previous airport: " << distanceEarth(curr.getLatitude(), curr.getLongitude(), prev.getLatitude(), prev.getLongitude()) << "km" << endl;
        } 
    }
}

/**
 * @brief Helper function to return the Pixel values corresponding to the latitude and longitude coordinates of a point
 * 
 * @param lat 
 * @param lng 
 * @param png 
 * @return vector<int> 
 */
vector<float> Graph::getXYCoord(float lat, float lng, double width, double height) {
    float radius = width / (2 * M_PI);
    float FE = 180;
    // Derive corresponding pixel values from airport latitude and longitude coordinates using Mercator Projection
    float latrad = deg2rad(lat);
    float lonrad = deg2rad(lng + FE);
    float x = lonrad * radius;
    float yFromEquator = radius * log(tan(M_PI / 4 + latrad / 2));
    float y = height / 2 - yFromEquator;
    vector<float> toReturn;
    toReturn.push_back(x);
    toReturn.push_back(y);
    return toReturn;
}

/**
 * @brief Calls recursive helper function to populate path vector, returns a vector with elements being stops on a route from source to destination
 * 
 * @param source 
 * @param destination 
 * @return vector<Vertex> 
 */
vector<Vertex> Graph::findPath(Vertex source, Vertex destination) {
    vector<Vertex> path;
    findPath(source, destination, path);
    return path;
}

/**
 * @brief Recursively populate a vector with the shortest path from one airport to another using djikstra's algorithm
 * 
 * @param source 
 * @param destination 
 * @param path 
 */
void Graph::findPath(Vertex source, Vertex destination, vector<Vertex>& path) {
    auto d = dijkstra(source);
    if (d.find(destination) == d.end()) {
        cout << "No Route Exists" << endl;
        return;
    }
    if (d[destination].second == source) {
        if (!count(path.begin(), path.end(), source)) path.push_back(source);
        if (!count(path.begin(), path.end(), destination))path.push_back(destination);
        return;
    }
    findPath(source, d[destination].second, path);
    findPath(d[destination].second, destination, path);
}

/**
 * Function to visualize our graph by drawing the vertices, or Airports, of the graph onto a world map
 */
void Graph::graphAirportVisualization() {
    cs225::PNG png;
    // Read from worldmap image which is WGS84 to be compatible with our projection code
    png.readFromFile("worldmap.png");
    for (auto& a : airport_list) {
        // Derive corresponding pixel values from airport latitude and longitude coordinates using helper function
        float x = getXYCoord(a.second.getLatitude(), a.second.getLongitude(), png.width(), png.height())[0];
        float y = getXYCoord(a.second.getLatitude(), a.second.getLongitude(), png.width(), png.height())[1];

        // Change color of airport and surrounding 8 pixels to red for more visibility on map
        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                // Ensure that x and y values of pixel we are coloring are within the dimensions of the map
                if (x + i >= 0 && x + i <= (int) png.width() && y + j >= 0 && y + j <= (int) png.height()) {
                    // Color the pixels red
                    HSLAPixel& pixel = png.getPixel((int) x + i, (int) y + j);
                    pixel.h = 0;
                    pixel.s = 1;
                    pixel.l = .5;
                    pixel.a = 1;
                }
            }
        }
    }
    png.writeToFile("worldMapWithAirports.png");
}

/**
 * @brief Visualize our graph by outputting it on a map with Airports colored red and the route between a source and destination airport colored green
 * 
 * @param source 
 * @param destination 
 */
void Graph::graphAirportAndRouteVisualization(Vertex source, Vertex destination) {
    graphAirportVisualization();
    PNG png;
    // Read from image created by graphAirportVisualization() function
    png.readFromFile("worldMapWithAirports.png");

    // Create a vertex to populate with the path from the source to the destination
    vector<Vertex> path;

    // Call recursive helper function to find the path
    findPath(source, destination, path);
    // Iterate through the path
    for (unsigned i = 1; i < path.size(); i++) {
        Vertex start = path[i - 1];
        Vertex end = path[i];

        // Get X and Y coordinates for the start and end airports respectively
        auto vec1 = getXYCoord(airport_list[start].getLatitude(), airport_list[start].getLongitude(), png.width(), png.height());
        auto vec2 = getXYCoord(airport_list[end].getLatitude(), airport_list[end].getLongitude(), png.width(), png.height());
        float x1 = vec1[0];
        float y1 = vec1[1];
        float x2 = vec2[0];
        float y2 = vec2[1];

        // Ensure x2 > x1
        if (x2 < x1) {
            float temp = x2;
            x2 = x1;
            x1 = temp;
            temp = y2;
            y2 = y1;
            y1 = temp;
        }

        // Generate line using Bresenham's Line Generation Algorithm
        float dy = y2 - y1;
        float dx = x2 - x1;
        float m = 2 * dy;
        float slopeError = m - dx;
        for (int x = x1, y = y1; x <= x2; x++) {
            // Add slope and increase angle
            slopeError += m;
        
            // Update slope error when it reaches limit
            if (slopeError >= 0) {
                y++;
                slopeError  -= 2 * dx;
            } else {
                y--;
                slopeError += 2 * dx;
            }

            // Change color of route and surrounding 8 pixels to green for more visibility on map
            for (int i = -2; i <= 2; i++) {
                for (int j = -2; j <= 2; j++) {
                    // Ensure that x and y values of pixel we are coloring are within the dimensions of the map
                    if (x + i >= 0 && x + i <= (int) png.width() && y + j >= 0 && y + j <= (int) png.height()) {
                        // Color the pixels green
                        HSLAPixel& pixel = png.getPixel((int) x + i, (int) y + j);
                        pixel.h = 120;
                        pixel.s = 1;
                        pixel.l = .5;
                        pixel.a = 1;
                    }
                }
            }
        }
        
    }
    png.writeToFile("worldMapWithAirportsAndRoute.png");
}