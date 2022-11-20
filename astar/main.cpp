#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

#include "node.h"

int heuristic(Node* a) {
	// Manhattan distance
	return abs(a->x - 8) + abs(a->y - 6);
}

std::vector<Node*> reconstructPath(
	std::unordered_map<int, Node*> from, Node* current
) {
	std::vector<Node*> path = std::vector<Node*>();

	while (from.find(current->key()) != from.end()) {
		current = from[current->key()];
		path.push_back(current);
	}

	return path;
}

std::vector<Node*> aStar(
	Node* root, std::string lines[], std::unordered_map<int, Node*> nodes
) {
	std::vector<Node*> open = std::vector<Node*>();

	// add the root node to the open list
	open.push_back(root);

	std::unordered_map<int, Node*> from = std::unordered_map<int, Node*>();
	std::unordered_map<int, int> gScore = std::unordered_map<int, int>();
	std::unordered_map<int, int> fScore = std::unordered_map<int, int>();

	// set the score for all nodes to -1
	for (auto const& x : nodes) {
		gScore[x.first] = std::numeric_limits<int>::max();
		fScore[x.first] = std::numeric_limits<int>::max();
	}

	// set the root node's gScore to 0
	gScore[root->key()] = 0;

	// set the root node's fScore to the heuristic value
	fScore[root->key()] = heuristic(root);

	// while there are still nodes to explore
	while (open.size() > 0) {
		// get the node with the lowest f score from the open list
		Node* current = open[0];

		for (int i = 1; i < open.size(); i++) {
			if (fScore[open[i]->key()] < fScore[current->key()]) {
				current = open[i];
			}
		}

		// if the node is the goal node, return the path
		if (current->x == 8 && current->y == 6) {
			return reconstructPath(from, current);
		}

		// remove the node from the open list
		open.erase(std::remove(open.begin(), open.end(), current), open.end());

		// for each neighbour of the node
		for (int i = 0; i < current->neighbours.size(); i++) {
			Node* neighbour = current->neighbours[i];

			// if the neighbour is not in the open list, add it
			if (std::find(open.begin(), open.end(), neighbour) == open.end()) {
				open.push_back(neighbour);
			}

			// calculate the tentative g score for the neighbour
			int tentativeGScore = gScore[current->key()] + 1;

			// if the tentative g score is greater than the neighbour's current
			// g score, skip it
			if (tentativeGScore >= gScore[neighbour->key()]) {
				continue;
			}

			// set the neighbour's parent to the current node
			from[neighbour->key()] = current;

			// set the neighbour's g score to the tentative g score
			gScore[neighbour->key()] = tentativeGScore;

			// set the neighbour's f score to the g score + the heuristic value
			fScore[neighbour->key()] =
				gScore[neighbour->key()] + heuristic(neighbour);
		}
	}

	return std::vector<Node*>();
}

void addNeighbours(
	Node* n, std::string lines[], std::unordered_map<int, Node*>& nodes
) {
	std::vector<Node*> process = std::vector<Node*>();

	// add the node to the nodes map
	nodes[n->key()] = n;

	// check up
	if (n->y > 0 && lines[n->y - 1][n->x] == ' ') {
		// make sure the node isn't already present
		if (nodes.find((n->x * 10) + (n->y - 1)) == nodes.end()) {
			// create the node
			Node* up = new Node(n->x, n->y - 1);

			// add the node to the process list
			n->addNeighbour(up);
			up->addNeighbour(n);
			process.push_back(up);
		}
	}

	// check down
	if (n->y < 6 && lines[n->y + 1][n->x] == ' ') {
		// make sure the node isn't already present
		if (nodes.find((n->x * 10) + (n->y + 1)) == nodes.end()) {
			// create the node
			Node* down = new Node(n->x, n->y + 1);

			// add the node to the process list
			n->addNeighbour(down);
			down->addNeighbour(n);
			process.push_back(down);
		}
	}

	// check left
	if (n->x > 0 && lines[n->y][n->x - 1] == ' ') {
		// make sure the node isn't already present
		if (nodes.find(((n->x - 1) * 10) + n->y) == nodes.end()) {
			// create the node
			Node* left = new Node(n->x - 1, n->y);

			// add the node to the process list
			n->addNeighbour(left);
			left->addNeighbour(n);
			process.push_back(left);
		}
	}

	// check right
	if (n->x < 8 && lines[n->y][n->x + 1] == ' ') {
		// make sure the node isn't already present
		if (nodes.find(((n->x + 1) * 10) + n->y) == nodes.end()) {
			// create the node
			Node* right = new Node(n->x + 1, n->y);

			// add the node to the process list
			n->addNeighbour(right);
			right->addNeighbour(n);
			process.push_back(right);
		}
	}

	for (int i = 0; i < process.size(); i++) {
		addNeighbours(process[i], lines, nodes);
	}
}

int main() {
	// clang-format off
	std::string lines[] = {
		"  #######",
		"#       #",
		"# # ### #",
		"# #   # #",
		"# ### # #",
		"#   #   #",
		"#######  "
	};
	// clang-format on

	Node root = Node(0, 0);
	std::unordered_map<int, Node*> nodes;

	// iterate through the maze, starting from the root node
	// and recursively adding neighbours to each node as we go
	addNeighbours(&root, lines, nodes);

	// use A* to find the shortest path from the root node to the node at the
	// bottom right
	std::vector<Node*> path = aStar(&root, lines, nodes);

	// print the path
	for (Node* n : path) {
		lines[n->y][n->x] = '*';
	}

	lines[6][8] = '*';

	for (int i = 0; i < 7; i++) {
		std::cout << lines[i] << '\n';
	}
}