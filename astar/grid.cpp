#include "grid.h"

#include <iostream>

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
	this->nodes = std::unordered_map<int, Node>();
	this->start = INT_MAX;
	this->goals = std::vector<int>();
}

void Grid::add(Node n) {
	this->nodes[n.y * this->cols + n.x] = n;
}

Grid Grid::fromLines(std::vector<std::string> lines) {
	int rows = lines.size();

	// ensure lines[0] exists
	if (rows == 0) {
		return Grid(0, 0);
	}

	int cols = lines[0].length();

	Grid grid(rows, cols);

	for (int y = 0; y < lines.size(); y++) {
		int xcols = lines[y].length();

		if (xcols != cols) {
			std::cout << "Error: line " << y << " has " << xcols
								<< " columns (expected " << cols << ")\n";
			return Grid(0, 0);
		}

		for (int x = 0; x < xcols; x++) {
			NodeType type = (NodeType) lines[y][x];
			Node node = Node(type, x, y, cols);

			if (type == NodeType::Goal) {
				grid.goals.push_back(node.getKey());

			} else if (type == NodeType::Start) {
				if (grid.start != INT_MAX) {
					std::cout << "Error: multiple start nodes\n";

					return Grid(0, 0);
				}

				grid.start = node.getKey();
			}

			grid.add(node);
		}
	}

	return grid;
}

// if there are multiple goals, return the heuristic of the closest one
int Grid::heuristic(Node *a) {
	int min = INT_MAX;

	for (int key : this->goals) {
		Node goal = this->nodes[key];
		int dist = abs(goal.x - a->x) + abs(goal.y - a->y);

		if (dist < min) {
			min = dist;
		}
	}

	return min;
}
