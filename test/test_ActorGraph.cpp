#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "ActorGraph.hpp"

using namespace std;
using namespace testing;

class SimpleActorGraph: public ::testing::Test {
  protected:

  public:
};

TEST_F(SimpleActorGraph, Test_loadFromFile){
	ActorGraph graph;

	bool success = graph.loadFromFile("../testFile.txt", false);

	graph.buildGraph();
	
	ASSERT_EQ(true, success);
		
}

TEST_F(SimpleActorGraph, Test_loadFromFile_isEmpty){
	ActorGraph graph;
	
	ASSERT_EQ(false, graph.loadFromFile("newTestFile.txt", false));
		
}

TEST_F(SimpleActorGraph, Test_shortestPath){
	ActorGraph graph;
	
	graph.loadFromFile("../testFile.txt", false);

	
			
}
