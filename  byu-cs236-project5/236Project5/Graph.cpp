#include "Graph.h"
#include <iostream>


Graph::Graph(void){}
Graph::~Graph(void){}

Graph::Graph(std::string n, std::vector<Rule> r){

	std::vector<Rule>::iterator ruleIter;
	std::map<std::string, Node>::iterator graphIter;

	createGraph(r);

	for ( graphIter = graph.begin(); graphIter != graph.end(); graphIter++) {
			std::cout << graphIter->first << "\n";
			std::cout << "\t" << graphIter->second.toString() << "\n";
	}

}

void Graph::createGraph(std::vector<Rule> r){
	std::vector<Rule>::iterator ruleIter;

	for ( ruleIter = r.begin(); ruleIter < r.end(); ruleIter++) {

		if ( graph.find(ruleIter->getHead().getName()) == graph.end() ) {
			Node temp = Node();

			for(int i = 0; i < ruleIter->getPredicateNames().size(); i++)
				temp.addChild(ruleIter->getPredicateNames().at(i));	

				graph[ruleIter->getHead().getName()] = temp;

		} else {
			for(int i = 0; i < ruleIter->getPredicateNames().size(); i++)
				graph[ruleIter->getHead().getName()].addChild(ruleIter->getPredicateNames().at(i));
		}
			
	}
}

void Graph::buildDFStree(){
}

void Graph::findCycles(){
}

void Graph::sortGraph(){
}

void Graph::makeList(){
}
