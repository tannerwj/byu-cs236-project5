#pragma once
#include <vector>
class Node
{

private:
	std::vector<Node> dependsOn;
public:
	Node(void);
	~Node(void);
};

