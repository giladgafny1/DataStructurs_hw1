#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <memory>

template<class T, class C>
class Node {
    C key;
    T data;
    std::shared_ptr<Node<T, C>> parent;
    std::shared_ptr<Node<T, C>> right;
    std::shared_ptr<Node<T, C>> left;
    int h;

public:
    Node(T data, C key) : key(key), data(data), parent(nullptr), right(nullptr), left(nullptr), h(0) {}

    Node() : key(key), data(data), parent(nullptr), right(nullptr), left(nullptr), h(0) {};

    Node(Node &node) = default;

    ~Node() = default;

    //good?
    Node &operator=(const Node &node) = default;


    void setKey(C key) {
        this->key = key;
    }

    C &getKey() {
        return this->key;
    }

    C *getKeyPtr() {
        return &(this->key);
    }

    void setData(T data) {
        this->data = data;
    }

    T &getData() {
        return this->data;
    }

    T *getDataPtr() {
        return &(this->data);
    }


    void setHeight(int h) {
        this->h = h;
    }

    int getHeight() {
        return this->h;
    }

    void setParent(std::shared_ptr<Node<T, C>> parent) {
        this->parent = parent;
    }

    std::shared_ptr<Node<T, C>> getParent() {
        return this->parent;
    }

    void setRight(std::shared_ptr<Node<T, C>> right) {
        this->right = right;
    }

    std::shared_ptr<Node<T, C>> getRight() {
        return this->right;
    }

    bool isLeaf() {
        return (this->hasLeft() == false && this->hasRight() == false);
    }

    void setLeft(std::shared_ptr<Node<T, C>> left) {
        this->left = left;
    }

    std::shared_ptr<Node<T, C>> getLeft() {
        return this->left;
    }

