#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int key) {
        data = key;
        left = right = nullptr;
        height = 1;
    }
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node* rightRotate(Node* node) {
    Node* l1 = node->left;
    Node* r1 = l1->right;

    l1->right = node;
    node->left = r1;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    l1->height = 1 + std::max(getHeight(l1->left), getHeight(l1->right));

    return l1;
}

Node* leftRotate(Node* node) {
    Node* r1 = node->right;
    Node* l1 = r1->left;

    r1->left = node;
    node->right = l1;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    r1->height = 1 + std::max(getHeight(r1->left), getHeight(r1->right));

    return r1;
}

Node* minValue(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* insert(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->data) {
        node->left = insert(node->left, key);
    } else if (key > node->data) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->data) {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->data) {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* del(Node* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->data) {
        root->left = del(root->left, key);
    } else if (key > root->data) {
        root->right = del(root->right, key);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
        } else {
            Node* temp = minValue(root->right);
            root->data = temp->data;
            root->right = del(root->right, temp->data);
        }
    }

    if (root == nullptr) {
        return root;
    }

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(Node* root, int count) {
    if (count == 1 && root == nullptr) {
        std::cout << "EMPTY" << std::endl;
        return;
    }

    if (root != nullptr) {
        inorder(root->left, count + 1);
        std::cout << root->data << " ";
        inorder(root->right, count + 1);
    }
}

void preorder(Node* root, int count) {
    if (root == nullptr && count == 1) {
        std::cout << "EMPTY" << std::endl;
        return;
    }

    if (root != nullptr) {
        std::cout << root->data << " ";
        preorder(root->left, count + 1);
        preorder(root->right, count + 1);
    }
}

void postorder(Node* root, int count) {
    if (root == nullptr && count == 1) {
        std::cout << "EMPTY" << std::endl;
        return;
    }

    if (root != nullptr) {
        postorder(root->left, count + 1);
        postorder(root->right, count + 1);
        std::cout << root->data << " ";
    }
}

int main(void) {
    std::string in;
    std::getline(std::cin, in);
    std::istringstream stream(in);
    std::string com;
    std::vector<std::string> commands;

    Node* root = nullptr;

    while (stream >> com) {
        commands.push_back(com);
    }

    for (int i = 0; i < commands.size(); i++) {
        if (commands[i][0] == 'A') {
            root = insert(root, std::stoi(commands[i].substr(1)));
        } else if (commands[i][0] == 'D') {
            root = del(root, std::stoi(commands[i].substr(1)));
        } else if (commands[i] == "IN") {
            inorder(root, 1);
        } else if (commands[i] == "PRE") {
            preorder(root, 1);
        } else if (commands[i] == "POST") {
            postorder(root, 1);
        }
    }
}