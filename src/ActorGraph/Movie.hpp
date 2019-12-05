/*
 * Movie.hpp
 * Author: Andrew Masters, Abdulkhaliq Omar
 *
 * Movie.hpp defines, declares, and implements functions for the movie class
 *
 * The movie class holds a movie and all the actors of that movie
 * This class acts as a link or edge connecting actors
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <string>
#include "Actor.hpp"

class Actor;

using namespace std;

class Movie {
  protected:
    string name;  // name of movie

    int year;  // year movie came out

  public:
    set<Actor*> actors;  // actor(s) starring in this movie

    string getName() { return name; }  // Get for name variable

    int getYear() { return year; }  // Get for year variable

    // constructor for the class
    Movie(string name, int year) : name(name), year(year){};

    /* add an actor to list of actors starring in this movie*/
    void addActor(Actor* actor) { actors.insert(actor); }

    // Get function for actors set
    set<Actor*> getAllActors() { return actors; }

    /* Checks if two actors star in the same movie */
    bool checkIfCostars(Actor*& actor1, Actor*& actor2);
};

/* Checks if two actors star in the same movie by checking
 * if both actor1 and actor2 exist in the set of this movie
 * */
bool Movie::checkIfCostars(Actor*& actor1, Actor*& actor2) {
    if (actors.find(actor1) != actors.end() &&
        actors.find(actor2) != actors.end())
        return true;

    return false;
}

/* struct used to compare elements. Needed by set data structure */
struct movieComparator {
    bool operator()(Movie* const& a, Movie* const& b) {
        // if similar names, sort them by year
        if (a->getName().compare(b->getName()) == 0) {
            return a->getYear() < b->getYear();
        }
        // else sort them by names
        return a->getName() < b->getName();
    }
};

#endif
