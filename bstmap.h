//---------------------------------------------------------------------------
// NAME: Tyler Kamphouise
// DATE: Fall 2021
// DESC: Super cool Binary Search Tree, way cooler than dictionaries or hash tables
//---------------------------------------------------------------------------

#ifndef BSTMAP_H
#define BSTMAP_H

#include "map.h"
#include "arrayseq.h"
#include <iostream>


template<typename K, typename V>
class BSTMap : public Map<K,V>
{
public:

    // default constructor
    BSTMap();

    // copy constructor
    BSTMap(const BSTMap& rhs);

    // move constructor
    BSTMap(BSTMap&& rhs);

    // copy assignment
    BSTMap& operator=(const BSTMap& rhs);

    // move assignment
    BSTMap& operator=(BSTMap&& rhs);  

    // destructor
    ~BSTMap();
  
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
  
private:

  // node for linked-list separate chaining
    struct Node 
    {
        K key;
        V value;
        Node* left;
        Node* right;
    };

    // number of key-value pairs in map
    int count = 0;

    // array of linked lists
    Node* root = nullptr;

    // clean up the tree and reset count to zero given subtree root
    void make_empty(Node* st_root);

    // copy assignment helper
    Node* copy(const Node* rhs_st_root) const;
  
    // erase helper
    Node* erase(const K& key, Node* st_root);

    // find_keys helper
    void find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const;

    // sorted_keys helper
    void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

    // height helper
    int height(const Node* st_root) const;
  
};


    // TODO: Implement the above functions per the directions in HW-7

    // default constructor
    template<typename K, typename V>
    BSTMap<K,V>::BSTMap()
    {

    }

    // copy constructor
    template<typename K, typename V>
    BSTMap<K,V>::BSTMap(const BSTMap& rhs)
    {
        *this = rhs;
    }

    // move constructor
    template<typename K, typename V>
    BSTMap<K,V>::BSTMap(BSTMap&& rhs)
    {
        *this = std::move(rhs);
    }

    // copy assignment
    template<typename K, typename V>
    BSTMap<K,V>& BSTMap<K,V>::operator=(const BSTMap& rhs)
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
    BSTMap<K,V>& BSTMap<K,V>::operator=(BSTMap&& rhs)
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
    BSTMap<K,V>::~BSTMap()
    {
        make_empty(root);
    }
  
    // Returns the number of key-value pairs in the map
    template<typename K, typename V>
    int BSTMap<K,V>::size() const
    {
        return count;
    }

    // Tests if the map is empty
    template<typename K, typename V>
    bool BSTMap<K,V>::empty() const
    {
        if (size() == 0)
            return true;
        else    
            return false;
    }

    // Allows values associated with a key to be updated. Throws
    // out_of_range if the given key is not in the collection.
    template<typename K, typename V>
    V& BSTMap<K,V>::operator[](const K& key)
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
    const V& BSTMap<K,V>::operator[](const K& key) const
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
    void BSTMap<K,V>::insert(const K& key, const V& value)
    {
        Node* entry = new Node;
        entry->key = key;
        entry->value = value;
        entry->left = nullptr;
        entry->right = nullptr;
        if (empty())
            root = entry;
        else
        {
            Node* cur = root;
            while (1)
            {
                if (entry->key > cur->key)
                {
                    if (cur->right == nullptr)
                    {
                        cur->right = entry;
                        break;
                    }
                    else
                        cur = cur->right;
                }
                if (entry->key < cur->key)
                {
                    if (cur->left == nullptr)
                    {
                        cur->left = entry;
                        break;
                    }
                    else
                        cur = cur->left;
                }
            }
        }
        ++count;
    }

    // Shrinks the collection by removing the key-value pair with the
    // given key. Does not modify the collection if the collection does
    // not contain the key. Throws out_of_range if the given key is not
    // in the collection.
    template<typename K, typename V>
    void BSTMap<K,V>::erase(const K& key)
    {
        if(empty() or contains(key) == false) 
            throw std::out_of_range("void BSTMap<K,V>::erase(const K& key)");
        --count;
        root = erase(key,root);
    }

    // Returns true if the key is in the collection, and false otherwise.
    template<typename K, typename V>
    bool BSTMap<K,V>::contains(const K& key) const
    {
        if (empty())
            return false;
        else
        {
            Node* cur = root;
            while (1)
            {
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
    ArraySeq<K> BSTMap<K,V>::find_keys(const K& k1, const K& k2) const
    {
        ArraySeq<K> keys;
        Node* st_root = root;
        find_keys(k1, k2, st_root, keys );
        keys.sort();
        return keys;
    }

    // Returns the keys in the collection in ascending sorted order
    template<typename K, typename V>
    ArraySeq<K> BSTMap<K,V>::sorted_keys() const
    {
        ArraySeq<K> keys;
        Node* st_root = root;
        sorted_keys(st_root, keys);
        keys.sort();
        return keys;
    }

    // Returns the height of the binary search tree
    template<typename K, typename V>
    int BSTMap<K,V>::height() const
    {
        Node* st_root = root;
        return height(st_root);
    }
  
    // clean up the tree and reset count to zero given subtree root
    template<typename K, typename V>
    void BSTMap<K,V>::make_empty(Node* st_root)
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

    // ***************** //
    // **** HELPERS **** //
    // ***************** //

    // copy assignment helper
    template<typename K, typename V>
    typename BSTMap<K,V>::Node* BSTMap<K,V>::copy(const Node* st_root) const
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
  
    // erase helper
    template<typename K, typename V>
    typename BSTMap<K,V>::Node* BSTMap<K,V>::erase(const K& key, Node* st_root)
    {

        if(st_root == nullptr) 
            return st_root;
        if(key < st_root->key)
            st_root->left = erase(key, st_root->left);
        else if(key > st_root->key)
            st_root->right = erase(key, st_root->right);
        else
        {
            if(st_root->left == nullptr and st_root->right == nullptr) 
                return nullptr;
            else if(st_root->left == nullptr) 
            {
                Node* temp = st_root->right;
                delete st_root;
                return temp;
            }
            else if(st_root->right == nullptr) 
            {
                Node* temp = st_root->left;
                delete st_root;
                return temp;
            }
            Node* cur = st_root->right;
            while(cur != nullptr and cur->left != nullptr) 
                cur = cur->left;
            Node* tmp = cur;
            st_root->key = tmp->key;
            st_root->right = erase(tmp->key, st_root->right);
        }
        return st_root;
    }

    // find_keys helper
    template<typename K, typename V>
    void BSTMap<K,V>::find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const
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
    void BSTMap<K,V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
    {
        if(st_root == nullptr)
            return;
        keys.insert(st_root->key, keys.size());
        if (st_root->left != nullptr)
            sorted_keys(st_root->left, keys);
        if (st_root->right != nullptr)
            sorted_keys(st_root->right, keys);
    }

    // height helper
    template<typename K, typename V>
    int BSTMap<K,V>::height(const Node* st_root) const
    {
        /*
        int max = 0;
        if (st_root->left != nullptr and st_root->right != nullptr)
        {
            if (height(st_root->left) > height(st_root->right))
                max = height(st_root->left);
            else
                max = height(st_root->right);
        }
        else if (st_root->left != nullptr)
            max = height(st_root->left);
        else if (st_root->right != nullptr)
            max = height(st_root->right);
        return 1 + max;
        */
        if(st_root == nullptr)
            return 0;
        else
        {
            int left_height = height(st_root->left);
            int right_height = height(st_root->right);
            if (left_height > right_height)
                return (left_height + 1);
            else
                return (right_height + 1);
        }
    }

#endif
