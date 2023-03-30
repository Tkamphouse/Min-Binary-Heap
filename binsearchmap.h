
//---------------------------------------------------------------------------
// NAME:
// DATE: Fall 2021
// DESC:
//---------------------------------------------------------------------------

#ifndef BINSEARCHMAP_H
#define BINSEARCHMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class BinSearchMap : public Map<K,V>
{
public:

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

  // Returns true if the key is in the collection, and false
  // otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order.
  ArraySeq<K> sorted_keys() const;  

private:

  // If the key is in the collection, bin_search returns true and
  // provides the key's index within the array sequence (via the index
  // output parameter). If the key is not in the collection,
  // bin_search returns false and provides the last index checked by
  // the binary search algorithm. 
  bool bin_search(const K& key, int& index) const;
  
  // implemented as a resizable array of (key-value) pairs
  ArraySeq<std::pair<K,V>> seq;

};

// TODO: Implement the BinSearchMap functions below. Note that you do
//       not need to implement a default constructor, destructor, copy
//       constructor, copy assignment operator, move constructor, and
//       move assignment operator for this version of Map. Instead,
//       the default C++ implementations are sufficient.

  // Returns the number of key-value pairs in the map
template<typename K, typename V>
int BinSearchMap<K,V>::size() const
{
  return seq.size();
}

  // Tests if the map is empty
template<typename K, typename V>
bool BinSearchMap<K,V>::empty() const
{
  return seq.empty();
}

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& BinSearchMap<K,V>::operator[](const K& key)
{
  int index = 0;
  bin_search(key, index);
  if (contains(key) == false)
    throw std::out_of_range("BinSearchMap<K,V>::operator[](const K& key)");
  else
    return seq[index].second;
}

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
template<typename K, typename V>
const V& BinSearchMap<K,V>::operator[](const K& key) const
{
  int index = 0;
  bin_search(key, index);
  if (contains(key) == false)
    throw std::out_of_range("BinSearchMap<K,V>::operator[](const K& key)");
  else
    return seq[index].second;
}

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
template<typename K, typename V>
void BinSearchMap<K,V>::insert(const K& key, const V& value)
{
  int index = 0;
  bin_search(key, index);
  std::pair<K,V> p { key , value };
  seq.insert( p , index); //or index -1 if fails
}

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
template<typename K, typename V>
void BinSearchMap<K,V>::erase(const K& key)
{
  int index = 0;
  bin_search(key, index);
  if (contains(key) == false)
    throw std::out_of_range("BinSearchMap<K,V>::operator[](const K& key)");
  else
    seq.erase(index);
}

  // Returns true if the key is in the collection, and false
  // otherwise.
template<typename K, typename V>
bool BinSearchMap<K,V>::contains(const K& key) const
{
  int index = 0;
  return bin_search(key, index);
}

  // Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> BinSearchMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> k;
  int index = 0;
  bin_search(k1, index);
  int bottom_bound = index;
  bin_search(k2, index);
  int top_bound = index;
  if (top_bound >= size())
    top_bound = size() - 1;
  for (int i = bottom_bound; i <= top_bound; ++i)
    k.insert(seq[i].first, k.size()); 
  return k;
}

  // Returns the keys in the collection in ascending sorted order.
template<typename K, typename V>
ArraySeq<K> BinSearchMap<K,V>::sorted_keys() const
{
  ArraySeq<K> k;
  for (int i = 0; i < seq.size(); ++i)
    k.insert(seq[i].first, i);
  return k;
}

  // If the key is in the collection, bin_search returns true and
  // provides the key's index within the array sequence (via the index
  // output parameter). If the key is not in the collection,
  // bin_search returns false and provides the last index checked by
  // the binary search algorithm. 
template<typename K, typename V>
bool BinSearchMap<K,V>::bin_search(const K& key, int& index) const
{
  int mid;
  int low = 0;
  int high = size() - 1;
  /*
  if (seq.size() == 0)
  {
    index = 0;
    return false;
  }
  */
  while ( low <= high )
  {
    index = 0;
    // find the middle index
    //mid = low + ((high - low) >> 1);
    mid = (low + high) / 2;
    if ( seq[mid].first == key ) // key found
    {
      index = mid;
      return true;
    }
    else if ( seq[mid].first > key ) // key may be on the left half
    {
      high = mid - 1;
      index = mid;
    }
    else if ( seq[mid].first < key ) // key may be on the right half
    {
      low = mid + 1;
      index = low;
    }
  }
  // key not found
  return false;
}

#endif
