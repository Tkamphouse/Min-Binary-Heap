    //---------------------------------------------------------------------------
    // NAME: Tyler Kamphouse
    // DATE: Fall 2021
    // DESC: AVL Tree! Let's GO!
    //---------------------------------------------------------------------------

    #ifndef AVLMAP_H
    #define AVLMAP_H

    #include "map.h"
    #include "arrayseq.h"


    template<typename K, typename V>
    class AVLMap : public Map<K,V>
    {
    public:

    // default constructor
    AVLMap();

    // copy constructor
    AVLMap(const AVLMap& rhs);

    // move constructor
    AVLMap(AVLMap&& rhs);

    // copy assignment
    AVLMap& operator=(const AVLMap& rhs);

    // move assignment
    AVLMap& operator=(AVLMap&& rhs);  

    // destructor
    ~AVLMap();
    
    // Returns the number of key-value pairs in the map
    int size() const;

    // Tests if the map is empty
    bool empty() const;

    // Allows values associated with a key to be updated. Throws
    // out_of_range if the given key is not in the collection.
    V& operator[](const K& key);

    // Returns the value for a given key. Throws out_of_range if the
    // given key is not in the collection. 
    const V& operator[](const K& key) const;

    // Extends the collection by adding the given key-value
    // pair. Assumes the key being added is not present in the
    // collection. Insert does not check if the key is present.
    void insert(const K& key, const V& value);

    // Shrinks the collection by removing the key-value pair with the
    // given key. Does not modify the collection if the collection does
    // not contain the key. Throws out_of_range if the given key is not
    // in the collection.
    void erase(const K& key);

    // Returns true if the key is in the collection, and false otherwise.
    bool contains(const K& key) const;

    // Returns the keys k in the collection such that k1 <= k <= k2
    ArraySeq<K> find_keys(const K& k1, const K& k2) const;

    // Returns the keys in the collection in ascending sorted order
    ArraySeq<K> sorted_keys() const;  

    // Returns the height of the binary search tree
    int height() const;

    // helper to print the tree for debugging
    void print() const;
    
    private:

    // node for avl tree
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        int height;
    };

    // number of nodes
    int count = 0;

    // root node
    Node* root = nullptr;

    // clean up the tree and reset count to zero given subtree root
    void make_empty(Node* st_root);

    // copy assignment helper
    Node* copy(const Node* rhs_st_root) const;
    
    // erase helper
    Node* erase(const K& key, Node* st_root);

    // insert helper
    Node* insert(const K& key, const V& value, Node* st_root);
    
    // find_keys helper
    void find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const;

    // sorted_keys helper
    void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

    // rotations
    Node* right_rotate(Node* k2);
    Node* left_rotate(Node* k2);
    
    // rebalance
    Node* rebalance(Node* st_root);

    // print helper
    void print(std::string indent, const Node* st_root) const;
    
    };


    template<typename K, typename V>
    void AVLMap<K,V>::print() const
    {
        print(std::string(""), root);
    }


    template<typename K, typename V>
    void AVLMap<K,V>::print(std::string indent, const Node* st_root) const
    {
        if (!st_root)
            return;
        std::cout << st_root->key << " (" << st_root->height << ")" <<  std::endl;
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
    AVLMap<K,V>::AVLMap()
    {

    }

    // copy constructor
    template<typename K, typename V>
    AVLMap<K,V>::AVLMap(const AVLMap& rhs)
    {
        *this = rhs;
    }

    // move constructor
    template<typename K, typename V>
    AVLMap<K,V>::AVLMap(AVLMap&& rhs)
    {
        *this = std::move(rhs);
    }

    // copy assignment
    template<typename K, typename V>
    AVLMap<K,V>& AVLMap<K,V>::operator=(const AVLMap& rhs)
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
    AVLMap<K,V>& AVLMap<K,V>::operator=(AVLMap&& rhs)
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
    AVLMap<K,V>::~AVLMap()
    {
        make_empty(root);
    }
    
    // Returns the number of key-value pairs in the map
    template<typename K, typename V>
    int AVLMap<K,V>::size() const
    {
        return count;
    }

    // Tests if the map is empty
    template<typename K, typename V>
    bool AVLMap<K,V>::empty() const
    {
        if (size() == 0)
            return true;
        else    
            return false;
    }

    // Allows values associated with a key to be updated. Throws
    // out_of_range if the given key is not in the collection.
    template<typename K, typename V>
    V& AVLMap<K,V>::operator[](const K& key)
    {
        if (empty())
            throw std::out_of_range("BSTMap<K,V>::operator[](const K& key) const");
        else
        {
            Node* cur = root;
            while (1)
            {
                if (key == cur->key)
                    return cur->value;
                if (key > cur->key)
                {
                    if (cur->right == nullptr)
                        throw std::out_of_range("BSTMap<K,V>::operator[](const K& key) const");
                    else
                        cur = cur->right;
                }
                if (key < cur->key)
                {
                    if (cur->left == nullptr)
                        throw std::out_of_range("BSTMap<K,V>::operator[](const K& key) const");
                    else
                        cur = cur->left;
                }
            }
        }
    }

    // Returns the value for a given key. Throws out_of_range if the
    // given key is not in the collection. 
    template<typename K, typename V>
    const V& AVLMap<K,V>::operator[](const K& key) const
    {
        if (empty())
            throw std::out_of_range("BSTMap<K,V>::operator[](const K& key) const");
        else
        {
            Node* cur = root;
            while (1)
            {
                if (key == cur->key)
                    return cur->value;
                if (key > cur->key)
                {
                    if (cur->right == nullptr)
                        throw std::out_of_range("BSTMap<K,V>::operator[](const K& key) const");
                    else
                        cur = cur->right;
                }
                if (key < cur->key)
                {
                    if (cur->left == nullptr)
                        throw std::out_of_range("BSTMap<K,V>::operator[](const K& key) const");
                    else
                        cur = cur->left;
                }
            }
        }
    }

    // Extends the collection by adding the given key-value
    // pair. Assumes the key being added is not present in the
    // collection. Insert does not check if the key is present.
    template<typename K, typename V>
    void AVLMap<K,V>::insert(const K& key, const V& value)
    {   
        ++count;
        root = insert(key, value, root);
    }

    // Shrinks the collection by removing the key-value pair with the
    // given key. Does not modify the collection if the collection does
    // not contain the key. Throws out_of_range if the given key is not
    // in the collection.
    template<typename K, typename V>
    void AVLMap<K,V>::erase(const K& key)
    {
        if(empty() or contains(key) == false) 
            throw std::out_of_range("void BSTMap<K,V>::erase(const K& key)");
        --count;
        root = erase(key,root);
    }

    // Returns true if the key is in the collection, and false otherwise.
    template<typename K, typename V>
    bool AVLMap<K,V>::contains(const K& key) const
    {
        if (empty())
            return false;
        else
        {
            Node* cur = root;
            while (1)
            {
                //actual contains
                if (key == cur->key)
                    return true;
                if (key > cur->key)
                {
                    if (cur->right == nullptr)
                        return false;
                    else
                        cur = cur->right;
                }
                if (key < cur->key)
                {
                    if (cur->left == nullptr)
                        return false;
                    else
                        cur = cur->left;
                }
            }
        }
    }

    // Returns the keys k in the collection such that k1 <= k <= k2
    template<typename K, typename V>
    ArraySeq<K> AVLMap<K,V>::find_keys(const K& k1, const K& k2) const
    {
        ArraySeq<K> keys;
        Node* st_root = root;
        find_keys(k1, k2, st_root, keys );
        keys.sort();
        return keys;
    }

    // Returns the keys in the collection in ascending sorted order
    template<typename K, typename V>
    ArraySeq<K> AVLMap<K,V>::sorted_keys() const
    {
        ArraySeq<K> keys;
        Node* st_root = root;
        sorted_keys(st_root, keys);
        keys.sort();
        return keys;
    }

    // Returns the height of the binary search tree
    template<typename K, typename V>
    int AVLMap<K,V>::height() const
    {
        if(root)
            return root->height;
        else
            return 0;
    }

    // clean up the tree and reset count to zero given subtree root
    template<typename K, typename V>
    void AVLMap<K,V>::make_empty(Node* st_root)
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

    // copy assignment helper
    template<typename K, typename V>
    typename AVLMap<K,V>::Node* AVLMap<K,V>::copy(const Node* st_root) const
    {
        if(st_root == nullptr) 
            return nullptr;
        Node* tmp = new Node;
        tmp->key = st_root->key;
        tmp->value = st_root->value;
        tmp->height = st_root->height;
        tmp->right = copy(st_root->right);
        tmp->left = copy(st_root->left);
        return tmp;
    }
    
    // erase helper
    template<typename K, typename V>
    typename AVLMap<K,V>::Node* AVLMap<K,V>::erase(const K& key, Node* st_root)
    {
        int b = 0;
        if(st_root == nullptr) 
            return rebalance(st_root);
        if(key < st_root->key)
        {
            st_root->left = erase(key, st_root->left);
            ++b;
        }
        else if(key > st_root->key)
        {
            st_root->right = erase(key, st_root->right);
            ++b;
        }
        //erase height change
        if (!st_root->right and !st_root->left)
            st_root->height = 1;
        else if (st_root->left and !st_root->right)
        {
            if (st_root->height - st_root->left->height > 1)
                st_root->height--;
        }
        else if (st_root->right and !st_root->left)
        {
            if (st_root->height - st_root->right->height > 1)
                st_root->height--;
        }
        else if (st_root->right and st_root->left)
        {
            if ( (st_root->height - st_root->right->height > 1) and (st_root->height - st_root->left->height > 1) )
                st_root->height--;
        }
        //in order successor
        if (b < 1)
        {
            if(st_root->left == nullptr and st_root->right == nullptr) 
            {
                delete st_root;
                return nullptr;
            }
            else if(st_root->left == nullptr) 
            {
                Node* temp = st_root->right;
                delete st_root;
                return rebalance(temp);
            }
            else if(st_root->right == nullptr) 
            {
                Node* temp = st_root->left;
                delete st_root;
                return rebalance(temp);
            }
            //in order successor
            Node* cur = st_root->right;
            while(cur != nullptr and cur->left != nullptr) 
                cur = cur->left;
            Node* tmp = cur;
            st_root->key = tmp->key;
            st_root->value = tmp->value;
            st_root->right = erase(tmp->key, st_root->right);
        }
        return rebalance(st_root);
    }

    // insert helper
    template<typename K, typename V>
    typename AVLMap<K,V>::Node* AVLMap<K,V>::insert(const K& key, const V& value, Node* st_root)
    {
        if (!st_root)
        {
            Node* tmp = new Node;
            tmp->key = key;
            tmp->value = value;
            tmp->left = nullptr;
            tmp->right = nullptr;
            tmp->height = 1;
            st_root = tmp;
        }
        else
        {
            if (key <= st_root->key)
                st_root->left = insert(key, value, st_root->left);
            else
                st_root->right = insert(key, value, st_root->right);    
            // ** v backtracking v ** //
            if (st_root->left and !st_root->right)
                st_root->height = 1 + st_root->left->height;
            else if (st_root->right and !st_root->left)
                st_root->height = 1 + st_root->right->height;
            else if (st_root->left->height > st_root->right->height)
                st_root->height = 1 + st_root->left->height;
            else if (st_root->left->height <= st_root->right->height)
                st_root->height = 1 + st_root->right->height;
        }
        return rebalance(st_root);
    }
    
    // find_keys helper
    template<typename K, typename V>
    void AVLMap<K,V>::find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const
    {
        if(st_root == nullptr)
            return;
        if (st_root->key >= k1 and st_root->key <= k2)
            keys.insert(st_root->key, keys.size());
        if (st_root->left != nullptr)
            find_keys(k1, k2, st_root->left, keys);
        if (st_root->right != nullptr)
            find_keys(k1, k2, st_root->right, keys);
    }

    // sorted_keys helper
    template<typename K, typename V>
    void AVLMap<K,V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
    {
        if(st_root == nullptr)
            return;
        keys.insert(st_root->key, keys.size());
        if (st_root->left != nullptr)
            sorted_keys(st_root->left, keys);
        if (st_root->right != nullptr)
            sorted_keys(st_root->right, keys);
    }

    // rotations
    template<typename K, typename V>
    typename AVLMap<K,V>::Node* AVLMap<K,V>::right_rotate(Node* st_root)
    {
        Node* Lptr = st_root->left; 
        st_root->left = Lptr->right; 
        Lptr->right = st_root; 
        return Lptr;
    }

    template<typename K, typename V>
    typename AVLMap<K,V>::Node* AVLMap<K,V>::left_rotate(Node* st_root)
    {
        Node* Rptr = st_root->right; 
        st_root->right = Rptr->left; 
        Rptr->left = st_root; 
        return Rptr;
    }

    // rebalance
    template<typename K, typename V>
    typename AVLMap<K,V>::Node* AVLMap<K,V>::rebalance(Node* st_root)
    {
        Node* Lptr = st_root->left;
        Node* Rptr = st_root->right;
        //left but no right
        if (Lptr and !Rptr and Lptr->height > 1)
        {
            //right left
            if (!Lptr->left)
            {
                st_root->left = left_rotate(Lptr);
                st_root->left->left->height--;
                st_root->left->height++;
            }
            //left left
            st_root = right_rotate(st_root);
            if (st_root->right->left and !st_root->right->right)
            {
                st_root->right->height--;
                st_root->height++;          
            }     
            else
                st_root->right->height -= 2;
        }
        //right but no left
        else if (Rptr and !Lptr and Rptr->height > 1)
        {
            //left right
            if (!Rptr->right)
            {
                st_root->right = right_rotate(Rptr);
                st_root->right->right->height--;
                st_root->right->height++;
            }
            //right right
            st_root = left_rotate(st_root);
            if (st_root->left->right and !st_root->left->left)
            {
                st_root->left->height--;
                st_root->height++;
            }     
            else
                st_root->left->height -= 2;
        }
        //left and right, left heavy
        else if (Lptr and Rptr and (Lptr->height - Rptr->height) > 1)
        {
            //left left
            if (Lptr->left->height >= Lptr->right->height)
            {
                st_root = right_rotate(st_root);
                st_root->right->height -= 2;
            }
            //right left
            else if (Lptr->right->height > Lptr->left->height)
            {
                st_root->left = left_rotate(Lptr);
                st_root->left->left->height--;
                st_root->left->height++;
                st_root = right_rotate(st_root);
                st_root->right->height -= 2;
            }
        }
        //left and right, right heavy
        else if (Lptr and Rptr and (Rptr->height - Lptr->height) > 1)
        {
            //right right
            if (Rptr->right->height >= Rptr->left->height)
            {
                st_root = left_rotate(st_root);
                st_root->left->height -= 2;
            }
            //left right
            else if (Rptr->left->height > Rptr->right->height)
            {
                st_root->right = right_rotate(Rptr);
                st_root->right->right->height--;
                st_root->right->height++;
                st_root = left_rotate(st_root);
                st_root->left->height -= 2;
            }
        }
        return st_root; 
    }

    #endif
    
