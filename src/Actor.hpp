#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <iostream>
#include<string>
#include<bits/stdc++.h>

using namespace std;

/** The Movie struct forms the edges that join nodes
 * in the graph
 */

typedef struct Movie {  

	string name;//name of movie
	int year;// year movie came out

	Movie(string name, int year) {  
	
           name = name;
	   year = year;
	
	}
        //comparison function to be used by unordered set for MOvie objects
	bool operator==(const Movie & movie) const { 
	
	  return this->name == movie.name && this->year == movie.year;	
	}
	
} Movie;

/** hashfunction to be used for unordered set of Movie objects
 */

class hashFunction {   

    size_t operator()(const Movie& movie)const {  

       return (hash<string>()(movie.name)) ^ (hash<int>()(movie.year));
    }
};

/** This class forms the nodes in the graph
 */
class Actor {      


	public:

		string name;//the name of the actor

		Movie movie;//single movie actor stars in
	        
		unordered_set<Movie, hashFunction> movies; // All the movies actor stars in
	
		//constructor for the class
		Actor( string name, Movie movie) : name(name), movie(movie) { 
		
		   movies.insert(movie);//add move to list of movies
		
		};
		
		/* Checks if two actors star in the same movie
		 */
		bool checkIfCostars( const Actor & actor1, const Actor & actor2) {  }

};




