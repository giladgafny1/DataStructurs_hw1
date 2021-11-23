#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <memory>

template <class T, class C>
class Node {
    C key;
    T data;
    Node<T,C> *parent;
    Node<T,C> *right;
    Node<T,C> *left;
    int h;

public:
    Node(T data, C key) : key(key), data(data), parent(nullptr), right(nullptr), left(nullptr), h(0) {}
    Node(Node &node) = default;

    ~Node() = default;

    //good?
    Node &operator=(const Node &node) = default;

    void setKey(C key)
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

    void setParent(Node<T,C> *parent) {
        this->parent = parent;
    }

    Node<T, C> *getParent() {
        return this->parent;
    }

    void setRight(Node<T, C> *right) {
        this->right = right;
    }

    Node<T, C> *getRight() {
        return this->right;
    }

    void setLeft(Node<T, C> *left) {
        this->left = left;
    }

    Node<T, C> *getLeft() {
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

template <class T,class C>
class Avltree {
public:
    std::shared_ptr<Node<T, C>> root;

    Avltree(): root(nullptr){}


    int insert(Node<T, C>* node);

    void remove(Node<T, C>* node);
    int inorder(Node<T, C> *root, T *order, int count);
    void preorder(Node<T, C>* root);

    void postorder(Node<T, C>* root);
    void roll(Node<T, C>* node, int bf);
    void llRoll(Node<T, C>* node);
    void lrRoll(Node<T, C>* node);
    void rrRoll(Node<T, C>* node);
    void rlRoll(Node<T, C>* node);
    Node<T, C>* findKey(C key);
    Node<T, C>* getRoot();




};

template<class T ,class C>
Node<T, C>* Avltree<T,C>::getRoot()
{
    return root;
}

template<class T ,class C>
Node<T, C>* Avltree<T,C>::findKey(C key)
{
    Node<T, C>* iterator = root;
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

template<class T ,class C>
int Avltree<T,C>::insert(Node<T, C>* node){
    if (root == nullptr)
    {
        root = node;
        return 1;
    }
    C key = node->getKey();
    if (this->findKey(node->getKey()) != nullptr)
        return -1;
    Node<T, C>* iterator = root;
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
        Node<T, C>* p = iterator->getParent();
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

template<class T ,class C>
void Avltree<T,C>::roll(Node<T, C>* node, int bf) {
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

template<class T ,class C>
void Avltree<T,C>::llRoll(Node<T, C>* node)
{
    Node<T, C>* temp = node->getLeft();
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

template<class T ,class C>
void Avltree<T,C>::lrRoll(Node<T, C>* node)
{
    Node<T, C>* temp1 = node->getLeft();
    Node<T, C>* temp2 = node->getLeft()->getRight();
    node->setLeft(temp2->getRight());
    temp2->getRight()->setParent(node);
    temp1->setRight(temp2->getLeft());
    temp2->getLeft()->setParent(temp1);
    temp2->setLeft(temp1);
    temp1->setParent(temp2);
    temp2->setRight(node);
    if(node->getKey()==root->getKey())
    {
        root = temp2;
    }
    node->setParent(temp1);


}
template<class T ,class C>
void Avltree<T,C>::rrRoll(Node<T, C>* node)
{
    //need to test
    Node<T, C>* temp = node->getRight();
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

template<class T ,class C>
void Avltree<T,C>::rlRoll(Node<T, C>* node)
{
    //need to test
    Node<T, C>* temp1 = node->getRight();
    Node<T, C>* temp2 = node->getRight()->getLeft();
    node->setRight(temp2->getLeft());
    temp2->getLeft()->setParent(node);
    temp1->setLeft(temp2->getRight());
    temp2->getRight()->setParent(temp1);
    temp2->setRight(temp1);
    temp1->setParent(temp2);
    temp2->setLeft(node);
    if(node->getKey()==root->getKey())
    {
        root = temp2;
    }
    node->setParent(temp1);
}

template<class T ,class C>
int Avltree<T,C>::inorder(Node<T, C> *root, T *order, int count) {
    if(!root){
        return 0;
    }
    int tmp;
    tmp = this->inorder(root->getLeft(),order,count);
    if(tmp!=0)
        count=tmp;
    order[count]=root->getData();
    count++;
    tmp = this->inorder(root->getRight(),order,count);
    if(tmp!=0)
        count=tmp;
    return count;
}

#endif