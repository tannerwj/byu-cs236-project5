#pragma once
#include <set>
class Node
{

private:
	std::set<std::string> myChrldren;
	bool visited;
	int postorder;

public:
	Node(void);
	~Node(void);
};

