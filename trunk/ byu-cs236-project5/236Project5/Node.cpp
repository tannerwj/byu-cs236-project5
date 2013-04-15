#include "Node.h"


Node::Node(void){
	visited = false;
	postorder = 0;
}
Node::~Node(void){}

void Node::addChild(std::string s){
	myChildren.push_back(s);
}

void Node::setVisited(bool value){
	visited = value;
}

bool Node::isVisited(){
	return visited;
}

void Node::setPostOrder(int n){
	postorder = n;
}

int Node::getPostOrder(){
	return postorder;
}

std::vector<std::string> Node::getChildren(){
	return myChildren;
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