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

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include "navigation.hpp"

class Navigation;

/* struct used to compare elements. Needed by set data structure */
struct LocationComparator {
    bool operator()(pair<int, Location*> const& a, pair<int, Location*> const& b) {
        if(a.first == b.first)
        	return a.second->name < b.second->name;
	else
		return a.first > b.first;
    }
};

bool Navigation::loadFromFile(string in_filename) {
    // Initialize the file stream
    ifstream infile(in_filename);

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the current line
        if (!getline(infile, s)) break;

        istringstream ss(s);

        vector<string> record;

        while (ss) {
            string str;

            // get the current string before hitting a tab character and put
            // it in 'str'
            if (!getline(ss, str, ' ')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            // we should have exactly 2 columns
            continue;
        }

        string name(record[0]);
        int x = stoi(record[1]);
	int y = stoi(record[2]);

	Location* location = new Location( name, x, y);

        locations[name] = location;  
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

    infile.close();
    return true;
}



bool Navigation::loadConnections(string in_filename) {
    // Initialize the file stream
    ifstream infile(in_filename);

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the current line
        if (!getline(infile, s)) break;

        istringstream ss(s);

        vector<string> record;

        while (ss) {
            string str;

            // get the current string before hitting a tab character and put
            // it in 'str'
            if (!getline(ss, str, ' ')) break;
            record.push_back(str);
        }

        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }

        string name1(record[0]);
        string name2(record[1]);

	

	if(locations.find(name1) != locations.end()){
	    locations[name1]->neighbors.emplace_back(locations[name2]);
	}

	if(locations.find(name2) != locations.end()){
	    locations[name2]->neighbors.emplace_back(locations[name1]);
	}


}
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

    infile.close();
    return true;
}



/*finds the shortest path in a weighted graph */
vector<string> Navigation:: AStarSearch(string location1, string locationEnd) { 

    vector<string> path;
     
    auto location = locations.find(location1);

    if (location == locations.end()) {
        cout << "location does not exist " << endl;

        return path;
    }

    auto location2 = locations.find(locationEnd);

    if (location2 == locations.end()) {
        cout << "location2 does not exist " << endl;

        return path;
    }

   // initialize all distances to infinity
    for(auto iter2  = locations.begin(); iter2!=locations.end(); ++iter2) { 

	(*iter2).second->dist = INT_MAX;
	(*iter2).second->prev = nullptr;
	(*iter2).second->done = false;
    }

    priority_queue<pair<int, Location*>, vector<pair<int, Location*>>, LocationComparator> pq;
    
    Location* start = locations[location1];//start actor
    
    start->dist = 0; 
    
    //add start actor to priority queue 
    pq.emplace(make_pair(0, start));

    while(!pq.empty()) { 
	//deque actor from priority queue
	pair<int, Location*> current = pq.top();
	pq.pop();


	// if (current.second->name.compare(actor2->name) == 0)
           // break;  // if we have reached thedesination acto
       
	 //if we have not visited actor before
	if(current.second->done == false) { 
	   
	    current.second->done = true;

	    vector<Location*> neighbors = current.second->neighbors; 
	    
	    for(auto iter3  = neighbors.begin(); iter3 != neighbors.end(); ++iter3) {
		
		
		 Location* neighbor = *iter3;//get neighbor
	
		
		 int c = current.second->dist + eucledianDistance(current.second, neighbor);
		
		 //do relaxation technique if sum of two sides is less than third side
		if(c < neighbor->dist) { 
		  
	            neighbor->dist = c;
		     
		    neighbor->prev = current.second;
		    
		    pq.emplace(make_pair((c + ( eucledianDistance(current.second, neighbor))), neighbor));
		}
	    } 
	}
    }
    //get the second actor
    auto iterat = locations.find(locationEnd);

    Location* current = locations[locationEnd];

    if (current->prev == nullptr) return path;//we have not found any path to second actor
    
    //get path and output it as required
    while (current->prev) {
        
	path.emplace_back("-->(" + current->name + ")");
               
        current = current->prev;
    }
    path.emplace_back("("  + location1 +  ")");

    return path;
}


int Navigation::eucledianDistance(Location* location1, Location* location2){ 
 
   int x1 = location1->xCoord;
   int y1 = location1->yCoord;

   int x2 = location2->xCoord;
   int y2  = location2->yCoord;

   return sqrt(  pow(x1-x2, 2) + pow(y1-y2, 2) );
 
}

Navigation::~Navigation(){
	for(auto iter = locations.begin(); iter != locations.end(); ++iter){
		delete (*iter).second;
	}
}


bool loadTestPairs(string in_filename, vector<pair<string, string>>& pair) {
    // Initialize the file stream
    ifstream infile(in_filename);

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the current line
        if (!getline(infile, s)) break;

        istringstream ss(s);

        vector<string> record;

        while (ss) {
            string str;

            // get the current string before hitting a tab character and put
            // it in 'str'
            if (!getline(ss, str, ' ')) break;
            record.push_back(str);
        }

        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }

        string location1(record[0]);
        string location2(record[1]);

        pair.emplace_back(make_pair(location1, location2));  // add to list of pairs
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

    infile.close();
    return true;
}

int main(int argc,char *argv[]) {
    ofstream out;

    out.open(argv[4]);

    Navigation navigate;

    vector< pair <string, string>> pairs;

    // load all locations
    bool loadSuccess = navigate.loadFromFile(argv[1]);//load the file

    if(!loadSuccess) return 0;

    // load all connections to locations
    bool loadConnections = navigate.loadConnections(argv[2]);

    if(!loadConnections) return 0;

    // load test pairs
    bool loadPairs = loadTestPairs(argv[3], pairs);
    
    if (!loadPairs) return 0;

    out << "(location)-->(location)" << endl;
    
    for( int i = 0; i < pairs.size(); i++) {  
    
	vector<string> path = navigate.AStarSearch(pairs[i].first, pairs[i].second);
	for(int j = path.size() - 1; j >= 0; j--){
		out << path[j];
	}
	out << endl;
    
    }

    out.close(); 
    return 0;

}
