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
#include "movietraveller.hpp"

class Movietraveller;

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
bool Movietraveller::loadFromFile(const char* in_filename) {
    // Initialize the file stream
    ifstream infile;
    infile.open(in_filename);
   
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
void Movietraveller::createEdges() {
    
    for (auto iter = movies.begin(); iter != movies.end(); ++iter) {
        Movie* movie = *iter;
        // get all actors in this movie
        set<Actor*> actorsInMovie = movie->getAllActors();
        
        
	int i = 0;
        
	// connect all actors in this movie
        for (auto iter2 = actorsInMovie.begin(); iter2 != actorsInMovie.end();
             ++iter2) {
	    
	    
	     Actor* actor1 = *iter2;
	   
            for (auto iter3 = actorsInMovie.begin();
                 iter3 != actorsInMovie.end(); ++iter3) {
               
	        Actor* actor2 = *iter3;

                // prevent self loops in graph
                if (actor1->name.compare(actor2->name) == 0) continue;

		 
                //create new edge with this two actors
		Edge *edge = new Edge(movie, actor1, actor2, 1 + (2019 - movie->getYear()));
	
		bool found = false;
		//add it to list of all edges if edge is not already there
	/*	for( auto iter4 = edges.begin(); iter4 != edges.end(); ++iter4) {

		   if( (*iter4)->src->name == actor2->name && (*iter4)->dest->name == actor1->name && (*iter4)->movie->getName() == movie->getName()) found = true;
		}*/
		
	       //if(!found)	
		   edges.emplace_back(edge);
		
                        
	    }
	    i++;
    }
  }
}

void Movietraveller::makeSet(set<Actor*, ActorComparator> actors) {  

     for( auto iter = actors.begin(); iter != actors.end(); ++iter) {  
        //set parent to itself;
        (*iter)->parent = nullptr;
	(*iter)->rank = 0;
     } 
}

Actor* Movietraveller::find(Actor* actor){
	
	if(!actor->parent) return actor;
         	
         
	actor->parent = find(actor->parent);
       
	 
	return actor->parent;	
}

void Movietraveller::unionSets(Actor* actor1, Actor* actor2) { 


	Actor* parent1 = find(actor1);
	Actor* parent2 = find(actor2);

	       
       	//already same set
	if(parent1->name.compare(parent2->name) == 0) return;

        
	parent1->parent = parent2;//add
	
}

//Kruskal's algorithm
vector<Edge*> Movietraveller::Kruskals() {
   
     vector<Edge*> MST;//stores resultant mst
    
     //sort all the edges
     sort(edges.begin(), edges.end(), WeightComparator());

     

     while( MST.size() <  actors.size() - 1) {  
     		
	      if(edges.size() == 0) break;
	      Edge* edge = edges.back();//get edge

	      edges.pop_back();//remove it

	      Actor* parent1 = find( edge->src);

	      Actor* parent2 = find( edge->dest);


              //prevent cycles
	      if( parent1->name.compare(parent2->name) != 0){

	          unionSets(parent1, parent2);//merge two sets;
	      
	          MST.emplace_back(edge);//add edge to mst;
	      }
     }
     return MST;
}


// Deconstructor
Movietraveller::~Movietraveller() {
    // delete all movies
    for (auto iter = movies.begin(); iter != movies.end(); ++iter) {
        delete *iter;
    }
    for( auto iter = edges.begin(); iter != edges.end(); ++iter) { 
    
       delete(*iter);
    }
    // delete all actors
    for (auto iter = actors.begin(); iter != actors.end(); ++iter) {
        delete *iter;
    }

}


int main(int argc,char *argv[]) {
    ofstream out;

    out.open(argv[2]);

    Movietraveller traveller;

    traveller.loadFromFile(argv[1]);//load the file

    traveller.createEdges();//create all the edges in graph

    traveller.makeSet(traveller.actors);

    
    vector<Edge*> MST = traveller.Kruskals(); //run Kruskal's

    out << "(actor)<--[movie#@year]-->(actor)" << endl;
    
    int weight = 0;
    for( int i = 0; i < MST.size(); i++) {  
    
       Edge* edge = MST[i];
      
       weight += edge->weight;

       out <<  "(" << edge->src->name << ")";
       
       out << "<--[" << edge->movie->getName()<< "#@" << edge->movie->getYear() << "]-->";

       out<< "(" << edge->dest->name << ")";

     
       out<< endl;
    
    }

    out << "#NODES CONNECTED: " << traveller.actors.size() <<endl;
    out<< "#EDGES CHOSEN: " <<MST.size()<<endl;
    out <<"TOTAL EDGE WEIGHT: " <<weight<<endl;
    out.close(); 
    return 0;

}
