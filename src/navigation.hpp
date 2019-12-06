/*
 * navigation.hpp
 * Author: Andrew Masters, Abdulkhaliq Omar
 *
 * navigation.hpp defines and declares the class: Navigation
 */

#ifndef NAVIGATION_HPP
#define NAVIGATION_HPP
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include "Location.hpp"

class Location;
using namespace std;

/**
 * This class puts the Locations together by entering them into a map
 * and connecting them
 */
class Navigation {
  public:
    unordered_map<string, Location*> locations; // map of all locations

    /* adjacency list for each locations */
    vector<Location*> neighbors;

    // Class constructor
    Navigation() {}
    
    /* loadFromFile : this function takes one argument that is the file
     * contains locations with their x an y locations.
     *Params:  in_filename - the name of the file
     *Return: true or false whether the file was read successfully 
     */
    bool loadFromFile(string in_filename);
    
    
    /* loadConnections : this function takes one argument that is the file
     * containing the space-seperated names of pairs of locations
     *Params:  in_filename - the name of the file
     *Return: true or false whether the file was read successfully 
     */

    bool loadConnections(string in_filename);

   /* eucledianDistance : Calculates the eucledian distance between two locations.
    *Params:  location1- the first locations
    *	      location2 - the second location
    *Return: the eucledian distance 
    */
    int eucledianDistance(Location* location1, Location* location2);
    
    /* Finds the shortest path from one location to another
     * in a weighted graph using A* star algorithm
    * Params:
    *     location1- start location
    *     location2- the destination location
    *
    *Return: vector of string containing th shortest path betweens the two locations
    */
    vector<string> AStarSearch(string location1, string location2);
    
    
    // Deconstructor for the class
    ~Navigation();
};

#endif  // NAVIGATION_HPP
