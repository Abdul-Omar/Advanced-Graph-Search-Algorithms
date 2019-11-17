
#include <iostream>
#include<string>
#include <Movie.hpp>
#include<Actor.hpp>
#include<bits/stdc++.h>

using namespace std;

 /* add an actor to list of actors starring in this  movie*/
 void addActor( Actor* actor) {  
	
     actors.insert(actor);   
	
}
/* This function returns all actors depicted in this movie*/
set<Actor*> getAllActors( ) { 
	
  return actors;	
}
/* Checks if two actors star in the same movie */
bool checkIfCostars( const Actor & actor1, const Actor & actor2) { 
       
    if( actors.find(actor1) != actors.end() && actors.find(actor2) != actors.end())
	
	return true;
    }
	  
   return false;      	
}


