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

// Maybe include some data structures here
class Location;
using namespace std;

/**
 * This class puts the Locations together by entering them into a map
 * and connects
 */
class Navigation {
  public:
    unordered_map<string, Location*> locations; // map of all locations

    // list of all neighbors
    vector<Location*> neighbors;

    // Class constructor
    Navigation() {}

    bool loadFromFile(string in_filename);

    bool loadConnections(string in_filename);

    // calculate eucledian distance
    int eucledianDistance(Location* location1, Location* location2);

    vector<string> AStarSearch(string location1, string location2);
    // Deconstructor
    ~Navigation();
};

#endif  // NAVIGATION_HPP
