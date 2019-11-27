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
        return left.second < right.second;
    }
};
/* shortestPath : this function takes in two arguments both being of the class
 * Actor in order to find the shortest path between the two. This function uses
 * the concept of a BFS to determine the shortest number of movies between two
 * different actors
 */
vector<Actor*> BFS(Actor*& actor1, set<Actor*, ActorComparator> & actors, int level) {
    // initialize all distances to zero
    for (auto iter = actors.begin(); iter != actors.end(); ++iter) {
        (*iter)->dist = INT_MAX;
    }

    queue<Actor*> toExplore;

    vector<Actor*> levelTwo;

    vector<string> path;  // holds the shortest path from one actor to another

    auto iter = actors.find(actor1);

    if (iter == actors.end()) {
        cout << "actor does not exist " << endl;

        }
    // cout << (*iter)->name<<endl;

    Actor* start = *iter;
    start->dist = 0;

    toExplore.push(start);

    while (!toExplore.empty()) {
        Actor* current = toExplore.front();
        
	if(current->dist == level) {  
	
	   levelTwo.emplace_back(current);
	
	}
        
	toExplore.pop();

	if(current->dist == level + 1) break;//dont go to level 3

      
        auto it = current->neighbors.begin();

        for (; it != current->neighbors.end(); ++it) {
            // movie neighbor shares with current actor
            Movie* sharedMovie = (*it).second;

            // get the neighbor
            auto iter3 = actors.find((*it).first);

            Actor* neighbor = *iter3;

            if (neighbor->dist == INT_MAX) {
                neighbor->dist = current->dist + 1;
                toExplore.push(neighbor);
            }
        }
    }
   return levelTwo;
}


void predictLinks2(Actor* actor,
                            set<Actor*, ActorComparator>& actors, ofstream & out) {
   

    // get all the adjacency list of this actor
    vector<pair<Actor*, Movie*>> levelOne = actor->neighbors;

    // used to count frequency of levelOne actors in levelOne actors' own
    // adjacency list
    unordered_map<string, int> actorCount(levelOne.size());

    unordered_map<string, int> levelOneCount(levelOne.size());  // counts frequency of each queryactor's neighbors in
                           // second level neighbor

    // initialize it with first level neigbhors names
    for (int i = 0; i < levelOne.size(); i++) {
        levelOneCount[levelOne[i].first->name] = 0;
    }

  
    // get frequency of each friend in queryActor's neighbors
    for (auto v : levelOne) {
        ++actorCount[(v.first)->name];
    }

 

    // map of each second level neighbor and its weight
    priority_queue<pair<string, int>, vector<pair<string, int>>,
                   WeightComparator>
        levelOneWeight;

    for (int i = 0; i < levelOne.size(); i++) {

	//the weight of each levelTwo neighbor
        int weight = 0;

        for (auto iter = levelOne[i].first->neighbors.begin(); iter != levelOne[i].first->neighbors.end(); ++iter) {

	    //if we find level one actor in level two neighbors adjacency list
	    for(auto iter2 = levelOne.begin(); iter2 != levelOne.end(); ++iter2) {
	       
		 if(((*iter2).first)->name.compare((*iter).first->name) == 0){ 
	         
		   //cout << "found :  " << ((*iter2).first)->name << " in " << ((*iter).first)->name << "neighbors " <<endl;
		  
		   ++levelOneCount[(*iter2).first->name];
	
		  break;
	      
	      } 
	    
	   }
            
      }

        // computer total weight for each level two neighbor
        for (auto it = actorCount.begin(); it != actorCount.end(); ++it) {
	    
	   weight += (*it).second * levelOneCount[(*it).first];

        }

	  // reset count of found first level neighbors in secondLevel's neighbors
        for (int i = 0; i < levelOne.size(); i++) {
            levelOneCount[levelOne[i].first->name] = 0;
        }
       
       // insert levelTwo neighbor with its weight on to list
        levelOneWeight.emplace(levelOne[i].first->name, weight);
    }
    
  
      vector<string> topFour;

      

    // return top 4 weights in priority queue
    int k = 0;
     while(  !levelOneWeight.empty() && topFour.size() < 4 ) {
	     ++k;
	  string actorr = levelOneWeight.top().first;
	 
	 if(  topFour.size() >= 1 && (actorr.compare(topFour.at(topFour.size() - 1)) == 0)) { 
	    levelOneWeight.pop();
	    continue;		 
			 
         }
        topFour.emplace_back(actorr);
        levelOneWeight.pop();     
    }
   
     
    for( int i = 0; i < topFour.size(); i++) {  
    
    
      out << topFour[i];
      out << '\t';
    
    }
    out << '\n';
}



