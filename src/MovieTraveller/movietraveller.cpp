/*
 * movietraveller.cpp
 * Author: Andrew Masters, Abdulkhaliq Omar
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
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "Edge.hpp"


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
 * in which actors, movies, and the year of those movies exist. The other
 * argument determines weighted or unweighted graphs. All this information is
 * then stored in the data structure of the class ActorGraph
 */
bool loadFromFile(const char* in_filename,
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
                if (actor1->name.compare(actor2->name) == 0) continue;

                // pair<Actor*, Movie*> p1 = make_pair(actor1, movie);
                pair<Actor*, Movie*> p2 = make_pair(actor2, movie);
                actor1->connectActors(
                    p2);  // connect actors to create neighbors
                          // actor2->connectActors(p1);
            }
        }
    }
}

void MakeSet(set<Actor*, ActorComparator> actors){
  
   //initialize a disjoint set of all actors with parent being nullptr
   for( auto iter = actors.begin();  iter != actors.end(); ++iter) {
      //set parent to itself
      actorMap[*iter] = *iter;
 
   }

} 

Actor* find(Actor* actor){ 





}

void unionSets(Actor* actor1, Actor* actor2) { 






}

