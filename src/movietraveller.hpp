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
    vector<Edge*>edgesToDelete;//stores the MST to be deleted after

   /* createEdges : this function takes the actors and movies data structure that
    * already exists in this class (ActorGraph) and connects the actors that acted
    * in the same movie
   */
    void createEdges();
  
    
    /* loadFromFile : this function takes in two arguments, one that is the file
   * in which actors, movies, and the year of those movies exist. The other
   * argument determines weighted or unweighted graphs. All this information is
   * then stored in the data structure of the class ActorGraph
   */
    bool loadFromFile(char const* in_filename);

    /* find : this function finds the sentinel of a node
    * PARAMS:  actor-the node whose sentinel to find
    * RETURN: true or false whether the file was read successfully
    */
    Actor* find(Actor* actor);

     /* unionSets : this function merges two dijoint sets
    * PARAMS:  actor1, actor2- the two disjoint sets to merge
    * RETURN: none
    */
    void unionSets(Actor* actor1, Actor* actor2);
     
    /* makeSet : creates n disjoint sets(initializes n disjoint sets)
    * PARAMS:  actors- the disjoint sets to initialize
    * Return: NONE
    */
    void makeSet(set<Actor*, ActorComparator> actors);
    
    
    /* Kruskals : this function implements Kruskal's algorithm
    * to produce minimum spanning tree(MST) of the graph
    * PARAMS: NONE
    * RETURN: vector containing all the edges in MST.
    */ 
    vector<Edge*> Kruskals();
    
    /* destructor for the class */
    ~Movietraveller();
};

#endif
