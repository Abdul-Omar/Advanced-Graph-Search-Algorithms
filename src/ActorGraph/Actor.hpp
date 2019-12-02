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

    // to find shortest path between two actors
    Movie* sharedMovie = nullptr;
    Actor* prev = nullptr;
    int dist = 0;
    bool done = false;

    Actor* parent;
    int rank;

    // constructor for the class
    Actor(string name) : name(name){};

    /* THis function essentially acts as the link or edge between two Actor
     * Nodes */
    void connectActors(pair<Actor*, Movie*>& neighbor);
};

/* struct used to compare elements. Needed by set data structure */
struct ActorComparator {
    bool operator()(Actor* const& a, Actor* const& b) {
        // else sort them by names
        return a->name < b->name;
    }
};

#endif
