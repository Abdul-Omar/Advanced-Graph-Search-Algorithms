/*
 * ActorGraph.hpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include "Actor.hpp"
#include "Movie.hpp"

// Maybe include some data structures here
class Movie;
class Actor;
using namespace std;

/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    // Maybe add class data structure(s) here

    set<Actor*> actors;  // list of all actors in the file

    set<Movie*, movieComparator> movies;  // set of all movies in the file

    // adjency list, each actor mapped against co-starring actors

  public:
    /**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);

    // Maybe add some more methods here

    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
     * movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    /* function to build nodes and their connections */
    void buildGraph();

    /* finds the shortest path between any two actors in the graph */
    vector<string> shortestPath(Actor*& actor1, Actor*& actor2);
    
    // Deconstructor
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
