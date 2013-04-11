#include "Node.h"


Node::Node(void){
	bool visited = false;
	int postorder = 0;
}
Node::~Node(void){}

void Node::addChild(std::string s){
	myChildren.push_back(s);
}

void Node::setVisited(){
	visited = true;
}

bool Node::isVisited(){
	return visited;
}

std::string Node::toString(){
	std::string temp = "";
	for (int i = 0; i < myChildren.size(); i++){

		if (i > 0)
			temp += ",";

		temp += myChildren.at(i);

	}
	
	return temp;
}