    bool hasParent() {
        if (this->parent == nullptr)
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

    bool isRight() {
        if (this->parent == nullptr)
            return false;
        if (this->parent->right == nullptr)
            return false;
        if (this->parent->right->key == this->key)
            return true;
        return false;
    }

    bool isLeft() {
        if (this->parent == nullptr)
            return false;
        if (this->parent->left == nullptr)
            return false;
        if (this->parent->left->key == this->key)
            return true;
        return false;
    }

    std::shared_ptr<Node<T, C>> HasOneSon() {
        if (this->right == nullptr && this->left != nullptr)
            return this->left;
        if (this->right != nullptr && this->left == nullptr)
            return this->right;
        return nullptr;
    }

    int getBF() {
        int h_r = -1, h_l = -1;
        if (this->left != nullptr)
            h_l = this->left->h;
        if (this->right != nullptr)
            h_r = this->right->h;
        return h_l - h_r;
    }

    void removeTies() {
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

};

static int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

template<class T, class C>
static int getNodeHeight(std::shared_ptr<Node<T, C>> node) {
    if (node == nullptr)
        return 0;
    return node->getHeight();
}

template<class T, class C>
static void setNodeHeight(std::shared_ptr<Node<T, C>> node) {
    if (node != nullptr) {
        if (node->isLeaf())
            node->setHeight(0);
        else
            node->setHeight(1 + max(getNodeHeight(node->getLeft()), getNodeHeight(node->getRight())));
    }
}

template<class T, class C>
class Avltree {
public:
    typedef std::shared_ptr<Node<T, C>> Node_ptr;
    Node_ptr root;
    //Node<T,C>* root;

    Avltree() : root(nullptr) {}

    ~Avltree();

    void deleteAvlNode(Node_ptr node);

    void deleteAvlNodeaux();

    int insert(Node_ptr node);

    void remove(std::shared_ptr<Node<T, C>> node_to_remove);

    std::shared_ptr<Node<T, C>> removebinary(std::shared_ptr<Node<T, C>> node);

    std::shared_ptr<Node<T, C>> getNextLeft(std::shared_ptr<Node<T, C>> node);

    void makeATree(Node_ptr datas [], int start, int end);
    Node_ptr buildATree(Node_ptr datas [], int start, int end);

    int inorder(Node_ptr root, Node_ptr order[], int count, int n);
    int preorder(Node_ptr root, Node_ptr order[], int count);

    int inorderKeys(Node_ptr root, C** order, int count);


    void preorder(Node<T, C> *root);

    //void postorder(Node<T, C> *root);

    void roll(Node_ptr node, int bf);

    void llRoll(Node_ptr node);

    void lrRoll(Node_ptr node);

    void rrRoll(Node_ptr node);

    void rlRoll(Node_ptr node);

    Node_ptr findKey(C key);

    Node_ptr getRoot();
};

// destructor - not sure if needed cause were using shared_ptr:

template<class T, class C>
Avltree<T, C>::~Avltree<T,C>()
{
    deleteAvlNodeaux();

}


template<class T, class C>
void Avltree<T, C>::deleteAvlNode(Node_ptr node)
{
    if (node!=nullptr)
    {
        deleteAvlNode(node->getLeft());
        deleteAvlNode(node->getRight());
        if(node->getParent()!= nullptr)
        {
            if(node->isLeft())
                node->getParent()->getLeft().reset();
            else
                node->getParent()->getRight().reset();
        }
        node.reset();
    }
}

template<class T, class C>
void Avltree<T, C>::deleteAvlNodeaux() {

}


template<class T, class C>
std::shared_ptr<Node<T, C>> Avltree<T, C>::getRoot() {
    return root;
}

template<class T, class C>
std::shared_ptr<Node<T, C>> Avltree<T, C>::findKey(C key) {
    if (root == nullptr)
        return nullptr;
    std::shared_ptr<Node<T, C>> iterator = root;
    while (iterator != nullptr) {
        if (iterator->getKey() == key)
            return iterator;
        if (iterator->getKey() < key) {
            iterator = iterator->getRight();
            continue;
        }
        if (iterator->getKey() > key) {
            iterator = iterator->getLeft();
        }
    }
    return nullptr;
}

template<class T, class C>
int Avltree<T, C>::insert(std::shared_ptr<Node<T, C>> node) {
    if (root == nullptr) {
        root = node;
        return 1;
    }
    C key = node->getKey();
    if (this->findKey(node->getKey()) != nullptr)
        return -1;
    std::shared_ptr<Node<T, C>> iterator = root;
    while (iterator != nullptr) {
        if (iterator->getKey() < key) {
            if (!(iterator->hasRight()))
                break;
            iterator = iterator->getRight();
            continue;
        }
        if (iterator->getKey() > key) {
            if (!iterator->hasLeft())
                break;
            iterator = iterator->getLeft();
        }
    }
    if (iterator->getKey() > key)
        iterator->setLeft(node);
    else
        iterator->setRight(node);
    node->setParent(iterator);
    node->setHeight(0);
    iterator = node;
    //balancing:
    while (iterator != root) {
        std::shared_ptr<Node<T, C>> p = iterator->getParent();
        int it_height = iterator->getHeight();
        int p_height = p->getHeight();
        if (p_height >= it_height + 1)
            return 1;
        p->setHeight(it_height + 1);
        if (p->getBF() >= 2 || p->getBF() <= -2) {
            roll(p, p->getBF());
            return 1;
        }
        iterator = p;

    }
    return 1;
}

template<class T, class C>
void Avltree<T, C>::roll(std::shared_ptr<Node<T, C>> node, int bf) {
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
        if (node->getRight()->getBF() == 1) {
            rlRoll(node);
            return;
        }
    }
}

template<class T, class C>
void Avltree<T, C>::llRoll(std::shared_ptr<Node<T, C>> node) {
    std::shared_ptr<Node<T, C>> temp = node->getLeft();
    node->setLeft(temp->getRight());
    if(temp->getRight()!= nullptr)
    {
        temp->getRight()->setParent(node);
    }
    temp->setRight(node);
    //you need, right?
    if (node->hasParent()) {
        if (node->isLeft())
            node->getParent()->setLeft(temp);
        if (node->isRight())
            node->getParent()->setRight(temp);
    } else
        root = temp;
    temp->setParent(node->getParent());
    node->setParent(temp);
    //updating heights:
    setNodeHeight(node);
    setNodeHeight(temp);
}

template<class T, class C>
void Avltree<T, C>::lrRoll(std::shared_ptr<Node<T, C>> node) {
    std::shared_ptr<Node<T, C>> temp1 = node->getLeft();
    std::shared_ptr<Node<T, C>> temp2 = node->getLeft()->getRight();
    node->setLeft(temp2->getRight());
    if (temp2->getRight() != nullptr)
        temp2->getRight()->setParent(node);
    temp1->setRight(temp2->getLeft());
    if (temp2->getLeft() != nullptr)
        temp2->getLeft()->setParent(temp1);
    temp2->setLeft(temp1);
    temp1->setParent(temp2);
    temp2->setRight(node);
    if (node->getKey() == root->getKey()) {
        root = temp2;
        temp2->setParent(nullptr);
    } else {
        temp2->setParent(node->getParent());
        if (node->isRight())
            node->getParent()->setRight(temp2);
        else
            node->getParent()->setLeft(temp2);
    }
    node->setParent(temp2);
    //updating heights:
    setNodeHeight(node);
    setNodeHeight(temp1);
    setNodeHeight(temp2);

}

template<class T, class C>
void Avltree<T, C>::rrRoll(std::shared_ptr<Node<T, C>> node) {
    //need to test
    std::shared_ptr<Node<T, C>> temp = node->getRight();
    node->setRight(temp->getLeft());
    if(temp->getLeft()!= nullptr)
    {
        temp->getLeft()->setParent(node);
    }
    if (node->hasParent()) {
        if (node->isLeft())
            node->getParent()->setLeft(temp);
        if (node->isRight())
            node->getParent()->setRight(temp);
    } else
        root = temp;
    temp->setLeft(node);
    temp->setParent(node->getParent());
    node->setParent(temp);
    //updating heights:
    if (node->isLeaf())
        node->setHeight(0);
    else
        node->setHeight(1 + max(getNodeHeight(node->getLeft()), getNodeHeight(node->getLeft())));
    temp->setHeight(1 + max(getNodeHeight(temp->getLeft()), getNodeHeight(temp->getRight())));
}

template<class T, class C>
void Avltree<T, C>::rlRoll(std::shared_ptr<Node<T, C>> node) {
    //need to test
    std::shared_ptr<Node<T, C>> temp1 = node->getRight();
    std::shared_ptr<Node<T, C>> temp2 = node->getRight()->getLeft();
    node->setRight(temp2->getLeft());
    if (temp2->getLeft() != nullptr)
        temp2->getLeft()->setParent(node);
    temp1->setLeft(temp2->getRight());
    if (temp2->getRight() != nullptr)
        temp2->getRight()->setParent(temp1);
    temp2->setRight(temp1);
    temp1->setParent(temp2);
    temp2->setLeft(node);
    if (node->getKey() == root->getKey()) {
        root = temp2;
        temp2->setParent(nullptr);
    } else {
        temp2->setParent(node->getParent());
        if (node->isRight())
            node->getParent()->setRight(temp2);
        else
            node->getParent()->setLeft(temp2);
    }
    node->setParent(temp2);

    //updating heights:
    setNodeHeight(node);
    setNodeHeight(temp1);
    setNodeHeight(temp2);
}

template<class T, class C>
int Avltree<T, C>::inorder(std::shared_ptr<Node<T, C>> root, std::shared_ptr<Node<T, C>>* order, int count, int n) {
    if (!root || count==n) {
        return 0;
    }
    int tmp;
    tmp = this->inorder(root->getLeft(), order, count,n);
    if (tmp != 0)
        count = tmp;
    order[count] = root;
    count++;
    if(count!= n){
        tmp = this->inorder(root->getRight(), order, count,n);
        if (tmp != 0)
            count = tmp;
    }
    return count;
}

template<class T, class C>
int Avltree<T, C>::preorder(Node_ptr root, Node_ptr *order, int count) {
    if (!root) {
        return 0;
    }
    int tmp;
    tmp = this->preorder(root->getLeft(), order, count);
    if (tmp != 0)
        count = tmp;
    tmp = this->preorder(root->getRight(), order, count);
    if (tmp != 0)
        count = tmp;
    order[count] = root;
    count++;
    return count;
}

template<class T, class C>
int Avltree<T, C>::inorderKeys(std::shared_ptr<Node<T, C>> root, C** order, int count) {
    if (!root) {
        return 0;
    }
    int tmp;
    tmp = this->inorderKeys(root->getLeft(), order, count);
    if (tmp != 0)
        count = tmp;
    order[count] = root->getKeyPtr();
    count++;
    tmp = this->inorderKeys(root->getRight(), order, count);
    if (tmp != 0)
        count = tmp;
    return count;
}

template<class T, class C>
std::shared_ptr<Node<T, C>> Avltree<T, C>::removebinary(std::shared_ptr<Node<T, C>> node) {
    //added the removeTies where i thought was needed;
    if(node== nullptr){
        return nullptr;
    }
    if (node->isLeaf()) {
        if (root->getKey() == node->getKey()) {
            node->removeTies();
            root = nullptr;
            return nullptr;
        }
        if (node->isRight()) {
            node->getParent()->setRight(nullptr);
        } else {
            node->getParent()->setLeft(nullptr);
        }
        std::shared_ptr<Node<T, C>> parent = node->getParent();
        node->removeTies();
        setNodeHeight(node);
        setNodeHeight(parent);
        return parent;
    }
    if (node->HasOneSon() != nullptr) {
        //G added a case if root
        if (root->getKey() == node->getKey()) {
            root = node->HasOneSon();
            node->HasOneSon()->setParent(nullptr);
            node->removeTies();
            setNodeHeight(node);
            return nullptr;
        }
        if (node->isLeft()) {
            node->getParent()->setLeft(node->HasOneSon());
            node->HasOneSon()->setParent(node->getParent());
        } else{
            node->getParent()->setRight(node->HasOneSon());
            node->HasOneSon()->setParent(node->getParent());
        }
        std::shared_ptr<Node<T, C>> parent = node->getParent();
        node->removeTies();
        setNodeHeight(node);
        setNodeHeight(parent);
        return parent;
    }
    std::shared_ptr<Node<T, C>> new_root = getNextLeft(node);
    std::shared_ptr<Node<T, C>> new_right_son;
    std::shared_ptr<Node<T, C>> new_parent = node->getParent();
    std::shared_ptr<Node<T, C>> new_grandson = new_root->getRight();


    if (!(new_root->getParent()->getKey() == node->getKey())) {
        new_right_son = node->getRight();
    } else {
        new_right_son = new_root->getRight();
    }
    if (new_right_son != nullptr){
        if(new_grandson!= nullptr &&(!(new_right_son->getKey()==new_grandson->getKey()))) {
            new_right_son->setParent(new_root);
            new_right_son->setLeft(new_grandson);
        }
        if(new_grandson== nullptr)
        {
            new_right_son->setParent(new_root);
            new_right_son->setLeft(new_grandson);
        } else
        {
            new_right_son->setParent(new_root);
        }
    }
    new_root->setParent(new_parent);
    new_root->setLeft(node->getLeft());
    new_root->setRight(new_right_son);
    node->getLeft()->setParent(new_root);

    if (new_parent != nullptr) {
        if (node->isRight())
            new_parent->setRight(new_root);
        else
            new_parent->setLeft(new_root);
    }
    if(node->getKey()== root->getKey())
    {
        root=new_root;
    }
    setNodeHeight(new_grandson);
    setNodeHeight(new_right_son);
    setNodeHeight(new_root);
    setNodeHeight(new_parent);
    if (new_right_son != nullptr) {
        node->removeTies();
        return new_right_son;
    }
    node->removeTies();
    return new_root;
}

template<class T, class C>
void Avltree<T, C>::remove(std::shared_ptr<Node<T, C>> node_to_remove) {
    std::shared_ptr<Node<T, C>> node = removebinary(node_to_remove);
    // int height=node->getHeight();
    if (node != nullptr) {
        roll(node, node->getBF());
        while (node->getParent() != nullptr) {
            node = node->getParent();
            // height=node->getHeight();
            roll(node, node->getBF());
        }
    }

}

template<class T, class C>
std::shared_ptr<Node<T, C>> Avltree<T, C>::getNextLeft(std::shared_ptr<Node<T, C>> node) {
    std::shared_ptr<Node<T, C>> node_next = node->getRight();
    while (node_next->hasLeft()) {
        node_next = node_next->getLeft();
    }
    return node_next;
}

template<class T, class C>
void Avltree<T, C>::makeATree(Node_ptr *datas, int start, int end)  {
    root= buildATree(datas,start,end);
    setNodeHeight(root);
}
template<class T,class C>
std::shared_ptr<Node<T, C>> Avltree<T, C>::buildATree(std::shared_ptr<Node<T, C>> *datas, int start, int end) {
    if(start>end)
        return nullptr;
    int mid=(end+start)/2;
    std::shared_ptr<Node<T, C>> Node_r=datas[mid];
    Node_r->setLeft(buildATree(datas,start, mid-1));
    Node_r->setRight(buildATree(datas,mid+1,end));
    if(Node_r->getRight()!= nullptr)
        Node_r->getRight()->setParent(Node_r);
    if(Node_r->getLeft()!= nullptr)
        Node_r->getLeft()->setParent(Node_r);
    setNodeHeight(Node_r);
    return Node_r;
}


#endif