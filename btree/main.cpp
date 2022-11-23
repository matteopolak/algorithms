#include <iostream>

struct Node {
	int value = 0;
	Node *left = nullptr;
	Node *right = nullptr;
};

void print(Node *node) {
	if (node == nullptr) {
		return;
	}

	print(node->left);

	std::cout << node->value;

	print(node->right);
}

void reverse(Node *node) {
	if (node == nullptr) {
		return;
	}

	reverse(node->left);
	reverse(node->right);

	Node *temp = node->left;
	node->left = node->right;
	node->right = temp;
}

int main() {
	// create a random btree
	Node *root = new Node;
	root->value = 1;
	root->left = new Node;
	root->left->value = 2;
	root->left->left = new Node;
	root->left->left->value = 4;
	root->left->right = new Node;
	root->left->right->value = 5;
	root->right = new Node;
	root->right->value = 3;
	root->right->left = new Node;
	root->right->left->value = 6;
	root->right->right = new Node;
	root->right->right->value = 7;

	// print the btree
	print(root);

	// reverse the btree
	reverse(root);

	// print the btree
	print(root);
}
