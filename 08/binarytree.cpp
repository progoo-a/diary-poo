#include <functional>
#include <stack>
#include <iostream>

struct Node {
    int value = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

class Tree {
    Node* root;

public:
    void insert(int value) {
        Node* node = new Node{value, nullptr, nullptr};

        if (!root) {
            root = node;
            return;
        }

        Node* current = root;
        while (true) {
            if (value < current->value) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = node;
                    break;
                }
            } else {
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = node;
                    break;
                }
            }
        }
    }

    // DFS means Depth First Search
    auto dfs(std::function<void(Node*)> f) {
        std::stack<Node*> stack;
        stack.push(root);
        while (!stack.empty()) {
            Node* node = stack.top();
            stack.pop();
            f(node);
            if (node->right) stack.push(node->right);
            if (node->left) stack.push(node->left);
        }
    }
};

int main() {
    Tree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    tree.dfs([](Node* node) {
        std::cout << node->value << " ";
    });
    std::cout << std::endl;
}