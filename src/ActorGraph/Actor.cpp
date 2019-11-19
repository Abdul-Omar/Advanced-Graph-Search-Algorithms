#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <pair>
#include <string>
#include <vector>

using namespace std;
/* THis function essentially acts as the link or edge between two Actor Nodes */
void Actor::connectActors(pair<Actor*, Movie*> neighbor) {
    neighbors.emplace_back(neighbor);
}