void predictLinks(Actor* actor,
                            set<Actor*, ActorComparator>& actors, ofstream & out) {
    // all neighbors of query actor's neighbors
    vector<Actor*> secondLevelNeighbors;

    // all neighbors of query actor's neighbors
    vector<Actor*> thirdLevelNeighbors;


    // get all the adjacency list of this actor
    vector<pair<Actor*, Movie*>> levelOne = actor->neighbors;

    // used to count frequency of levelOne actors in levelOne actors' own
    // adjacency list
    unordered_map<string, int> actorCount(levelOne.size());

    unordered_map<string, int> levelTwoCount(levelOne.size());  // counts frequency of each queryactor's neighbors in
                           // second level neighbor

    // initialize it with first level neigbhors names
    for (int i = 0; i < levelOne.size(); i++) {
        levelTwoCount[levelOne[i].first->name] = 0;
    }

  
    // get frequency of each friend in queryActor's neighbors
    for (auto v : levelOne) {
        ++actorCount[(v.first)->name];
    }

    //cout<<actorCount.size()<<endl;
   queue<Actor*> q;

   secondLevelNeighbors = BFS(actor,actors, 2);//get all second level neighbors


    // map of each second level neighbor and its weight
    priority_queue<pair<string, int>, vector<pair<string, int>>,
                   WeightComparator>
        levelTwoWeight;

    for (int i = 0; i < secondLevelNeighbors.size(); i++) {

	//the weight of each levelTwo neighbor
        int weight = 0;

        for (auto iter = secondLevelNeighbors[i]->neighbors.begin();
             iter != secondLevelNeighbors[i]->neighbors.end(); ++iter) {

	    //if we find level one actor in level two neighbors adjacency list
	    for(auto iter2 = levelOne.begin(); iter2 != levelOne.end(); ++iter2) {
	     
		 if(((*iter2).first)->name.compare((*iter).first->name) == 0){ 
	         
		   ++levelTwoCount[(*iter2).first->name];
	
		  break;
	      
	      } 
	    
	   }
            
      }

        // computer total weight for each level two neighbor
        for (auto it = actorCount.begin(); it != actorCount.end(); ++it) {
	    
	   	   	    weight += (*it).second * levelTwoCount[(*it).first];

        }

	  // reset count of found first level neighbors in secondLevel's neighbors
        for (int i = 0; i < levelOne.size(); i++) {
            levelTwoCount[levelOne[i].first->name] = 0;
        }



       
       // insert levelTwo neighbor with its weight on to list
        levelTwoWeight.emplace(secondLevelNeighbors[i]->name, weight);
    }
  
    vector<string> topFour;

    // return top 4 weights in priority queue
    int k = 0;
     while(  !levelTwoWeight.empty() && k < 4 ) {
	     ++k;
        topFour.emplace_back(levelTwoWeight.top().first);
        levelTwoWeight.pop();
    }

    for( int i = 0; i < topFour.size(); i++) {  
    
    
      out << topFour[i];
      out << '\t';
    
    }
    out << endl;
}

bool loadQueryActors(string in_filename, vector<string>& queryActors) {
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
              // we should have exactly 1 column
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
      
}

int main(int argc, char* argv[]) {
   
     

     ofstream out(argv[3]); //open collab file for writing

     ofstream out2(argv[4]); //open uncollab file for writing


     vector<string> actors;

     bool success = loadQueryActors(argv[2], actors);  // load the test pairs
    
     if( actors.size() == 0) {  
     
      cout << "empty "<<endl;

      return 0;
     }

    
     ActorGraph graph;

    graph.loadFromFile(argv[1], false);

    graph.buildGraph();  // build the graph to search

    // write the header of the file first
    // out << "(actor)--[movie#@year]-->(actor)--..." << endl;

    
      
    for( int i = 0; i < actors.size(); i++) { 
	  Actor* actor = new Actor( actors[i]); 
        
	 auto it = graph.actors.find(actor);

	 if(it == graph.actors.end())return 0;
     
          predictLinks(*it, graph.actors, out2);

         predictLinks2(*it, graph.actors, out);

	 delete(actor);

      
    }
        
   

  

    return 0;
}
