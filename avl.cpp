
template <class T>
class Node {
    int key;
    T data;
    Node<T> *right;
    Node<T> *left;

public:
    Node(int key, T data) : key(key), data(data), right(nullptr), left(nullptr) {}

    ~Node() = default;

    void setKey(int key)
    {
        this->key=key;
    }

    int getKey()
    {
        return this->key;
    }

    void setData(T data) {
        this->data = data;
    }

    T getData() {
        return this->data;
    }

    void setRight(Node<T> *right) {
        this->right = right;
    }

    Node<T> *getRight() {
        return this->right;
    }

    void setLeft(Node<T> *right) {
        this->left = left;
    }

    Node<T> *getLeft() {
        return this->left;
    }

    bool hasRight() {
        if (this->right == nullptr)
            return false;
        return true;
    }

    bool hasLeft() {
        if (this->left == nullptr)
            return false;
        return true;
    }
};

template <class T>
class Avltree {
    Node<T>* root;

    void insert(Node<T>)
    void inorder(Node<T> root);
    void preorder(Node<T> root);
    void postorder(Node<T> root);
};

