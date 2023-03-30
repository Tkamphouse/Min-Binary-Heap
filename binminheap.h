    //---------------------------------------------------------------------------
    // NAME: Tyler Kamphouse
    // DATE: Fall 2021
    // DESC: Extra Credit Binary Min Heap, super cool, super fun :)
    //---------------------------------------------------------------------------

    #ifndef MINHEAP_H
    #define MINHEAP_H

    #include "map.h"
    #include "arrayseq.h"
    #include <math.h>

    template<typename K, typename V>
    class MinHeap 
    {
    public:

    // default constructor
    MinHeap();

    // copy constructor
    MinHeap(const MinHeap& rhs);

    // move constructor
    MinHeap(MinHeap&& rhs);

    // copy assignment
    MinHeap& operator=(const MinHeap& rhs);

    // move assignment
    MinHeap& operator=(MinHeap&& rhs);  

    // destructor
    ~MinHeap();
    
    // Returns the number of key-value pairs in the map
    int size() const;

    // Tests if the map is empty
    bool empty() const;

    // Extends the collection by adding the given key-value
    // pair. Assumes the key being added is not present in the
    // collection. Insert does not check if the key is present.
    void insert(const K& key, const V& value);

    // find_min
    K find_min() const;

    // remove_min
    void remove_min();

    // Heap Sort
    ArraySeq<K> heap_sort() const;

    // helper to print the tree for debugging
    void print() const;


    private:

    // node for avl tree
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
    };

    // number of nodes
    int count = 0;

    // root node
    Node* root = nullptr;

    // clean up the tree and reset count to zero given subtree root
    void make_empty(Node* st_root);

    // copy assignment helper
    Node* copy(const Node* rhs_st_root) const;

    // print helper
    void print(std::string indent, const Node* st_root) const;

    // last node helper
    Node* last_insert(int n, Node* st_root, K& key, V& value);

    // last node helper
    Node* last_erase(int n, Node* st_root);
    
    };


    template<typename K, typename V>
    void MinHeap<K,V>::print() const
    {
        print(std::string(""), root);
    }


    template<typename K, typename V>
    void MinHeap<K,V>::print(std::string indent, const Node* st_root) const
    {
        if (!st_root)
            return;
        std::cout << st_root->key <<  std::endl;
        if (st_root->left) {
            std::cout << indent << " lft: ";
            print(indent + " ", st_root->left);
        }
        if (st_root->right) {
            std::cout << indent << " rgt: ";
            print(indent + " ", st_root->right);
        }
    }


    //----------------------------------------------------------------------
    // TODO: Implement the above functions below
    //----------------------------------------------------------------------

    template<typename K, typename V>
    MinHeap<K,V>::MinHeap()
    {

    }

    // copy constructor
    template<typename K, typename V>
    MinHeap<K,V>::MinHeap(const MinHeap& rhs)
    {
        *this = rhs;
    }

    // move constructor
    template<typename K, typename V>
    MinHeap<K,V>::MinHeap(MinHeap&& rhs)
    {
        *this = std::move(rhs);
    }

    // copy assignment
    template<typename K, typename V>
    MinHeap<K,V>& MinHeap<K,V>::operator=(const MinHeap& rhs)
    {
        if(this != &rhs) 
        {
            make_empty(root);
            root = copy(rhs.root);
            count = rhs.count;
        }
        return *this;
    }

    // move assignment
    template<typename K, typename V>
    MinHeap<K,V>& MinHeap<K,V>::operator=(MinHeap&& rhs)
    {
        if(this != &rhs) 
        {
            make_empty(root);
            root = rhs.root;
            rhs.root = nullptr;
            count = rhs.count;
            rhs.count = 0;
        }
        return *this;
    }

    // destructor
    template<typename K, typename V>
    MinHeap<K,V>::~MinHeap()
    {
        make_empty(root);
    }
    
    // Returns the number of key-value pairs in the map
    template<typename K, typename V>
    int MinHeap<K,V>::size() const
    {
        return count;
    }

    // Tests if the map is empty
    template<typename K, typename V>
    bool MinHeap<K,V>::empty() const
    {
        if (size() == 0)
            return true;
        else    
            return false;
    }

    // Extends the collection by adding the given key-value
    // pair. Assumes the key being added is not present in the
    // collection. Insert does not check if the key is present.
    template<typename K, typename V>
    void MinHeap<K,V>::insert(const K& key, const V& value)
    {   
        Node* insertion = new Node;
        insertion->left = nullptr;
        insertion->right = nullptr;
        insertion->key = key;
        insertion->value = value;
        if (empty())
        {
            root = insertion;
            ++count;
        }
        else
        {
            ++count;
            Node* st_root = last_insert(count, root, insertion->key, insertion->value);
            if (st_root->key > insertion->key)
            {
                K tmp_k = st_root->key;
                V tmp_v = st_root->value;
                st_root->key = insertion->key;
                st_root->value = insertion->value;
                insertion->key = tmp_k;
                insertion->value = tmp_v;
            }
            if (!st_root->left)
                st_root->left = insertion;
            else 
                st_root->right = insertion;
        }
    }

    // finds min
    template<typename K, typename V>
    K MinHeap<K,V>::find_min() const
    {
        if (empty())
            throw std::out_of_range("MinHeap<K,V>::find_min()");
        else
            return root->key;
    }

    // finds min
    template<typename K, typename V>
    void MinHeap<K,V>::remove_min()
    {
        if (empty())
            throw std::out_of_range("MinHeap<K,V>::remove_min()");
        else if (count == 1)
            root = nullptr;
        else if (count == 2)
        {
            root->key = root->left->key;
            root->value = root->left->value;
            root->left = nullptr;
        }
        else if (count == 3)
        {
            if (root->left->key < root->right->key)
            {
                root->key = root->left->key;
                root->value = root->left->value;
                root->left = root->right;
                root->right = nullptr;
            }
            else
            {
                root->key = root->right->key;
                root->value = root->right->value;
                root->right = nullptr;
            }
        }
        else if (count > 3)
        {
            //return node above last
            Node* last = new Node;
            if (!last_erase(count, root)->right)
            {
                last = last_erase(count, root)->left;
                root->key = last->key;
                root->value = last->value;
                last_erase(count, root)->left = nullptr;
            }
            else 
            {
                last = last_erase(count, root)->right;
                root->key = last->key;
                root->value = last->value;
                last_erase(count, root)->right = nullptr;
            }
            //trickle down
            Node* cur = root;
            while (cur->left and cur->right)
            {
                if (cur->left->key < cur->right->key)
                {
                    if (cur->left->key < cur->key)
                    {
                        K tmp_k = cur->key;
                        V tmp_v = cur->value;
                        cur->key = cur->left->key;
                        cur->value = cur->left->value;
                        cur->left->key = tmp_k;
                        cur->left->value = tmp_v;
                    }
                    cur = cur->left;
                }
                else
                {
                    if (cur->right->key < cur->key)
                    {
                        K tmp_k = cur->key;
                        V tmp_v = cur->value;
                        cur->key = cur->right->key;
                        cur->value = cur->right->value;
                        cur->right->key = tmp_k;
                        cur->right->value = tmp_v;
                    }
                    cur = cur->right;
                }
            }
        }
        --count;
    }

    // clean up the tree and reset count to zero given subtree root
    template<typename K, typename V>
    void MinHeap<K,V>::make_empty(Node* st_root)
    {
        if(st_root != nullptr)
        {
            make_empty(st_root->left);
            make_empty(st_root->right);
            delete (st_root);
            st_root = nullptr;
            count = 0;
        }
    }

    template<typename K, typename V>
    ArraySeq<K> MinHeap<K,V>::heap_sort() const
    {
        ArraySeq<K> keys;
        MinHeap<K,V> tmp = *this;
        for (int i = 0; i < size(); ++i)
        {
            keys.insert(tmp.find_min(), keys.size());
            tmp.remove_min();
        }
        return keys;
    }

    // copy assignment helper
    template<typename K, typename V>
    typename MinHeap<K,V>::Node* MinHeap<K,V>::copy(const Node* st_root) const
    {
        if(st_root == nullptr) 
            return nullptr;
        Node* tmp = new Node;
        tmp->key = st_root->key;
        tmp->value = st_root->value;
        tmp->right = copy(st_root->right);
        tmp->left = copy(st_root->left);
        return tmp;
    }

    // Last Node of complete Tree finder
    template<typename K, typename V>
    typename MinHeap<K,V>::Node* MinHeap<K,V>::last_insert(int n, Node* st_root, K& key, V& value)
    {
        if (st_root->key > key)
        {
            K tmp_k = st_root->key;
            V tmp_v = st_root->value;
            st_root->key = key;
            st_root->value = value;
            key = tmp_k;
            value = tmp_v;
        }
        if (!st_root->right or !st_root->left)
            return st_root;
        int h = ceil(log2(n + 1));
        int unfilled = (pow(2, h) - 1) - (n);
        int leaf_max = pow(2, h - 1);
        int leaf_filled = leaf_max - unfilled;
        if ((leaf_max / 2) >= leaf_filled)
            return last_insert(n - pow(2, h - 2), st_root->left, key, value);
        else
            return last_insert(n - pow(2, h - 1), st_root->right, key, value);
    }

    // Last Node of complete Tree finder
    template<typename K, typename V>
    typename MinHeap<K,V>::Node* MinHeap<K,V>::last_erase(int n, Node* st_root)
    {
        if (st_root->left and !st_root->right)
            return st_root;
        if (st_root->left and st_root->right and !st_root->left->left)
            return st_root;
        int h = ceil(log2(n + 1));
        int unfilled = (pow(2, h) - 1) - (n);
        int leaf_max = pow(2, h - 1);
        int leaf_filled = leaf_max - unfilled;
        if ((leaf_max / 2) >= leaf_filled)
            return last_erase(n - pow(2, h - 2), st_root->left);
        else
            return last_erase(n - pow(2, h - 1), st_root->right);
    }

    #endif
    
