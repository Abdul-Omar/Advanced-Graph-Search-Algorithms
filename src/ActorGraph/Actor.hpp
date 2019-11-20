#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "Movie.hpp"

class Movie;

using namespace std;
/** This class forms the nodes in the graph
 */
class Actor {
  public:
    string name;  // the name of the actor

    // actor's adjacency list
    vector<pair<Actor*, Movie*>> neighbors;

    Actor* prev = nullptr;
    int dist;

    // constructor for the class
    Actor(string name) : name(name){};

    /* THis function essentially acts as the link or edge between two Actor
     * Nodes */
    void connectActors(pair<Actor*, Movie*> neighbor);

    bool operator<(const Actor*& b) { return (this->name < b->name); }
};

#endif
