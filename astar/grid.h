#ifndef __GRID_H_
#define __GRID_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "node.h"

class Grid {
 public:
	int rows, cols;
	std::unordered_map<int, Node> nodes;
	int start;
	std::vector<int> goals;

	Grid(int rows, int cols);

	void add(Node n);

	static Grid fromLines(std::vector<std::string> lines);

	// if there are multiple goals, return the heuristic of the closest one
	int heuristic(Node *a);
};

#endif /* GRID_H_ */
