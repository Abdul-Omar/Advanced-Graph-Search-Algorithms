/*
 * ActorGraph.hpp - class declaraion and definition of variables and functions
 * Author: Andrew Masters, Abdikhalik Ahmed
 */

/*
 * ActorGraph class holds a set of actors and movies that connects movies and
 * actors One function loads all the actors and movies into the actors and
 * movies set data structure with the 'loadFromFile' function
 *
 * The actors and movies are then connected together with the 'buildgraph'
 * function
 *
 * The shortest of movies and actors between two different actors is found
 * with the 'shortestPath' function
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include "Actor.hpp"
#include "Movie.hpp"

// declare classes to
class Movie;
class Actor;
using namespace std;

class ActorGraph {
    // protected:
    // Maybe add class data structure(s) here
  public:
    set<Actor*, ActorComparator> actors;  // list of all actors in the file

    set<Movie*, movieComparator> movies;  // set of all movies in the file

    // Constuctor of the Actor graph
    ActorGraph(void);

    /* loadFromFile : this function takes in two arguments, one that is the file
     * in which actors, movies, and the year of those movies exist. The other
     * argument determines weighted or unweighted graphs. All this information
     * is then stored in the data structure of the class ActorGraph
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    /* buildGraph : this function takes the actors and movies data structure
     * that already exists in this class (ActorGraph) and connects the actors
     * that acted in the same movie */
    void buildGraph();

    /* shortestPath : this function takes in two arguments both being of the
     * class Actor in order to find the shortest path between the two. This
     * function uses the concept of a BFS to determine the shortest number of
     * movies between two different actors
     */
    vector<string> shortestPath(Actor*& actor1, Actor*& actor2);

    // Deconstructor; releases all objects stored in the heap; i.e. actors and
    // movies
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
