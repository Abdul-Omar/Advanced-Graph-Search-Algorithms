inc = include_directories('.')

actorGraph = library('actorGraph', sources: ['ActorGraph.cpp', 'ActorGraph.hpp'])

actor_graph_dep = declare_dependency(include_directories: inc,
	link_with: actorGraph)
