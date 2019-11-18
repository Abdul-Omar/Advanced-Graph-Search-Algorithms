subdir('ActorGraph')
subdir('Movie')
subdir('Actor')

actorgraph_exe = executable('AutoGraph.cpp.executable',
	source: ['ActorGraph.cpp', 'Actor.cpp', 'Movie.cpp'],
	dependencies : [actor_graph_dep, actor_dep, movie_dep],
	install : true)
