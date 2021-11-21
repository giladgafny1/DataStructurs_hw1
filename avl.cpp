
template <class T>
class Node
{
    int key;
    T data;
    Node<T>* right;
    Node<T>* left;

public:
    Node(int key, T data): key(key), data(data), right(nullptr), left(nullptr) {}
    ~Node() = default;
    


};

