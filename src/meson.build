subdir('ActorGraph')

pathfinder_exe = executable('pathfinder.cpp.executable',
	sources: ['pathfinder.cpp'],
	dependencies: [actorgraph_dep],
	install: true)

linkpredictor_exe = executable('linkpredictor.cpp.executable',
	sources: ['linkpredictor.cpp'],
	dependencies: [actorgraph_dep],
	install: true)

movietraveler_exe = executable('movietraveler.cpp.executable',
	sources: ['movietraveller.cpp', 'movietraveller.hpp', 'Edge.hpp'],
	dependencies: [actorgraph_dep],
	install: true)

navigationsystem_exe = executable('navigationsystem.cpp.executable',
	sources: ['navigation.cpp', 'navigation.hpp'],
	dependencies: [],
	install: true)
