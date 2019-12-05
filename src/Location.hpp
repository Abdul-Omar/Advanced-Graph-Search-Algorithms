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

    int xCoord;
    int yCoord;


 
    // constructor for the class
    Location(string name, int x, int y) : name(name), xCoord(x), yCoord(y){};
};



#endif
