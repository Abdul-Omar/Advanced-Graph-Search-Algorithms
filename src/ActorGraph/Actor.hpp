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
};

/* used by un_oredered set for hashing */
struct ActorComparator {
    bool operator == (Actor* const& a, Actor* const& b) {
        return a->name == b->name;
    }
};

struct Actor_hash {
    std::size_t operator()(const Actor*& actor) const {
        return std::hash<std::string>()(actor->name) ^
               hash<string>()(actor->name);
    }
};
#endif
