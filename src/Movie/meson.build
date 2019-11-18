inc = include_directories('.')

Movie = library('Movie', dependencies: [actor_dep], sources: ['Movie.cpp'])

movie_dep = declare_dependency(include_directories: inc,
	link_with: Movie)
