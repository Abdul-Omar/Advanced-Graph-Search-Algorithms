inc = include_directories('.')

test_ActorGraph_exe = executable('test_ActorGraph.cpp.executable',
	sources: ['test_ActorGraph.cpp'],
	dependencies : [actorgraph_dep, gtest_dep],
	include_directories : inc)
test('my ActorGraph test', test_ActorGraph_exe)
