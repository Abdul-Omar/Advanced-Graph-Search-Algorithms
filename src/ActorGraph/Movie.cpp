
#include <bits/stdc++.h>
#include <Actor.hpp>
#include <Movie.hpp>
#include <iostream>
#include <string>

using namespace std;

/* add an actor to list of actors starring in this  movie*/
void Movie::addActor(Actor* actor) { actors.insert(actor); }
/* This function returns all actors depicted in this movie*/
set<Actor*> Movie::getAllActors() { return actors; }
/* Checks if two actors star in the same movie */
bool Movie::checkIfCostars(const Actor*& actor1, const Actor*& actor2) {
    if (actors.find(actor1) != actors.end() &&
        actors.find(actor2) != actors.end())

        return true;
}

return false;
}
