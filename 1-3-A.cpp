#include <iostream>
#include <string>
 
using namespace std;
 
struct Node
{
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) { key = k; left = right = 0; height = 1; }
};
 
class AVL {
public:
    AVL();
    ~AVL();
 
    void Insert(int);
    void Erase(int);
    void Exists(int);
    void Next(int);
    void Prev(int);
 
private:
    Node* root;
 
    Node* insert(int, Node*);
    Node* rebalance(Node*);
    Node* deleteNode(int, Node*);
    Node* deleteMin(Node*);
 
    int findMin(Node*);
    int balance(Node*);
    void fixheight(Node*);
    int height(Node*);
    Node* rightRotate(Node*);
    Node* leftRotate(Node*);
 
    bool exist(int, Node*);
    int next_node(int, Node*);
    int prev_node(int, Node*);
};
 
AVL::AVL(): root(nullptr)
{
}
 
AVL::~AVL() {
    while (root != nullptr) {
        Erase(root->key);
    }
}
 
 
void AVL::Insert(int key) {
    root = insert(key, root);
}
 
Node* AVL::insert(int key, Node* node) {
    if (node == nullptr) return new Node(key);
    if (key > node->key) node->right = insert(key, node->right);
    else if (key == node->key) return (node);
    else node->left = insert(key, node->left);
    return rebalance(node);
}
 
Node* AVL::rebalance(Node* node) {
    fixheight(node);
    if (balance(node) == 2) {
        if (balance(node->right) < 0) node->right = rightRotate(node->right);
        return(leftRotate(node));
    }
    if (balance(node) == -2) {
        if (balance(node->left) > 0) node->left = leftRotate(node->left);
        return(rightRotate(node));
    }
    return node;
}
 
int AVL::height(Node* node) {
    return node ? node->height : 0;
}
 
void AVL::fixheight(Node* node) {
    node->height = height(node->right) > height(node->left) ? height(node->right) + 1 : height(node->left) + 1;
}
 
int AVL::balance(Node* node) {
    return height(node->right) - height(node->left);
}
 
Node* AVL::rightRotate(Node* node) {
    Node* p = node->left;
    node->left = p->right;
    p->right = node;
    fixheight(node);
    fixheight(p);
    return(p);
}
 
Node* AVL::leftRotate(Node* node) {
    Node* p = node->right;
    node->right = p->left;
    p->left = node;
    fixheight(node);
    fixheight(p);
    return(p);
}
 
void AVL::Erase(int key) {
    root = deleteNode(key, root);
}
 
Node* AVL::deleteNode(int key, Node* node) {
    if (node == nullptr) return nullptr;
    if (key > node->key) {
        node->right = deleteNode(key, node->right);
        return rebalance(node);
    }
    else if (key < node->key) {
        node->left = deleteNode(key, node->left);
        return rebalance(node);
    }
    else {
        if (node->right == nullptr) {
            Node* left_son = node->left;
            delete node;
            return left_son;
        }
        else {
            int minimum = findMin(node->right);
            Node* ans = new Node(minimum);
            Node* left_1 = node->left;
            Node* right_1 = deleteMin(node->right);
            ans->left = left_1;
            ans->right = right_1;
            delete node;
            return rebalance(ans);
        }
    }
}
 
int AVL::findMin(Node* node){
    if (node->left == nullptr) return node->key;
    return findMin(node->left);
}
 
Node* AVL::deleteMin(Node* node) {
    if (node->left == nullptr) {
        Node* ans = node->right;
        delete node;
        return ans;
    }
    node->left = deleteMin(node->left);
    return rebalance(node);
}
 
void AVL::Exists(int key) {
    if (exist(key, root)) std::cout << "true" << "\n";
    else std::cout << "false" << "\n";
}
 
bool AVL::exist(int key, Node* node) {
    if (node == nullptr) return 0;
    if (node->key == key) return 1;
    if (key > node->key) return exist(key, node->right);
    return exist(key, node->left);
}
 
void AVL::Next(int key) {
    int a = next_node(key, root);
    if (a == 1000000001) std::cout << "none" << "\n";
    else std::cout << a << "\n";
}
 
int AVL::next_node(int key, Node* node) {
    int min = 1000000001;
    while (node != nullptr) {
        if (node->key < min and node->key > key) min = node->key;
        if (node->key > key) node = node->left;
        else node = node->right;
    }
    return min;
}
 
void AVL::Prev(int key) {
    int a = prev_node(key, root);
    if (a == -1000000001) cout << "none" << "\n";
    else cout << a << "\n";
}
 
 
int AVL::prev_node(int key, Node* node) {
    int max = -1000000001;
    while (node != nullptr) {
        if (node->key > max and node->key < key) max = node->key;
        if (node->key < key) node = node->right;
        else node = node->left;
    }
    return max;
}
 
void solve(string s, int x, AVL& tree){
    if (s == "insert") {
        tree.Insert(x);
    }
    if (s == "delete") {
        tree.Erase(x);
    }
    if (s == "exists") {
        tree.Exists(x);
    }
    if (s == "prev") {
        tree.Prev(x);
    }
    if (s == "next") {
        tree.Next(x);
    }
}
 
int main() {
    AVL tree;
    int x = 0;
    string s = "";
    while (std::cin >> s) {
        cin >> x;
        solve(s, x, tree);
    }
    return 0;
}
