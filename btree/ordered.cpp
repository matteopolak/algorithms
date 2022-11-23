#include <iostream>

struct Node {
	int value = 0;
	Node *left = nullptr;
	Node *right = nullptr;
};

bool addNode(Node *root, int value) {
	if (root->value == value) {
		return false;
	}

	if (value < root->value) {
		if (root->left == nullptr) {
			root->left = new Node;
			root->left->value = value;
			return true;
		}

		return addNode(root->left, value);
	}

	if (root->right == nullptr) {
		root->right = new Node;
		root->right->value = value;

		return true;
	}

	return addNode(root->right, value);
}

void print(Node *node) {
	if (node == nullptr) {
		return;
	}

	print(node->left);

	std::cout << node->value;

	print(node->right);
}

int main() {
	int c;
	std::cin >> c;

	Node *root = new Node;

	for (int i = 0; i < c; ++i) {
		int value;
		std::cin >> value;

		addNode(root, value);
	}

	print(root);
}
