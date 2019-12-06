/*
 * Edge.hpp 
 * Author: Andrew Masters, Abdulkhaliq Omar
 * DATE: 12/29/2019
 */
#ifndef EDGE_HPP
#define EDGE_HPP

class Movie;
class Actor;
/** This class forms the edges in the graph
 */
class Edge {
  public:
    Actor* src;//the source actor
    Actor* dest;//destination actor
    Movie* movie;         // movie shared by this two actors
    unsigned int weight;  // weight of this edge
    /* constructor for the class */
    Edge(Movie* movie, Actor* src, Actor* dest, int weight)
        : movie(movie), src(src), dest(dest), weight(weight) {}
};
// compare weights of two edges
struct WeightComparator {
    bool operator()(Edge* const& a, Edge* const& b) {
        // else sort them by distance
        return a->weight > b->weight;
    }
};
#endif
