#include <iostream>

template<typename T>
class TreeNode {
public:
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinaryTree {
private:
    TreeNode<T>* root;

    void clear(TreeNode<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    TreeNode<T>* copy(TreeNode<T>* node) {
        if (!node) return nullptr;
        TreeNode<T>* newNode = new TreeNode<T>(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const BinaryTree& other) : root(copy(other.root)) {}

    BinaryTree(BinaryTree&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear(root);
            root = copy(other.root);
        }
        return *this;
    }

    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this != &other) {
            clear(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    ~BinaryTree() {
        clear(root);
    }

    void insert(const T& value) {
        if (!root) {
            root = new TreeNode<T>(value);
        } else {
            TreeNode<T>* current = root;
            while (true) {
                if (value < current->data) {
                    if (!current->left) {
                        current->left = new TreeNode<T>(value);
                        break;
                    }
                    current = current->left;
                } else {
                    if (!current->right) {
                        current->right = new TreeNode<T>(value);
                        break;
                    }
                    current = current->right;
                }
            }
        }
    }

    void inorder(TreeNode<T>* node) const {
        if (node) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

    void display() const {
        inorder(root);
        std::cout << std::endl;
    }

    TreeNode<T>* getRoot() const {
        return root;
    }
};
