#pragma once
#include <vector>
#include <string>

class Node
{

private:
	std::vector<std::string> myChildren;
	bool visited;
	int postorder;

public:
	Node(void);
	~Node(void);
	void addChild(std::string);
	void setVisited(bool);
	bool isVisited();
	void setPostOrder(int);
	int getPostOrder();
	std::vector<std::string> getChildren();
	std::string toString();
};

