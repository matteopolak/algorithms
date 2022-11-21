#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "grid.h"
#include "node.h"

std::vector<Node*> reconstructPath(
	std::unordered_map<int, Node*> from, Node* current
) {
	std::vector<Node*> path = std::vector<Node*>();

	path.push_back(current);

	while (from.find(current->getKey()) != from.end()) {
		current = from[current->getKey()];
		path.push_back(current);
	}

	std::reverse(path.begin(), path.end());

	return path;
}

std::vector<Node*> aStar(Node* root, Grid grid) {
	std::vector<Node*> open = std::vector<Node*>();

	// add the root node to the open list
	open.push_back(root);

	std::unordered_map<int, Node*> from = std::unordered_map<int, Node*>();
	std::unordered_map<int, int> gScore = std::unordered_map<int, int>();
	std::unordered_map<int, int> fScore = std::unordered_map<int, int>();

	// set the score for all nodes to -1
	for (auto const& x : grid.nodes) {
		gScore[x.first] = INT_MAX;
		fScore[x.first] = INT_MAX;
	}

	// set the root node's gScore to 0
	gScore[root->getKey()] = 0;

	// set the root node's fScore to the heuristic value
	fScore[root->getKey()] = grid.heuristic(root);

	// while there are still nodes to explore
	while (open.size() > 0) {
		// get the node with the lowest f score from the open list
		Node* current = open[0];
		int lowest = fScore[current->getKey()];

		for (int i = 1; i < open.size(); i++) {
			int score = fScore[open[i]->getKey()];

			if (score < lowest) {
				current = open[i];
				lowest = score;
			}
		}

		// if the node is a goal, we're done!
		if (grid.heuristic(current) == 0) {
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
			int tentativeGScore = gScore[current->getKey()] + 1;

			// if the tentative g score is greater than the neighbour's current
			// g score, skip it
			if (tentativeGScore >= gScore[neighbour->getKey()]) {
				continue;
			}

			// set the neighbour's parent to the current node
			from[neighbour->getKey()] = current;

			// set the neighbour's g score to the tentative g score
			gScore[neighbour->getKey()] = tentativeGScore;

			// set the neighbour's f score to the g score + the heuristic value
			fScore[neighbour->getKey()] =
				gScore[neighbour->getKey()] + grid.heuristic(neighbour);
		}
	}

	return std::vector<Node*>();
}

void addNeighbours(Grid* grid, Node* root, std::unordered_set<int>* seen) {
	std::vector<Node*> process = std::vector<Node*>();

	if (seen->find(root->getKey()) != seen->end()) {
		return;
	}

	// check up
	if (root->y > 0 && grid->nodes.find(root->getKey() - grid->cols) != grid->nodes.end()) {
		if (std::find(root->neighbours.begin(), root->neighbours.end(), &grid->nodes[root->getKey() - grid->cols]) == root->neighbours.end()) {
			Node* up = &grid->nodes[root->getKey() - grid->cols];

			if (up->type != NodeType::Wall) {
				root->addNeighbour(up);
				up->addNeighbour(root);
				process.push_back(up);
			}
		}
	}

	// check down
	if (root->y < grid->rows - 1 && grid->nodes.find(root->getKey() + grid->cols) != grid->nodes.end()) {
		if (std::find(root->neighbours.begin(), root->neighbours.end(), &grid->nodes[root->getKey() + grid->cols]) == root->neighbours.end()) {
			Node* down = &grid->nodes[root->getKey() + grid->cols];

			if (down->type != NodeType::Wall) {
				root->addNeighbour(down);
				down->addNeighbour(root);
				process.push_back(down);
			}
		}
	}

	// check left
	if (root->x > 0 && grid->nodes.find(root->getKey() - 1) != grid->nodes.end()) {
		if (std::find(root->neighbours.begin(), root->neighbours.end(), &grid->nodes[root->getKey() - 1]) == root->neighbours.end()) {
			Node* left = &grid->nodes[root->getKey() - 1];

			if (left->type != NodeType::Wall) {
				root->addNeighbour(left);
				left->addNeighbour(root);
				process.push_back(left);
			}
		}
	}

	// check right
	if (root->x < grid->cols - 1 && grid->nodes.find(root->getKey() + 1) != grid->nodes.end()) {
		if (std::find(root->neighbours.begin(), root->neighbours.end(), &grid->nodes[root->getKey() + 1]) == root->neighbours.end()) {
			Node* right = &grid->nodes[root->getKey() + 1];

			if (right->type != NodeType::Wall) {
				root->addNeighbour(right);
				right->addNeighbour(root);
				process.push_back(right);
			}
		}
	}

	for (int i = 0; i < process.size(); i++) {
		addNeighbours(grid, process[i], seen);
	}
}

int main() {
	int rows;

	std::cout << "Enter the number of rows: ";
	std::cin >> rows;

	std::vector<std::string> lines = std::vector<std::string>();

	for (int i = 0; i < rows; ++i) {
		std::string line;

		std::cout << "Enter row " << i << ": ";
		std::cin >> line;

		lines.push_back(line);
	}

	Grid grid = Grid::fromLines(lines);

	std::unordered_map<int, Node*> nodes;
	std::unordered_set<int> seen;

	// iterate through the maze, starting from the root node
	// and recursively adding neighbours to each node as we go

	Node start = grid.nodes[grid.start];

	addNeighbours(&grid, &start, &seen);

	// use A* to find the shortest path from the root node to the node at the
	// bottom right
	std::vector<Node*> path = aStar(&start, grid);

	// print the path
	for (Node* n : path) {
		lines[n->y][n->x] = '*';
	}

	for (int i = 0; i < 7; i++) {
		std::cout << lines[i] << '\n';
	}
}
