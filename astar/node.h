#ifndef __NODE_H_
#define __NODE_H_

#include <vector>

enum class NodeType {
	Empty = '.',
	Wall = '#',
	Start = 'S',
	Goal = 'G',
};

class Node {
 public:
	NodeType type;
	std::vector<Node*> neighbours;
	int x;
	int y;

	Node(NodeType type, int x, int y, int cols);
	Node() = default;

	void addNeighbour(Node* n);

	int getKey();

 private:
	int cols;
};

#endif /* NODE_H_ */
