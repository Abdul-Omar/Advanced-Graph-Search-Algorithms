/*
 * Actor.hpp
 * Author: Andrew Masters, Abdulkhaliq Omar
 *
 * Actor.hpp defines, declares, and implements the actor class
 *
 * This actor class creates an actor and holds all the neighbors
 * or costars of the actor.
 *
 * This class forms the nodes by which the graph will be built on.
 */

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

    vector<Actor*> children;  // all the children of this sentinel actor

    Actor* parent;
    int rank;

    // constructor for the class
    Actor(string name) : name(name){};

    /* This function creates a link between two nodes */
    void connectActors(pair<Actor*, Movie*>& neighbor) {
        neighbors.push_back(neighbor);
    }
};

/* struct used to compare elements. Needed by set data structure */
struct ActorComparator {
    bool operator()(Actor* const& a, Actor* const& b) {
        // else sort them by names
        return a->name < b->name;
    }
};

#endif
