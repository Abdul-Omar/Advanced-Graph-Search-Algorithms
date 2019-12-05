/*
 * Movie.cpp
 * Author: Andrew Masters, Abdulkhaliq Omar
 *
 * Movie.cpp implements the functions that were declared in Movie.hpp
 * Adds an actor to the actor set of the movie class if perfomed in it
 *
 * Holds a getter function to return the set of actors that is protected
 *
 * Holds a function that will check if two actors played in the same movie

#include "Movie.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include "Actor.hpp"

using namespace std;

void Movie::addActor(Actor* actor) { actors.insert(actor); }

set<Actor*> Movie::getAllActors() { return actors; }

bool Movie::checkIfCostars(Actor*& actor1, Actor*& actor2) {
    if (actors.find(actor1) != actors.end() &&
        actors.find(actor2) != actors.end())
        return true;

    return false;
}*/
