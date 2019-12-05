#ifndef EDGE_HPP
#define EDGE_HPP

class Movie;
class Actor;

class Edge {
  public:
    Actor* src;
    Actor* dest;
    Movie* movie;         // movie shared by this two actors
    unsigned int weight;  // weight of this edge

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
