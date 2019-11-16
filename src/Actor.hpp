#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <iostream>
#include<string>
#include<pair>
#include<vector>
#include<bits/stdc++.h>

using namespace std;
/** This class forms the nodes in the graph
 */
class Actor {      


	public:

		string name;//the name of the actor

		Movie movie;//single movie actor stars in
	        
		//actor's adjacency list
		vector<pair< Movie, Actor>> neighbors; 
	
		//constructor for the class
		Actor( string name, Movie movie) : name(name), movie(movie) { 
		
		   movies.insert(movie);//add move to list of movies
		
		};

                /* THis function essentially acts as the link or edge between two Actor Nodes */
		void connectActors( pair<Movie, Actor> neighbor) {  
		
		    neighbors.emplace_back(neighbor);  
		
		}		
			
};
/* used by un_oredered set for hashing */
struct ActorComparator {
    bool operator() (Actor* const & a, Actor* const & b){
	return a->name < b->name;
    }
};
struct Actor_hash {
    std::size_t operator()(const Actor* & actor) const {
        return std::hash<std::string>()(actor->name);
    }
}

