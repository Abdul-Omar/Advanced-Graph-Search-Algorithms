/*
 * ActorGraph.cpp
 * Author: Andrew Masters, Abdikhalik Ahmed
 *
 * ActorGraph.cpp implements the functions defined in ActorGraph.hpp
 * This file has a set number of functions whos purpose is to load the file into
 * the data structure (loadFromFile), build the graph connecting all the actors 
 * (buildGraph), and to find the shortest path between two actors.
 *
 */

#include "ActorGraph.hpp"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) {}

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

/* loadFromFile : this function takes in two arguments, one that is the file
 * in which actors, movies, and the year of those movies exist. The other argument
 * determines weighted or unweighted graphs.
 * All this information is then stored in the data structure of the class ActorGraph
 */
bool ActorGraph::loadFromFile(const char* in_filename,
                              bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the current line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the current string before hitting a tab character and put it
            // in 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);

        // create a movie and actor objects
        Actor* newActor = new Actor(actor);
        Movie* newMovie = new Movie(movie_title, year);

        // add actor to list of actors
        if (actors.find(newActor) == actors.end()) {
            actors.insert(newActor);
        } else {
            auto iter = actors.find(newActor);
            delete newActor;
            newActor = *iter;
        }

        // add actor to list of actors
        if (movies.find(newMovie) == movies.end()) {
            // add movie to list of movies.
            movies.insert(newMovie);

            newMovie->addActor(newActor);

        } else {
            if ((newMovie->actors).find(newActor) == (newMovie->actors).end()) {
                auto iter = movies.find(newMovie);
                (*iter)->addActor(newActor);
            }
            delete newMovie;
        }
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/* buildGraph : this function takes the actors and movies data structure that
 * already exists in this class (ActorGraph) and connects the actors that acted
 * in the same movie */
void ActorGraph::buildGraph() {
    for (auto iter = movies.begin(); iter != movies.end(); ++iter) {
        Movie* movie = *iter;
        // get all actors in this movie
        set<Actor*> actorsInMovie = movie->getAllActors();

        // connect all actors in this movie
        for (auto iter2 = actorsInMovie.begin(); iter2 != actorsInMovie.end();
             ++iter2) {
            Actor* actor1 = *iter2;

            for (auto iter3 = actorsInMovie.begin();
                 iter3 != actorsInMovie.end(); ++iter3) {
                Actor* actor2 = *iter3;

                // prevent self loops in graph
                if (actor1->name.compare( actor2->name) == 0) continue;

                pair<Actor*, Movie*> p1 = make_pair(actor1, movie);
                pair<Actor*, Movie*> p2 = make_pair(actor2, movie);
                actor1->connectActors(p2);  // connect actors to create neighbors
                actor2->connectActors(p1);
            }
        }
    }
}

/* shortestPath : this function takes in two arguments both being of the class
 * Actor in order to find the shortest path between the two. This function uses
 * the concept of a BFS to determine the shortest number of movies between two
 * different actors
 */
vector<string> ActorGraph::shortestPath(Actor*& actor1, Actor*& actor2) {
    
    // initialize all distances to zero
    for (auto iter = actors.begin(); iter != actors.end(); ++iter) {
        (*iter)->dist = INT_MAX;
        (*iter)->prev = nullptr;
	(*iter)->sharedMovie = nullptr;
    }

    queue<Actor*> toExplore;

    vector<string> path;  // holds the shortest path from one actor to another

    auto iter = actors.find(actor1);

    if (iter == actors.end()) {
        cout << "actor does not exist " << endl;

        return path;
    }
    // cout << (*iter)->name<<endl;

    Actor* start = *iter;
    start->dist = 0;

    toExplore.push(start);

    while (!toExplore.empty()) {
       
	 Actor* current = toExplore.front();

	toExplore.pop();

        if (current->name.compare( actor2->name)  == 0 )break;  // if we have reached thedesination actor

        auto it = current->neighbors.begin();
        
	for (; it != current->neighbors.end(); ++it) {
           	   
            //movie neighbor shares with current actor
            Movie* sharedMovie = (*it).second;

            // get the neighbor
            auto iter3 = actors.find((*it).first);

            Actor* neighbor = *iter3;

            if (neighbor->dist == INT_MAX) {
                neighbor->dist = current->dist + 1;
                neighbor->prev = current;
		neighbor->sharedMovie = sharedMovie;
                //add movie to the path
                toExplore.push(neighbor);
		
            }
        }
    }
    
  

    auto iterat = actors.find(actor2);

    Actor* current = *iterat;
    
    if ((*iterat)->prev == nullptr) return path;
    
    while(current->prev){  
    
     //string str = "";
	    
     //str = str + "(" + current->name +  ")" + "--" + "[" + current->sharedMovie->getName() +  "]" + "-->";
     path.emplace_back("(" + current->name + ")");
     path.emplace_back("#@" + to_string(current->sharedMovie->getYear()) + "]-->");
     
     path.emplace_back("--[" + current->sharedMovie->getName());

     //path.emplace_back(str);
     current = current->prev;
    
    }
     path.emplace_back("(" + actor1->name + ")");

    return path;
}

// Deconstructor for the class ActorGraph that deletes all objects on the heap
// Both the movies and actors stored on the heap are deleted here
ActorGraph::~ActorGraph() {
    // delete all movies
    for (auto iter = movies.begin(); iter != movies.end(); ++iter) {
        delete *iter;
    }

    // delete all actors
    for (auto iter = actors.begin(); iter != actors.end(); ++iter) {
        delete *iter;
    }
}
