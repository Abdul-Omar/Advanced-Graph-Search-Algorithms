/*
 * linkpredictor.cpp
 * Author: <YOUR NAME HERE>
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
#include <vector>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "Movie.hpp"

using namespace std;


void predictLinks(Actor* actor){
	priority_queue<Actor*, ActorComparator> collab;
	priority_queue<Actor*, ActorComparator> notYetCollab; 
	
	//get all the adjacency list of this actor
	vector<pair<Actor*, Movie*>> levelOne = actor->neighbors;
	
	
	//used to count frequency of levelOne actors in levelOne actors' own adjacency list
	vector<pair<string,int>> actorCount(actor->neighbors.size());
	
	//initialize vector with names and initial count 
	for( int i = 0; i < levelOne.size(); i++) {  =	
	   actorCount[i].first =  (levelOne[i].first)->name;
	   actorCount[i].second = 0;
	
	}
	
	int counter = 0;
	
	//traverse through the adjacency list to find common actors with actor1
	for( auto it = levelOne.begin(); it != levelOne.end(); ++it) {  
		
	    //get each of levelOne actor's list;
	     vector<pair<Actor*, Movie*>>levelTwo = (*it)->neighbors;
		
	     for( auto iter = levelTwo.begin(); iter != levelTwo.end(); ++iter) {  
	         
		  //if we have found actor in neighbors list
	         if((*it)->name.compare((*iter)->name) == 0) { 
		 
		  actorCount[i].second += 1;//increment count for this actor;	    
		 }
		 i++;	     
	     }
	}
}
	
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

int main(int argc, char* argv[]) {
    string database(argv[1]);  // database file

    string pairsFile(argv[2]);  // the file containing the pairs

    ofstream out;

    out.open(argv[3]);

    vector<pair<string, string>> pairs;

    bool success = loadTestPairs(pairsFile, pairs);  // load the test pairs

    ActorGraph graph;

    graph.loadFromFile(argv[1], false);

    graph.buildGraph();  // build the graph to search

    // write the header of the file first
    out << "(actor)--[movie#@year]-->(actor)--..." << endl;



    return 0;
}
