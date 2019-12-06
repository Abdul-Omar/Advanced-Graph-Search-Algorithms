/*
 * Location.hpp - class declaraion and definition of variables and functions
 * Author: Andrew Masters, Abdulkhaliq Omar
 */
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
/** This class forms the nodes in the graph
 */
class Location {
  public:
    string name;  // the name of the actor

    // location's adjacency list
    vector<Location*> neighbors;

    Location* prev = nullptr;
    int dist = 0;
    bool done = false;

    int xCoord;//x coordinate of location
    int yCoord;//y coordinate of location

    // constructor for the class
    Location(string name, int x, int y) : name(name), xCoord(x), yCoord(y){};
};

#endif
