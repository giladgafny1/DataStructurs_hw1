template <class T>
class Node {
    int key;
    T data;
    Node<T> *parent;
    Node<T> *right;
    Node<T> *left;
    int h;

public:
    Node(int key, T data) : key(key), data(data), parent(nullptr), right(nullptr), left(nullptr), h(0) {}
    Node(Node &node) = default;

    ~Node() = default;

    //good?
    Node &operator=(const Node &node) = default;

    //good?
    bool &operator == (Node const &node)
    {
        if (node->key==this->key)
            return true;
        return false;
    }

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

    void setHeight(int h) {
        this->h = h;
    }

    T getHeight() {
        return this->h;
    }

    void setParent(Node<T> *parent) {
        this->parent = parent;
    }

    Node<T> *getParent() {
        return this->parent;
    }

    void setRight(Node<T> *right) {
        this->right = right;
    }

    Node<T> *getRight() {
        return this->right;
    }

    void setLeft(Node<T> *left) {
        this->left = left;
    }

    Node<T> *getLeft() {
        return this->left;
    }
    bool hasParent()
    {
        if(this->parent==nullptr)
            return false;
        return true;
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

    bool isRight()
    {
        if(this->parent->right->key==this->key)
            return true;
        return false;
    }
    bool isLeft()
    {
        if(this->parent->left->key==this->key)
            return true;
        return false;
    }
    int getBF()
    {
        int h_r = -1, h_l = -1;
        if (this->left!= nullptr)
            h_l = this->left->h;
        if (this->right!= nullptr)
            h_r = this->right->h;
        return h_l-h_r;
    }
};

template <class T>
class Avltree {
public:
    Node<T>* root;

    Avltree(): root(nullptr){}

    int insert(Node<T>* node);
    void remove(Node<T>* node);
    void inorder(Node<T>* root);
    void preorder(Node<T>* root);
    void postorder(Node<T>* root);

    void roll(Node<T>* node, int bf);
    void llRoll(Node<T>* node);
    void lrRoll(Node<T>* node);
    void rrRoll(Node<T>* node);
    void rlRoll(Node<T>* node);
    Node<T>* findKey(int key);


};

template<class T>
Node<T>* Avltree<T>::findKey(int key)
{
    Node<T>* iterator = root;
    while (iterator!=nullptr)
    {
        if (iterator->getKey()==key)
            return iterator;
        if (iterator->getKey()<key)
        {
            iterator=iterator->getRight();
            continue;
        }
        if (iterator->getKey()>key)
        {
            iterator=iterator->getLeft();
        }
    }
    return nullptr;
}

template<class T>
int Avltree<T>::insert(Node<T>* node){
    if (root == nullptr)
    {
        root = node;
        return 1;
    }
    int key = node->getKey();
    if (this->findKey(node->getKey()) != nullptr)
        return -1;
    Node<T>* iterator = root;
    while (iterator!=nullptr)
    {
        if (iterator->getKey()<key)
        {
            if (!(iterator->hasRight()))
                break;
            iterator=iterator->getRight();
            continue;
        }
        if (iterator->getKey()>key)
        {
            if(!iterator->hasLeft())
                break;
            iterator=iterator->getLeft();
        }
    }
    if (iterator->getKey()>key)
        iterator->setLeft(node);
    else
        iterator->setRight(node);
    node->setParent(iterator);
    node->setHeight(0);
    iterator = node;
    //balancing:
    while (iterator!=root)
    {
        Node<T>* p = iterator->getParent();
        int it_height = iterator->getHeight();
        int p_height = p->getHeight();
        if (p_height>=it_height+1)
            return 1;
        p->setHeight(it_height+1);
        if (p->getBF()>=2 || p->getBF()<=-2)
        {
            roll(p, p->getBF());
            return 1;
        }
        iterator = p;

    }
    return 1;
}

template<class T>
void Avltree<T>::roll(Node<T>* node, int bf) {
    if (bf == 2 && node->hasLeft()) {
        if (node->getLeft()->getBF() >= 0) {
            llRoll(node);
            return;
        }
        if (node->getLeft()->getBF() == -1) {
            lrRoll(node);
            return;
        }
    }
    if (bf == -2 && node->hasRight()) {
        if (node->getRight()->getBF() <= 0) {
            rrRoll(node);
            return;
        }
        if (node->getLeft()->getBF() == 1) {
            rlRoll(node);
            return;
        }
    }
}

template<class T>
void Avltree<T>::llRoll(Node<T>* node)
{
    Node<T>* temp = node->getLeft();
    node->setLeft(temp->getRight());
    temp->setRight(node);
    //you need, right?
    if(node->hasParent())
    {
        if(node->isLeft())
            node->getParent()->setLeft(temp);
        if(node->isRight())
            node->getParent()->setRight(temp);
    }
    node->setParent(temp);

}

template<class T>
void Avltree<T>::lrRoll(Node<T>* node)
{
    Node<T>* temp1 = node->getLeft();
    Node<T>* temp2 = node->getLeft()->getRight();
    node->setLeft(temp2->getRight());
    temp2->getRight()->setParent(node);
    temp1->setRight(temp2->getLeft());
    temp2->getLeft()->setParent(temp1);
    temp2->setLeft(temp1);
    temp1->setParent(temp2);
    temp2->setRight(node);
    if(node==root)
    {
        root = temp2;
    }
    node->setParent(temp1);


}
template<class T>
void Avltree<T>::rrRoll(Node<T>* node)
{
    //need to test
    Node<T>* temp = node->getRight();
    node->setRight(temp->getLeft());
    if(node->hasParent())
    {
        if(node->isLeft())
            node->getParent()->setLeft(temp);
        if(node->isRight())
            node->getParent()->setRight(temp);
    }
    temp->setLeft(node);
    node->setParent(temp);
}

template<class T>
void Avltree<T>::rlRoll(Node<T>* node)
{
    //need to test
    Node<T>* temp1 = node->getRight();
    Node<T>* temp2 = node->getRight()->getLeft();
    node->setRight(temp2->getLeft());
    temp2->getLeft()->setParent(node);
    temp1->setLeft(temp2->getRight());
    temp2->getRight()->setParent(temp1);
    temp2->setRight(temp1);
    temp1->setParent(temp2);
    temp2->setLeft(node);
    if(node==root)
    {
        root = temp2;
    }
    node->setParent(temp1);
}