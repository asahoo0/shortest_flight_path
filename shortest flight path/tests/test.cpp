#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>


#include "../graph/edge.h"
#include "../graph/graph.h"
#include "catch/catch.hpp"
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"

using std::string;
using std::vector;
using std::unordered_map;
using cs225::HSLAPixel;
using cs225::PNG;


//change tests to fit with graph and bfs together implementation
TEST_CASE("BFS traversal on simple dataset") {
	Vertex source = 1;
	Graph g("tests/simpleAirport.csv",
		"tests/simpleRoute.csv");
	vector<Airport> path = g.BFS(source);

	SECTION("Check visited correct number of airports") {
		REQUIRE(path.size() == 2);
	}

	SECTION("Check visited correct airport first") {
		REQUIRE(path.at(0).getCode() == 1);
	}

	SECTION("Visited airports in correct order") {
		REQUIRE(path.at(0).getCode() == 1);
		REQUIRE(path.at(1).getCode() == 2);
		// REQUIRE(path.at(2).getCode() == 3);
	}
}

TEST_CASE("BFS traversal on full dataset") {
    Vertex source = 1;
    Graph g("assets/airports.csv", "assets/routes.csv");
    vector<Airport> path = g.BFS(source);

    SECTION("Check visited correct airport first") {
        REQUIRE(path.at(0).getCode() == 1);
    }

    SECTION("Visited airports in correct order") {
	REQUIRE(path.at(0).getCode() == 1);
	REQUIRE(path.at(1).getCode() == 3);
	REQUIRE(path.at(2).getCode() == 4);
    }
}

TEST_CASE("Dijkstra no stops") {
  auto g = Graph("tests/simpleAirDij.csv", "tests/simpleRouDij.csv");
  vector<Vertex> path;
  g.findPath(1, 2, path);
  
  SECTION("Correct Distance") {
    Vertex a = path[0]; //source
    Vertex b = path[1]; //dest
    REQUIRE(g.getDistance(a,b) == 106);
  }
  SECTION("Check visited correct airport first") {
    REQUIRE(path.at(0) == 1);
  }
  
  SECTION("Check path size") {
    REQUIRE(path.size() == 2);
  }
  
  SECTION("Visited airports in correct order") {
    REQUIRE(path.at(0) == 1);
    REQUIRE(path.at(1) == 2);
  }
}

TEST_CASE("Dijkstra 1 stop") {
  auto g = Graph("tests/simpleAirDij.csv", "tests/simpleRouDij.csv");
  vector<Vertex> path;
  g.findPath(1, 3, path);
  
  SECTION("Correct Distance") {
    Vertex a = path[0]; //source
    Vertex b = path[1]; //stop
    Vertex c = path[2]; //dest
    REQUIRE(g.getDistance(a,b) == 106);
    REQUIRE(g.getDistance(b,c) == 179);
    REQUIRE(g.getDistance(a,b)+g.getDistance(b,c) == 285);
  }
  
  SECTION("Check visited correct airport first") {
    REQUIRE(path.at(0) == 1);
  }
  
  SECTION("Check path size") {
    REQUIRE(path.size() == 3);
  }
  
  SECTION("Visited airports in correct order") {
    REQUIRE(path.at(0) == 1);
    REQUIRE(path.at(1) == 2);
    REQUIRE(path.at(2) == 3);
  }
}

TEST_CASE("Dijkstra 2 stops") {
  auto g = Graph("tests/simpleAirDij.csv", "tests/simpleRouDij.csv");
  vector<Vertex> path;
  g.findPath(1, 4, path);
  
  SECTION("Correct Distance") {
      Vertex a = path[0]; //source
      Vertex b = path[1]; //stop
      Vertex c = path[2]; //stop
      Vertex d = path[3]; //dest
      REQUIRE(g.getDistance(a,b) == 106);
      REQUIRE(g.getDistance(b,c) == 179);
      REQUIRE(g.getDistance(c,d) == 281);
      REQUIRE(g.getDistance(c,d)+g.getDistance(b,c)+g.getDistance(a,b) == 566);
  }
  
  SECTION("Check visited correct airport first") {
    REQUIRE(path.at(0) == 1);
  }
  
  SECTION("Check path size") {
    REQUIRE(path.size() == 4);
  }
  
  SECTION("Visited airports in correct order") {
    REQUIRE(path.at(0) == 1);
    REQUIRE(path.at(1) == 2);
    REQUIRE(path.at(2) == 3);
    REQUIRE(path.at(3) == 4);
  }
}

TEST_CASE("Nonexistent Desination") {
  auto g = Graph("tests/simpleAirDij.csv", "tests/simpleRouDij.csv");
  vector<Vertex> path;
  g.findPath(1, 5, path); //stop 5 is not in simple dataset
  
  SECTION("Check path size") {
    REQUIRE(path.size() == 0);
  }
  
}

TEST_CASE("Nonexistent Source") {
  auto g = Graph("tests/simpleAirDij.csv", "tests/simpleRouDij.csv");
  vector<Vertex> path;
  g.findPath(5, 3, path); //stop 5 is not in simple dataset
  
  SECTION("Check path size") {
    REQUIRE(path.size() == 0);
  }
  
}

TEST_CASE("Source is Destination") {
  auto g = Graph("tests/simpleAirDij.csv", "tests/simpleRouDij.csv");
  vector<Vertex> path;
  g.findPath(3, 3, path);
  
  SECTION("Check path size") {
    REQUIRE(path.size() == 1);
  }
  
  SECTION("Visited airports in correct order") {
    REQUIRE(path.at(0) == 3);
  }
  
}

TEST_CASE("Dijkstra no stops Large Dataset") {
  auto g = Graph("assets/airports.csv", "assets/routes.csv");
  vector<Vertex> path;
  g.findPath(3830, 3093, path);
  
  SECTION("Check visited correct airport first") {
    REQUIRE(path.at(0) == 3830);
  }
  
  SECTION("Check path size") {
    REQUIRE(path.size() == 2);
  }
  
  SECTION("Visited airports in correct order") {
    REQUIRE(path.at(0) == 3830);
    REQUIRE(path.at(1) == 3093);
  }
}

TEST_CASE("Dijkstra 1 stop Large Dataset") {
  auto g = Graph("assets/airports.csv", "assets/routes.csv");
  vector<Vertex> path;
  g.findPath(2990, 4374, path);
  
  SECTION("Check visited correct airport first") {
    REQUIRE(path.at(0) == 2990);
  }
  
  SECTION("Check path size") {
    REQUIRE(path.size() == 3);
  }
  
  SECTION("Visited airports in correct order") {
    REQUIRE(path.at(0) == 2990);
    REQUIRE(path.at(1) == 2975); //2975 used to connect 2990 and 4374
    REQUIRE(path.at(2) == 4374);
  }
}

TEST_CASE("Graph Visualization Colors Vertex for random airport Red") {
  auto g = Graph("assets/airports.csv", "assets/routes.csv");
  g.graphAirportVisualization();
  PNG png;
  png.readFromFile("worldMapWithAirports.png");
  HSLAPixel pixel = png.getPixel(1462, 624);
  REQUIRE( pixel.h == 0);
  REQUIRE (pixel.s == 1);
  REQUIRE (pixel.l == .5);
  REQUIRE (pixel.a == 1);
}