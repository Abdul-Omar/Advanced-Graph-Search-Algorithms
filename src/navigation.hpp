/*
 * Location*Graph.hpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#ifndef NAVIGATION_HPP
#define NAVIGATION_HPP
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include "Location.hpp"

// Maybe include some data structures here
class Location;
using namespace std;

/**
 * TODO: add class header
 */
class Navigation {

    public:
   
    unordered_map<string, Location*> locations;  // list of all actors in the file
    vector<Location*> neighbors;
    Navigation(){}

   
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(string in_filename);

    bool loadConnections(string in_filename);

    /* function to build nodes and their connections */
    void buildGraph();
    
    //calculate eucledian distance
    int eucledianDistance(Location* location1, Location* location2);
   
    vector<string> AStarSearch(string location1, string location2);
    // Deconstructor
    ~Navigation();
};


#endif  // NAVIGATION_HPP
