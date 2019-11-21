/*
 * PathFinder.cpp
 * Author: <YOUR NAME HERE>
 *
 */

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include<vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "Movie.hpp"

using namespace std;

bool loadTestPairs(string in_filename,
                       vector<pair<string, string>>& pair) {
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

            pair.emplace_back(make_pair(actor1, actor2));//add to list of pairs     

        }
	    if (!infile.eof()) {
                cerr << "Failed to read " << in_filename << "!\n";
                return false;
           }

	   infile.close();
           return true;
}


int main(int argc, char* argv[]) {
    string database(argv[1]);  // database file

    string pairsFile(argv[2]);  // the file containing the pairs

    ofstream out;

    out.open(argv[3]);

    vector<pair<string, string>> pairs;

    bool success = loadTestPairs(pairsFile, pairs);  // load the test pairs

    ActorGraph graph;

    graph.loadFromFile(argv[1], false);

    graph.buildGraph();//build the graph to search

    // write the header of the file first
    out << "(actor)--[movie#@year]-->(actor)--..." << endl;

	
    // find shortest path between each pair of actors
    for (auto it = pairs.begin(); it != pairs.end(); ++it) {
       int count = 1;
         pair<string, string> actors = *it;

        Actor* actor1 = new Actor(actors.first);
        Actor* actor2 = new Actor(actors.second);

       vector<string> path = graph.shortestPath(actor1, actor2);


       for( auto iter = path.begin(); iter != path.end(); ++iter) {  


       	  out<< *iter;

	  if(count == 3){
		out<<endl;
		count = 0;
	  }
	  else{
		  out<< " -> ";
	  }

	  count++;
       }
       out<<endl;

        delete (actor1);
        delete (actor2);
    }

    return 0;
}
