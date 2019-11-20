#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <string>
#include "Actor.hpp"

class Actor;

using namespace std;

/* This class acts as the link or edge connecting actors */
class Movie {
  protected:
    string name;  // name of movie

    int year;  // year movie came out

  public:
    set<Actor*> actors;  // actor(s) starring in this movie
    
    string getName() { return name; }

    int getYear() { return year; }

    // constructor for the class
    Movie(string name, int year) : name(name), year(year){};

    /* add an actor to list of actors starring in this  movie*/
    void addActor(Actor* actor);

    /* This function returns all actors depicted in this movie*/
    set<Actor*> getAllActors();
    /* Checks if two actors star in the same movie
     */
    bool checkIfCostars(Actor*& actor1, Actor*& actor2);
};

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
