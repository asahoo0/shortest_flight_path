#include "graph/graph.h"
#include "graph/edge.h"
#include <iostream>
using namespace std;

int main() {
  
  std::string source; //inputed source
  std::string destination; //inputed destination
  int s; //source converted to int
  int d; //destination converted to int
  bool ok = false; //whether or not user input is ok
  auto a = Graph("assets/airports.csv", "assets/routes.csv"); //graph of all data
  
  //prompt user for inputs
  std::cout <<"\n" <<std::endl;
  std::cout<< "Please enter the number of the airport you want to fly from" << endl;
  std::cin >> source;
  std::cout<< "Please enter the number of your destination airport" << endl;
  std::cin >> destination;
  
  //check if string inputs are int
  try{
    //try to convert string to int
    s = std::stoi(source);
    d = std::stoi(destination);
    ok = true; //valid inputs
  } catch(std::invalid_argument a) {
    ok = false; //invalid inputs
  }
  
  while (!ok && !(a.vertexExists(s) && a.vertexExists(d) && a.edgeExists(s,d))){
    //loop based on invalid result
    std::cout <<"\n" <<std::endl;
    std::cout <<"Sorry your input was invalid or a route does not exist. \nPlease make sure the airport numbers are valid." <<std::endl;
    std::cout <<"\n" <<std::endl;
    
    //prompt user again
    std::cout<< "Please enter the number of the airport you want to fly from" << endl;
    std::cin >> source;
    std::cout<< "Please enter the number of your destination airport" << endl;
    std::cin >> destination;
    
    //check if string inputs are int again
    try{
      //try to convert string to int
      s = std::stoi(source);
      d = std::stoi(destination);
      ok = true; //valid inputs
    } catch(std::invalid_argument a) {
      ok = false; //invalid inputs
    }
  }
  
  //Loads all info for valid source and destination airports
  std::cout <<"\n" <<std::endl;
  std::cout <<"Your path will be represented with a green line." <<std::endl;
  std::cout <<"Loading Flight Path..." <<std::endl;
  std::cout <<"" <<std::endl;
  
  //path taken by djikstra
  vector<Vertex> path;
  a.findPath(s, d, path);
  
  int dist = 0; //total distance
  
  //check if path is empty
  if (path.size() == 0) {
    return 0;
  }
  //all flights available for each airport visited on dijkstra's
  //uses BFS to list all fights
  for (unsigned i = 0; i < path.size() - 1; i++){
    vector<Airport> port = a.BFS(path[i]);
    std::cout << "All Flights from ";
    std::cout << path[i];
    std::cout << ": ";
    for (auto j: port) {
      std::cout << j.getCode();
      std::cout << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
  
  for (unsigned i = 0; i < path.size() - 1; i++) { //printing djikstra's min dist
    Vertex e = path[i + 1];
    Vertex b = path[i];
    //distance from b->e
    std::cout << b;
    std::cout << " -> " ;
    std::cout << e;
    std::cout << " Distance: ";
    std::cout << a.getDistance(b,e);
    std::cout << " km" <<std::endl;
    dist += a.getDistance(b,e);
  }
  std::cout << "Total Flight Distance: ";
  std::cout << dist;
  std::cout << " km" <<std::endl;
  
  a.graphAirportAndRouteVisualization(s,d);
  std::cout <<"\n" <<std::endl;
  std::cout << "Thank you for using our Shortest Flight Implementation.\n" << std::endl;
  return 0;
}