subdir('ActorGraph')

pathfinder_exe = executable('pathfinder.cpp.executable',
	sources: ['pathfinder.cpp'],
	dependencies: [actorgraph_dep],
	install: true)

linkpredictor_exe = executable('linkpredictor.cpp.executable',
	sources: ['linkpredictor.cpp'],
	dependencies: [actorgraph_dep],
	install: true)

movietraveller_exe = executable('movietraveller.cpp.executable',
	sources: ['movietraveller.cpp', 'movietraveller.hpp', 'edge.hpp'],
	dependencies: [actorgraph_dep],
	install: true)
