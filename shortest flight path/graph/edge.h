/**
 * @file edge.h
 */

#pragma once

#include <limits.h>

#include <string>
#include <vector>
#include <iostream>

using std::string;

typedef int Vertex;

class Airport {
    
    public:

    /**
     * Default constructor
     */
    Airport() { }
    /**
     * Parameterized constructor
     */
    Airport(string name_, string city_, string country_, string IATA_, string ICAO_, double latitude_, double longitude_, int code_) : 
    name(name_), city(city_), country(country_), IATA(IATA_), ICAO(ICAO_), latitude(latitude_), longitude(longitude_), code(code_) {};

    /**
     * Returns the airport's name
     * @return name
     */
    string getName() { return name; }

    /**
     * Returns the airport's city
     * @return city
     */
    string getCity() { return city; }

    /**
     * Returns the airport's country
     * @return country
     */
    string getCountry() { return country; }

    /**
     * Returns the airport's IATA code
     * @return IATA
     */
    string getIATA() { return IATA; }

    /**
     * Returns the airport's ICAO code
     * @return ICAO
     */
    string getICAO() { return ICAO; }

    /**
     * Returns the airport's latitude
     * @return latitude
     */
    double getLatitude() { return latitude; }

    /**
     * Returns the airport's longitude
     * @return longitude
     */
    double getLongitude() { return longitude; }

    /**
     * Returns the airport's code
     * @return code
     */
    int getCode() { return code; }
    
    private:

    string name;
    string city;
    string country;
    string IATA;
    string ICAO;
    double latitude;
    double longitude;
    int code;

};

/**
 * A class to Construct Edges
 */
class Edge {
   public:
    Vertex source;
    Vertex target;

    /**
     * Default Constructor for Edge class
     */
    Edge() : source(-1), target(-1), weight(INT_MIN) { }

    /**
     * Parameter Constructor for Edge class
     * @param u First vertex for the edge
     * @param v Second vertex for the edge
     */
    Edge(Vertex u, Vertex v) : source(u), target(v), weight(INT_MIN) { }

    /**
     * Parameter Constructor for Edge class
     * @param u First vertex for the edge
     * @param v Second vertex for the edge
     * @param w Weight for the edge
     */
    Edge(Vertex u, Vertex v, int w) : source(u), target(v), weight(w) { }

    /**
     * Operator < to compare two edges
     * @param other Edge to compare with
     * @return true if weight is less than other weight, else false
     */
    bool operator<(const Edge& other) const { return weight < other.weight; }

    /**
     * Operator > to compare two edges
     * @param other Edge to compare with
     * @return true if weight is greater than other weight, else false
     */
    bool operator>(const Edge& other) const { return weight > other.weight; }

    /**
     * Operator == to compare two edges
     * @param other Edge to compare with
     * @return true if source == other.source and target == other.target
     */
    bool operator==(Edge& other) const { return (this -> source == other.source) && (this -> target == other.target); }

    /**
     * Getter for weight variable
     * @return weight
     */
    int getWeight() const { return weight; }

    /**
     * Output operator to send data to standard output
     * @param os file to write to
     * @param e Edge to display data of
     * @return os file
     */
    friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        std::string source("Source: "), target(", Target: "), weight(", Weight: ");
        os << source << std::to_string(e.source) << target << std::to_string(e.target) << weight << std::to_string(e.getWeight());
        return os;
    }

   private:
    int weight;
};