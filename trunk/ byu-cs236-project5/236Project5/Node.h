#pragma once
#include <vector>
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
	void setVisited();
	bool isVisited();
	std::vector<std::string> getChildren();
	std::string toString();
};

