inc = include_directories('.')

actorGraph = library('actorGraph', sources: ['ActorGraph.cpp', 'ActorGraph.hpp'])

actor = library('actor', sources: ['Actor.cpp', 'Actor.hpp'])

movie = library('movie', sources: ['Movie.cpp', 'Movie.hpp'])

actor_graph_dep = declare_dependency(include_directories: inc,
	link_with: [actorGraph, actor, movie])
actor_graph_dep = declare_dependency(include_directories: inc,
	link_with: [actorGraph, movie, actor])
