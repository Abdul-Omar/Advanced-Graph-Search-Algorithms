
#include <iostream>
#include<string>
#include<Actor.hpp>
#include<bits/stdc++.h>

using namespace std;

/* This class acts as the link or edge connecting actors */
class Movie { 

        protected:
		
	    vector<Actor*> actors;// all actor(s) starring in this movie

	public:	

	string name;//name of movie

	int year;// year movie came out
	
	set<Actor*> actors;// actor(s) starring in this movie
	
	//constructor for the class
	Movie(string name, int year) : name(name) , year(year) { };

	/* add an actor to list of actors starring in this  movie*/
        void addActor( Actor* actor); 
	
	
	/* This function returns all actors depicted in this movie*/
	set<Actor*> getAllActors( ); 
	
	/* Checks if two actors star in the same movie
	 */
	bool checkIfCostars( const Actor & actor1, const Actor& actor2); 
       
};  	  
/* struct used to compare elements. Needed by set data structure */
struct movieComparator{
    
	bool operator() (Movie* const & a, Movie* const & b) { 
	   
	   //if similar names, sort them by year
	   if(a->name.compare(b->name) == 0) {
	   
	     return a->year < b->year;
	 }
	   //else sort them by names
	 return a->name < b-> name;
    }
};

