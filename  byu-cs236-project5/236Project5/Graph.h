#pragma once
#include "Node.h"
#include "Rule.h"
#include <map>
#include <vector>
#include <queue>
#include <utility>

typedef std::pair<std::string,std::string>	Cycle;
typedef std::vector<Cycle>					Cycles;

class Graph
{

private:
	std::map	<std::string, Node>		graph;
	std::vector	<std::string>			DFSTree;
	Cycles								myCycles;

	void createGraph(std::vector<Rule>);
	void buildDFStree(std::string);
	void findCycles(std::string);
	void consolidateCycles();
	void printCycles();
	void sortGraph();

public:
	Graph(void);
	~Graph(void);
	Graph(std::string, std::vector<Rule>);

	std::vector<std::string> makeList();
	Cycles getCycles();

	/*
	(1) create the depends-on graph, 
	(2) build the depthfirst search tree that is produced for a given query (to initialize the traversal order), 
	(3) find cycles in a graph, 
	(4) topologically sort an acyclic graph (a search tree without back arrows in the project), and 
	(5) create a list, possibly
		with cycles, to direct rule execution.
	*/

};

