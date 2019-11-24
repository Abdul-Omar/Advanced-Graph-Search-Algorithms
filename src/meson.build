subdir('ActorGraph')

pathfinder_exe = executable('PathFinder.cpp.executable',
	sources: ['PathFinder.cpp'],
	dependencies: [actorgraph_dep],
	install: true)

linkpredictor_exe = executable('linkpredictor.cpp.executable',
	sources: ['linkpredictor.cpp'],
	dependencies: [actorgraph_dep],
	install: true)
