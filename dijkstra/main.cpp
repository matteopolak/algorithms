#include <iostream>
#include <string>

int main() {
	int rows, cols;

	std::cout << "Enter the number of rows: ";
	std::cin >> rows;

	std::cout << "Enter the number of columns: ";
	std::cin >> cols;

	std::string *matrix = new std::string[rows];

	for (int i = 0; i < rows; ++i) {
		std::cout << "Enter the value for row " << i + 1 << ": ";
		std::cin >> matrix[i];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << matrix[i * cols + j] << '\n';
		}

		std::cout << std::endl;
	}
}