#include "Graph.h"
#include <iostream>
#include <stack>


Graph::Graph(void){}
Graph::~Graph(void){}

Graph::Graph(std::string n, std::vector<Rule> r){

	std::vector<Rule>::iterator ruleIter;
	std::map<std::string, Node>::iterator graphIter;

	createGraph(r);
	graph[n].setVisited(true);
	buildDFStree(n);
	findCycles(n);

	//for (int i = 0; i < DFSTree.size(); i++)
		//std::cout << graph[DFSTree.at(i)].getPostOrder() << ": " << DFSTree.at(i) << "\n";

	//printCycles();
	consolidateCycles();
	//printCycles();



	//for ( graphIter = graph.begin(); graphIter != graph.end(); graphIter++) {
		//	std::cout << graphIter->first << "\n";
		//	std::cout << "\t" << graphIter->second.toString() << "\n";
	//}

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

void Graph::buildDFStree(std::string n){
	for (int i = 0; i < graph[n].getChildren().size(); i++){
		if (!graph[graph[n].getChildren().at(i)].isVisited()){
			graph[graph[n].getChildren().at(i)].setVisited(true);
			buildDFStree(graph[n].getChildren().at(i));
		}
	}
	DFSTree.push_back(n);
	graph[n].setPostOrder(DFSTree.size());
}

void Graph::findCycles(std::string n){
	Node currentNode = graph[n];

	for(int i = 0; i < currentNode.getChildren().size(); i++){

		int myPostOrder		=	currentNode.getPostOrder();
		int childsPostOrder =	graph[currentNode.getChildren().at(i)].getPostOrder();

		if (myPostOrder - childsPostOrder <= 0)
			myCycles.push_back(std::make_pair(n,currentNode.getChildren().at(i)));

		graph[n].setVisited(false);

		if (graph[currentNode.getChildren().at(i)].isVisited())
			findCycles(currentNode.getChildren().at(i));
	}

}

void Graph::consolidateCycles(){

	std::stack <Cycle>	newCycles;

	for (int i = 0; i < DFSTree.size(); i++){

		for (int j = 0; j < myCycles.size(); j++){

			if(myCycles.at(j).first == DFSTree.at(i)){
				if(newCycles.size() == 0){
					newCycles.push(myCycles.at(j));
				} else {
					if(graph[myCycles.at(j).first].getPostOrder() > graph[newCycles.top().second].getPostOrder()){
						newCycles.push(myCycles.at(j));
					} else {

						if(graph[myCycles.at(j).second].getPostOrder() >= graph[newCycles.top().second].getPostOrder()){
							Cycle temp = newCycles.top();
							newCycles.pop();
							temp.second = myCycles.at(j).second;
							newCycles.push(temp);
						}
					}
				}

			}

		}
	}

	myCycles.clear();
	while(!newCycles.empty()){
		myCycles.push_back(newCycles.top());
		newCycles.pop();
	}
}

void Graph::printCycles(){
	std::vector<std::pair<std::string,std::string> >::iterator cycleIter;
	std::cout << "<---Backward Edges--->\n";

	for(cycleIter = myCycles.begin(); cycleIter < myCycles.end(); cycleIter++)
		std::cout << "  " << cycleIter->first << " -> " << cycleIter->second << "\n";

	std::cout << "\n";
}

std::vector<std::string> Graph::makeList(){
	return DFSTree;
}

Cycles Graph::getCycles(){
	return myCycles;
}
