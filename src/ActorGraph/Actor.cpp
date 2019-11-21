
#include "Actor.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/* THis function essentially acts as the link or edge between two Actor Nodes */
void Actor::connectActors(pair<Actor*, Movie*>& neighbor) {
    neighbors.push_back(neighbor);
}
