/*
 * Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, 
 * то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
 * 2_2. Выведите элементы в порядке pre-order (сверху вниз).
 */

#include <iostream>
#include <assert.h>
#include <sstream>
#include <functional>
#include <stack>

template <typename T>
class BinaryNode {
public:
    T data;
    BinaryNode* left;
    BinaryNode* right;
    BinaryNode(T data) : data(data), left(NULL), right(NULL) {}
};

template <typename T, typename Comparator = std::less<T>>
class BinaryTree {
    BinaryNode<T>* root;

    void visit(BinaryNode<T>* node);
public:
    BinaryTree() : root(NULL) {}
    ~BinaryTree();
    void pre_order();
    void add(T nodeData, Comparator cmp = Comparator());
};

template <typename T, typename Comparator>
BinaryTree<T, Comparator>::~BinaryTree() {
    std::stack<BinaryNode<T>*> s;
    BinaryNode<T>* lastVisit = NULL;
    BinaryNode<T>* rootNow = root;
 
    while (!s.empty() || rootNow != NULL) {
        if (rootNow) {
            delete rootNow;

            if (rootNow->right) {
                s.push(rootNow->right);
            }

            rootNow = rootNow->left;
        }
        else {
            rootNow = s.top();
            s.pop();
        }
    }
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::visit(BinaryNode<T>* node) {
    std::cout << node->data << " ";
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::pre_order() {
    std::stack<BinaryNode<T>*> s;
    BinaryNode<T>* rootNow = root;
 
    while (!s.empty() || rootNow != NULL) {
        if (rootNow) {
            visit(rootNow);

            if (rootNow->right) {
                s.push(rootNow->right);
            }

            rootNow = rootNow->left;
        }
        else {
            rootNow = s.top();
            s.pop();
        }
    }
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::add(T nodeData, Comparator cmp) {
    BinaryNode<T>* newNode = new BinaryNode<T>(nodeData);
    if (root == NULL) {
        root = newNode;
        return;
    }

    BinaryNode<T>* nextNode = root;
    while (true) {
        if (cmp(nodeData, nextNode->data)) {
            if (nextNode->left != NULL) {
                nextNode = nextNode->left;
                continue;
            }
            else {
                nextNode->left = newNode;
                return;
            }
        }
        else {
            if (nextNode->right != NULL) {
                nextNode = nextNode->right;
                continue;
            }
            else {
                nextNode->right = newNode;
                return;
            }
        }
    }
}

void run(std::istream &is, std::ostream &os) {
    BinaryTree<int> tree;
    int N;
    is >> N;
    for (int i = 0; i < N; ++i) {
        int data;
        is >> data;
        tree.add(data);
    }
    tree.pre_order();
}

int main() {
    run(std::cin, std::cout);
    return 0;
}
