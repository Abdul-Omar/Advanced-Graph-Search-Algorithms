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

struct WeightComparator {
     bool operator()(pair<string,  int>& left, pair<string,  int>& right){
	
	 if(left.second == right.second){
		return left.first > right.first;
	
	}
        return left.second > right.second;
    }
};

vector<string> predictLinks(Actor* actor){
      
	       
       //all neighbors of query actor's neighbors
       vector<pair<Actor*, Movie*>>secondLevelNeighbors;
	
	//get all the adjacency list of this actor
	vector<pair<Actor*, Movie*>> levelOne = actor->neighbors;
	
	
	//used to count frequency of levelOne actors in levelOne actors' own adjacency list
	unordered_map<string,int> actorCount;
        
	//to reinstate original count of each neighbor
	vector<int> originalCount(actor->neighbors.size());
	
	//initialize vector with names and frequency of each actor in query actor's list
	for( int i = 0; i < levelOne.size(); i++) { 
	   
	    for( int j = 0; j < levelOne.size(); j++) {  
	   
	       if ( levelOne[i].first->name == levelOne[j].first->name){ 
	       
	            actorCount[(levelOne[j].first)->name]++;	
	       } 
	   
	   }
            originalCount[i] = actorCount[(levelOne[i].first)->name];    
	}
	

	
	//traverse through the adjacency list to find common actors with actor1
	for( auto it = levelOne.begin(); it != levelOne.end(); ++it) {  
		
	    //get each of levelOne actor's list;
	     vector<pair<Actor*, Movie*>>levelTwo = (*it).first->neighbors;
		
	     for( auto iter = levelTwo.begin(); iter != levelTwo.end(); ++iter) {  
                  
		   //get all neighbors of query actor's neighbors;
		  if(find(levelOne.begin(), levelOne.end(), *iter) == levelOne.end())  { 	 
		 	 //add to list of second level neighbors for query actor
		  	secondLevelNeighbors.emplace_back((*iter));
		  }
		      
	     }
	}
        
		
	//map of each second level neighbor and its weight
	priority_queue< pair<string, int>, vector<pair<string, int>>, WeightComparator>  levelTwoWeight;
	
	for( int i = 0; i < secondLevelNeighbors.size(); i++) { 
	  
	   //the weight of each levelTwo neighbor
	   int weight = 0;
	    
	   for(auto iter = secondLevelNeighbors[i].first->neighbors.begin(); iter != secondLevelNeighbors[i].first->neighbors.end(); ++iter){
	    
                 //if we have a level one actor in levelTwo's neighbors
	         if(find(levelOne.begin(), levelOne.end(), *iter) == levelOne.end()) {  
	    
		     auto it = actorCount.find((*iter).first->name);
		 
		     //update the count  
		     if(it != actorCount.end()) 
		    
		        it->second = (it->second * 2);//double the weight	    	
	         }
	   
           }
           
	   int count = 0;//how many common neighbors it has with queryActor
	   int k = 0;
	   //computer total weight for each level two neighbor
	   for( auto it = actorCount.begin(); it != actorCount.end(); ++it) { 
	       if((*it).second != originalCount[k]) {  	
	           count++; 
	           weight += (*it).second;   
	        
	       } 
	     k++;  
	   }
           
	   //get average weight for each levelTwo neighbor;
	   int averageWeight = weight/count;
           
	   //insert levelTwo neighbor with its weight on to list
	   levelTwoWeight.emplace(secondLevelNeighbors[i].first->name, averageWeight);
	   
	   //reset count map to original count	
	   for( int j = 0; j < actorCount.size(); j++) {  	
	      
	       actorCount[(levelOne[j].first)->name] = originalCount[j];	
	   }
       }

	vector<string> topFour;
	//return top 4 weights in priority queue
	while(!levelTwoWeight.empty()){
	    topFour.emplace_back(levelTwoWeight.top().first);
	    cout << "Name: " << levelTwoWeight.top().first << endl;
    	    cout << "Weight: " << levelTwoWeight.top().second << endl;	    
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

    //string pairsFile(argv[2]);  // the file containing the pairs

    //ofstream out;

    //out.open(argv[3]);

    //vector<pair<string, string>> pairs;

    //bool success = loadTestPairs(pairsFile, pairs);  // load the test pairs

    ActorGraph graph;

    graph.loadFromFile(argv[1], false);

    graph.buildGraph();  // build the graph to search

    // write the header of the file first
    //out << "(actor)--[movie#@year]-->(actor)--..." << endl;

    Actor* actor = new Actor( "Robert Downey Jr.");
    auto it = graph.actors.find(actor);
    vector<string> topFour = predictLinks(*it);

    for( int i = 0; i < topFour.size(); i++) {  
    
    
       //cout<<topFour[i]<<endl;
    }

   delete(actor);

    return 0;
}
