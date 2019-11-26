
#include "Actor.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/* THis function essentially acts as the link or edge between two Actor Nodes */
void Actor::connectActors(pair<Actor*, Movie*>& neighbor) {
    // Check if neighbor already exists; if it doesn't then add it else increase
    // number of edges
    /*for(int i = 0; i < neighbors.size(); i++){
        if(neighbor.first->name != neighbors[i].first->name){
            neighbors.push_back(neighbor);
        }
    } else {
        neighbor[i].second+1;
    }*/
    neighbors.push_back(neighbor);
}
