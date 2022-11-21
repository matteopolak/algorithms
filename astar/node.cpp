#include "node.h"

Node::Node(NodeType type, int x, int y, int cols)
		: type(type), x(x), y(y), cols(cols) {}

void Node::addNeighbour(Node* n) {
	this->neighbours.push_back(n);
}

int Node::getKey() {
	return this->y * this->cols + this->x;
}
