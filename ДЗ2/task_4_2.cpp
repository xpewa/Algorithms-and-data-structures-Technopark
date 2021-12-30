/*
 * Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел, 
 * а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, 
 * команда удаления числа A задается отрицательным числом “-A”. 
 * Запрос на получение k-ой порядковой статистики задается числом k. 
 * Требуемая скорость выполнения запроса - O(log n).
 */

#include <iostream>
#include <sstream>
#include <functional>
using namespace std;

template <typename T>
struct Node {
    Node(const T& key) 
        : key(key), left(nullptr), right(nullptr), height(1), count(1) {}
    T key;
    Node* left;
    Node* right;
    size_t height;
    size_t count;
};

template <typename T, typename Comparator = less<T>>
class AvlTree {
    Node<T>* root;

    Node<T>* addInternal(Node<T>* node, const T& key, Comparator cmp = Comparator());
    Node<T>* deleteInternal(Node<T>* node, const T& key, Comparator cmp = Comparator());
    Node<T>* doBalance(Node<T>* node);
    int getBalance(Node<T>* node);
    size_t getHeight(Node<T>* node);
    size_t getCount(Node<T>* node);
    void fixHeight(Node<T>* node);
    void fixCount(Node<T>* node);
    Node<T>* findMin(Node<T>* node);
    Node<T>* removeMin(Node<T>* node);
    Node<T>* rotateLeft(Node<T>* node);
    Node<T>* rotateRight(Node<T>* node);
    void destroyTree(Node<T>* node);
public:
    AvlTree() : root(nullptr) {}
    ~AvlTree() {destroyTree(root);}

    void add(const T& key);
    bool has(const T& key, Comparator cmp = Comparator());
    void delete_at(const T& key);
    T findKStatistic(int k, Comparator cmp = Comparator());
};

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::destroyTree(Node<T>* node) {
    if (!node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template <typename T, typename Comparator>
bool AvlTree<T, Comparator>::has(const T& key, Comparator cmp) {
    Node<T> *tmp = root;
    while (tmp) {
        if (tmp->key == key)
            return true;
        else if (cmp(tmp->key, key)) { //tmp->key < key
            tmp = tmp->right;
        }
        else {
            tmp = tmp->left;
        }
    }
    return false;
}

template <typename T, typename Comparator>
Node<T>* AvlTree<T, Comparator>::addInternal(Node<T>* node, const T& key, Comparator cmp) {
    if (!node) 
        return new Node<T>(key);
    if (cmp(key, node->key)) {
        node->left = addInternal(node->left, key);
    }
    else {
        node->right = addInternal(node->right, key);
    }

    return doBalance(node);
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::add(const T& key) {
    root = addInternal(root, key);
}

template <typename T, typename Comparator>
Node<T>* AvlTree<T, Comparator>::deleteInternal(Node<T>* node, const T& key, Comparator cmp) {
    if (!node)
        return nullptr;
    if (cmp(node->key, key)) { //node->key < key
        node->right = deleteInternal(node->right, key);
    }
    else if (node->key != key) {
        node->left = deleteInternal(node->left, key);
    }
    else {
        Node<T> *left = node->left;
        Node<T> *right = node->right;

        delete node;

        if (!right)
            return left;  
        Node<T> *min = findMin(right);
        min->right = removeMin(right);
        min->left = left;

        return doBalance(min);
    }
    return doBalance(node);
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::delete_at(const T& key) {
    root = deleteInternal(root, key);
}

template <typename T, typename Comparator>
Node<T>* AvlTree<T, Comparator>::findMin(Node<T>* node) {
    while (node->left)
        node = node->left;
    return node;
}

template <typename T, typename Comparator>
Node<T>* AvlTree<T, Comparator>::removeMin(Node<T>* node) {
    if (!node->left)
        return node->right;
    node->left = removeMin(node->left);
    return doBalance(node);
}

template <typename T, typename Comparator>
int AvlTree<T, Comparator>::getBalance(Node<T>* node) {
    return getHeight(node->right) - getHeight(node->left);
}

template <typename T, typename Comparator>
Node<T>* AvlTree<T, Comparator>::doBalance(Node<T>* node) {
    fixHeight(node);
    fixCount(node);

    switch (getBalance(node)) {
        case 2: {
            if (getBalance(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
            break;
        }
        case -2: {
            if (getBalance(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
            break;
        }
        default:
            return node;
    }
}

template <typename T, typename Comparator>
size_t AvlTree<T, Comparator>::getHeight(Node<T>* node) {
    return node ? node->height : 0;
}

template <typename T, typename Comparator>
size_t AvlTree<T, Comparator>::getCount(Node<T>* node) {
    return node ? node->count : 0;
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::fixHeight(Node<T>* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::fixCount(Node<T>* node) {
    node->count = getCount(node->left) + getCount(node->right) + 1;
}

template <typename T, typename Comparator>
Node<T>* AvlTree<T, Comparator>::rotateLeft(Node<T>* node) {
    Node<T>* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    fixHeight(node);
    fixCount(node);
    fixHeight(tmp);
    fixCount(tmp);
    return tmp;
}

template <typename T, typename Comparator>
Node<T>* AvlTree<T, Comparator>::rotateRight(Node<T>* node) {
    Node<T>* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    fixHeight(node);
    fixCount(node);
    fixHeight(tmp);
    fixCount(tmp);
    return tmp;
}

template <typename T, typename Comparator>
T AvlTree<T, Comparator>::findKStatistic(int k, Comparator cmp) {
    T result;
	Node<T>* node = root;
	size_t index = getCount(root->left);
	while (index != k) {
		if (cmp(index, k)) { //k > index
			node = node->right;
			index += getCount(node->left) + 1;
		} else {
			node = node->left;
			index -= getCount(node->right) + 1;
		}
	}
	result = node->key;
    return result;
}

void run(istream &is, ostream &os) {
    AvlTree<int> tree;
    int N;
    is >> N;
    for (int i=0; i < N; ++i) {
        int value, k;
        is >> value >> k;
        if (value < 0)
            tree.delete_at(-value);
        else
            tree.add(value);
        os << tree.findKStatistic(k) << endl;
    }
}

int main() {
    run(cin, cout);
    return 0;
}