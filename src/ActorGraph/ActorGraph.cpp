/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
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

        // add this actor to actors starring in this movie
        newMovie->addActor(newActor);

        bool movieFound = false;
        bool actorFound = false;

        // add actor to list of actors
        if (actors.find(newActor) == actors.end()) {
            actors.insert(newActor);
        } else {
            auto iter = actors.find(newActor);
            actorFound = true;
        }
        // add actor to list of actors
        if (movies.find(newMovie) == movies.end()) {
            // add movie to list of movies.
            movies.insert(newMovie);
        } else {
            auto iter = movies.find(newMovie);

            (*iter)->addActor(newActor);
            movieFound = true;
        }

        if (movieFound) delete (newMovie);
        if (actorFound) delete (newActor);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/* function to build nodes and their connections */
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
                actor1->connectActors(
                    make_pair(actor2, movie));  // connect actors
            }
        }
    }
}

vector<string> ActorGraph::shortestPath(Actor*& actor1, Actor*& actor2) {
    // initialize all distances to zero
    for (auto iter = actors.begin(); iter != actors.end(); ++iter) {
        (*iter)->dist = std::numeric_limits<double>::infinity();
    }

    queue<Actor*> toExplore;

    vector<string> path;  // holds the shortest path from one actor to another

    auto iter = actors.find(actor1);

    Actor* start = *iter;

    start->dist = 0;

    toExplore.push(start);

    while (!toExplore.empty()) {
        Actor* current = toExplore.front();

        // add Name to current Path
        path.emplace_back(current->name);

        toExplore.pop();

        if (current == actor2) break;  // if we have reached thedesination actor

        auto it = current->neighbors.begin();

        for (; it != current->neighbors.end(); ++it) {
            // movie neighbor shares with current actor
            Movie* sharedMovie = (*it).second;

            // get the neighbor
            auto iter3 = actors.find((*it).first);

            Actor* neighbor = *iter3;

            if (neighbor->dist == INT_MAX) {
                neighbor->dist = current->dist + 1;
                neighbor->prev = current;
                // add movie to the path
                path.emplace_back(sharedMovie->getName());
                toExplore.push(neighbor);
            }
        }
    }

    return path;
}
