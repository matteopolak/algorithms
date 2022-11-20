#ifndef NODE_H_
#define NODE_H_

#include <vector>

class Node {
 public:
	int x;
	int y;
	std::vector<Node*> neighbours;

	Node(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void addNeighbour(Node* n) {
		neighbours.push_back(n);
	}

	int key() {
		return x * 10 + y;
	}
};

#endif /* NODE_H_ */