inc = include_directories('.')

Actor = library('Actor', dependencies : [movie_dep], sources: ['Actor.cpp'])

actor_dep = declare_dependency(include_directories: inc,
	link_with: Actor)
