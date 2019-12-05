/*
 * movietraveller.hpp
 * Author: Andrew Masters, Abdulkhaliq Omar
 *
 * ActorGraph.cpp implements the functions defined in ActorGraph.hpp
 * This file has a set number of functions whos purpose is to load the file into
 * the data structure (loadFromFile), build the graph connecting all the actors
 * (buildGraph), and to find the shortest path between two actors.
 *
 */

#ifndef MOVIETRAVELLER_HPP
#define MOVIETRAVELLER_HPP

#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include "Actor.hpp"
#include "Edge.hpp"
#include "Movie.hpp"

// Maybe include some data structures here

using namespace std;
class Movietraveller {
  public:
    Movietraveller() {}

    std::set<Actor*, ActorComparator> actors;  // all the actors in graph

    std::set<Movie*, movieComparator> movies;  // all movies in graph

    vector<Edge*> edges;  // stores all the edges in the graph

    void createEdges();

    bool loadFromFile(char const* in_filename);

    Actor* find(Actor* actor);

    void unionSets(Actor* actor1, Actor* actor2);

    void makeSet(set<Actor*, ActorComparator> actors);
    // Kruskal's algorithm
    vector<Edge*> Kruskals();
    ~Movietraveller();
};

#endif
