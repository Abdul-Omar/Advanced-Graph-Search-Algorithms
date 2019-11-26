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
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "Movie.hpp"

using namespace std;

struct WeightComparator {
    bool operator()(pair<string, int>& left, pair<string, int>& right) {
        if (left.second == right.second) {
            return left.first > right.first;
        }
        return left.second > right.second;
    }
};
/* shortestPath : this function takes in two arguments both being of the class
 * Actor in order to find the shortest path between the two. This function uses
 * the concept of a BFS to determine the shortest number of movies between two
 * different actors
 */
void bfs(Actor* actor, vector<Actor*>& levelTwo, queue<Actor*>& q, set<Actor*, ActorComparator> &actors, int level) {
     
    auto it = actors.find(actor);
    Actor* actorr = *it;
    
    for (int i = 0; i < actorr->neighbors.size(); i++ ) {
         
        if (actorr->neighbors[i].first->dist != INT_MAX) continue;
       actorr->neighbors[i].first->dist = actorr->neighbors[i].first->dist + 1;
       q.push(actorr->neighbors[i].first);
      }

  
    if (!q.empty()) {
        actorr  = q.front();
        q.pop();
	 if(level == 2) {  
    
          levelTwo.emplace_back(actorr);
	  level = 0;
	  
	  
         }
	   

        bfs(actorr, levelTwo,q, actors, level + 1);
	 
       
    }
}

vector<string> predictLinks(Actor* actor,
                            set<Actor*, ActorComparator>& actors) {
    // all neighbors of query actor's neighbors
    vector<Actor*> secondLevelNeighbors;

    // get all the adjacency list of this actor
    vector<pair<Actor*, Movie*>> levelOne = actor->neighbors;

    // used to count frequency of levelOne actors in levelOne actors' own
    // adjacency list
    unordered_map<string, int> actorCount;

    unordered_map<string, int> levelTwoCount(
        levelOne.size());  // counts frequency of each queryactor's neighbors in
                           // second level neighbor

    // initialize it with first level neigbhors names
    for (int i = 0; i < levelOne.size(); i++) {
        levelTwoCount[levelOne[i].first->name] = 0;
    }

    // to reinstate original count of each neighbor
    vector<int> originalCount(actor->neighbors.size());
    int i = 0;

    // get frequency of each friend in queryActor's neighbors
    for (auto v : levelOne) {
        ++actorCount[(v.first)->name];
    }
   queue<Actor*> q;

   for(auto iter = actors.begin(); iter != actors.end(); ++iter) 
	   (*iter)->dist = INT_MAX;
    // get all valid second level neighbors
    bfs(actor,secondLevelNeighbors,q, actors, 0);

    cout << "size of secondLevel neighbors is " << secondLevelNeighbors.size()
         << endl;

    // map of each second level neighbor and its weight
    priority_queue<pair<string, int>, vector<pair<string, int>>,
                   WeightComparator>
        levelTwoWeight;

    for (int i = 0; i < secondLevelNeighbors.size(); i++) {
        // the weight of each levelTwo neighbor
        int weight = 0;

        for (auto iter = secondLevelNeighbors[i]->neighbors.begin();
             iter != secondLevelNeighbors[i]->neighbors.end(); ++iter) {
            auto iter3 = find(levelOne.begin(), levelOne.end(), *iter);

            // if we have a level one actor in levelTwo's neighbors
            if (iter3 != levelOne.end()) {
                auto it = levelTwoCount.find((*iter).first->name);

                // update the count
                if (it != levelTwoCount.end())
                    it->second = it->second + 1;  // double the weight
            }
        }

        // computer total weight for each level two neighbor
        for (auto it = actorCount.begin(); it != actorCount.end(); ++it) {
            weight += (*it).second * levelTwoCount[(*it).first];
        }

        // insert levelTwo neighbor with its weight on to list
        levelTwoWeight.emplace(secondLevelNeighbors[i]->name, weight);

        // reset count map to original count
        for (int j = 0; j < actorCount.size(); j++) {
            actorCount[(levelOne[j].first)->name] = 0;
        }
    }

    /*for(int i = 0; i < levelOne.size(); i++){
            cout << levelOne[i].first->name << endl;
    }*/

    for (int i = 0; i < secondLevelNeighbors.size(); i++) {
        cout << secondLevelNeighbors[i]->name << endl;
    }

    vector<string> topFour;
    // return top 4 weights in priority queue
    while (!levelTwoWeight.empty()) {
        topFour.emplace_back(levelTwoWeight.top().first);
        // cout << "Name: " << levelTwoWeight.top().first << endl;
        // cout << "Weight: " << levelTwoWeight.top().second << endl;
        levelTwoWeight.pop();
    }

    return topFour;
}

bool loadQueryActor(string in_filename, vector<string> queryActors) {
    /*
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
              if (!getline(ss, str, '\n')) break;
              record.push_back(str);
          }

          if (record.size() != 1) {
              // we should have exactly 2 columns
              continue;
          }

          string actor(record[0]);

          queryActors.emplace_back(actor);  // add to list of pairs
      }
      if (!infile.eof()) {
          cerr << "Failed to read " << in_filename << "!\n";
          return false;
      }

      infile.close();
      return true;
      */
}

int main(int argc, char* argv[]) {
    string database(argv[1]);  // database file

    // string pairsFile(argv[2]);  // the file containing the pairs

    // ofstream out;

    // out.open(argv[3]);

    // vector<pair<string, string>> pairs;

    // bool success = loadTestPairs(pairsFile, pairs);  // load the test pairs

    ActorGraph graph;

    graph.loadFromFile(argv[1], false);

    graph.buildGraph();  // build the graph to search

    // write the header of the file first
    // out << "(actor)--[movie#@year]-->(actor)--..." << endl;

    Actor* actor = new Actor("Kevin Bacon");
    auto it = graph.actors.find(actor);
    vector<string> topFour = predictLinks(*it, graph.actors);

    for (int i = 0; i < topFour.size(); i++) {
        // cout<<topFour[i]<<endl;
    }

    delete (actor);

    return 0;
}
