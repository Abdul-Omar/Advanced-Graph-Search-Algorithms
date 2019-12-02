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
#include <utility>
#include <set>
#include "Movie.hpp"
#include "Actor.hpp"
#include "Edge.hpp"

// Maybe include some data structures here

using namespace std;
class Movietraveller { 
    protected:
        
	std::set<Actor*, actorCompare> actors;

	std::set<Movie*, movieCompare> movies;

    public:
	Movietraveller() { } 

	bool loadFromFile(char const* in_filename, bool use_weighted_edges);
 
	void MakeSet("not sure yet on what to pass ");  

	Actor* find(Actor* actor);

	void unionSets(Actor* act1, Actor* act2);

};
