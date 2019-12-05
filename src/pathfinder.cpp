/*
 * pathfinder.cpp
 * Author: Andrew Masters, Abdulkhaliq Omar
 *
 * pathfinder.cpp implements necessary functions to run the program
 *
 * Functions implemented here: loadTestPairs and dijkstra
 *
 * Also includes a struct ActorComparator that is used for the dijkstra function
 * And main to run compile the code and run the program
 *
 */

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "Movie.hpp"

using namespace std;

/* struct used to compare elements. Needed by set data structure (Used for dijkstra*/
struct ActorComparator2 {
    bool operator()(pair<int, Actor*> const& a, pair<int, Actor*> const& b) {
        return a.first > b.first;
    }
};

/* Loads all pairs that is contained in the given file, extracts them and enters them
 * into a vector pair that is returned.
 */
bool loadTestPairs(string in_filename, vector<pair<string, string>>& pair) {
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

            // get the current string before hitting a tab character and put
            // it in 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }

        string actor1(record[0]);
        string actor2(record[1]);

        pair.emplace_back(make_pair(actor1, actor2));  // add to list of pairs
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

    infile.close();
    return true;
}

/* Finds the shortest path in a weighted graph
 * Uses the Actor and Movie class to locate paths from one given actor
 * to another. Enters all relevant neighbors of actor1 into a queue
 * and after sets the distance for all, will set a path from actor1 to
 * actor2. The path is then read backward and put into a vector of string
 * that is returned.
 */
vector<string> dijkstra(Actor* actor1, Actor* actor2,
                        set<Actor*, ActorComparator>& actors) {
    vector<string> path;

    // Ensure actor1 exists
    auto iter = actors.find(actor1);

    if (iter == actors.end()) {
        cout << "actor does not exist " << endl;

        return path;
    }
	// Ensure actor2 exists
    auto iter2 = actors.find(actor2);

    if (iter2 == actors.end()) {
        cout << "actor does not exist " << endl;

        return path;
    }

    // initialize all distances to infinity
    for (auto iter2 = actors.begin(); iter2 != actors.end(); ++iter2) {
        (*iter2)->dist = INT_MAX;
        (*iter2)->prev = nullptr;
        (*iter2)->done = false;
    }

    priority_queue<pair<int, Actor*>, vector<pair<int, Actor*>>,
                   ActorComparator2>
        pq;

    Actor* start = *iter;  // start actor
    start->dist = 0;

    // add start actor to priority queue
    pq.emplace(make_pair(0, start));

    while (!pq.empty()) {
        // deque actor from priority queue
        pair<int, Actor*> current = pq.top();
        pq.pop();

        // if (current.second->name.compare(actor2->name) == 0)
        // break;  // if we have reached thedesination acto

        // if we have not visited actor before
        if (current.second->done == false) {
            current.second->done = true;

            vector<pair<Actor*, Movie*>> neighbors = current.second->neighbors;

            for (auto iter3 = neighbors.begin(); iter3 != neighbors.end();
                 ++iter3) {
                pair<Actor*, Movie*> neighbor = *iter3;  // get neighbor

                int c = current.second->dist +
                        (1 + (2019 - neighbor.second->getYear()));

                // do relaxation technique if sum of two sides is less than
                // third side
                if (c < neighbor.first->dist) {
                    neighbor.first->dist = c;

                    neighbor.first->prev = current.second;

                    neighbor.first->sharedMovie = neighbor.second;

                    pq.emplace(make_pair(c, neighbor.first));
                }
            }
        }
    }
    // get the second actor
    auto iterat = actors.find(actor2);

    Actor* current = *iterat;

    if ((*iterat)->prev == nullptr)
        return path;  // we have not found any path to second actor

    // get path and output it as required
    while (current->prev) {
        path.emplace_back("(" + current->name + ")");
        path.emplace_back("#@" + to_string(current->sharedMovie->getYear()) +
                          "]-->");

        path.emplace_back("--[" + current->sharedMovie->getName());

        current = current->prev;
    }
    path.emplace_back("(" + actor1->name + ")");

    return path;
}


// Main function that must have 4 arguments
// one that holds all actors and the movies they played in
// second that determineds whether we run dijkstra(weighted)
// 	or shortestPath(unweighted)
// third that holds the pairs that will find the path from one to the other 
// fourth is the file we output the path of each pair into

int main(int argc, char* argv[]) {
    string pairsFile(argv[3]);  // the file containing the pairs

    ofstream out;

    out.open(argv[4]);

    vector<pair<string, string>> pairs;

    bool success = loadTestPairs(pairsFile, pairs);  // load the test pairs

    ActorGraph graph;

    graph.loadFromFile(argv[1], false);

    graph.buildGraph();  // build the graph to search

    // write the header of the file first
    out << "(actor)--[movie#@year]-->(actor)--..." << endl;

    if (*argv[2] == 'u') {
        // find shortest path between each pair of actors
        for (auto it = pairs.begin(); it != pairs.end(); ++it) {
            pair<string, string> actors = *it;

            Actor* actor1 = new Actor(actors.first);
            Actor* actor2 = new Actor(actors.second);

            vector<string> path = graph.shortestPath(actor1, actor2);

            for (int i = path.size() - 1; i >= 0; i--) {
                out << path[i];
            }
            out << endl;

            delete (actor1);
            delete (actor2);
        }
        out.close();

        return 0;

    }

    else if (*argv[2] == 'w') {
        // find shortest path between each pair of actors
        for (auto it = pairs.begin(); it != pairs.end(); ++it) {
            pair<string, string> actors = *it;

            Actor* actor1 = new Actor(actors.first);
            Actor* actor2 = new Actor(actors.second);

            vector<string> path = dijkstra(actor1, actor2, graph.actors);

            for (int i = path.size() - 1; i >= 0; i--) {
                out << path[i];
            }
            out << endl;

            delete (actor1);
            delete (actor2);
        }
        out.close();

        return 0;
    }

    cout << "Weighted or Unweighted was not specified in second argument"
         << endl;
    return 0;
}
