inc = include_directories('.')

actorGraph = library('actorGraph', sources: ['ActorGraph.cpp', 'ActorGraph.hpp',
	'Actor.cpp', 'Actor.hpp', 'Movie.cpp', 'Movie.hpp'])

actorgraph_dep = declare_dependency(include_directories: inc,
	link_with: actorGraph)

