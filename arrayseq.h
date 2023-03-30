
//---------------------------------------------------------------------------
// NAME:
// FILE: arrayseq.h
// DATE: Fall 2021
// DESC: 
//----------------------------------------------------------------------


#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include <stdexcept>
#include <ostream>
#include "sequence.h"


template<typename T>
class ArraySeq : public Sequence<T>
{

public:

  // Default constructor
  ArraySeq();

  // Copy constructor
  ArraySeq(const ArraySeq& rhs);

  // Move constructor
  ArraySeq(ArraySeq&& rhs);

  // Copy assignment operator
  ArraySeq& operator=(const ArraySeq& rhs);

  // Move assignment operator
  ArraySeq& operator=(ArraySeq&& rhs);

  // Destructor
  ~ArraySeq();
  
  // Returns the number of elements in the sequence
  virtual int size() const;

  // Tests if the sequence is empty
  virtual bool empty() const;

  // Returns a reference to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual T& operator[](int index);

  // Returns a constant address to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual const T& operator[](int index) const;

  // Extends the sequence by inserting the element at the given
  // index. Throws out_of_range if the index is invalid.
  virtual void insert(const T& elem, int index);

  // Shrinks the sequence by removing the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual void erase(int index);

  // Returns true if the element is in the sequence, and false
  // otherwise.
  virtual bool contains(const T& elem) const;

  // Sorts the elements in the sequence using less than equal (<=)
  // operator. (Not implemented in HW-3)
  virtual void sort(); 

  // implements merge sort over current sequence
  void merge_sort();

  // implements quick sort over current sequence
  void quick_sort();

  
private:

  // resizable array
  T* array = nullptr;

  // size of list
  int count = 0;

  // max capacity of the array
  int capacity = 0;

  // helper to double the capacity of the array
  void resize();
  
  // helper to delete the array list (called by destructor and copy
  // constructor)
  void make_empty();

   // helper functions for merge and quick sort
  void merge_sort(int start, int end);

  void quick_sort(int start, int end);

};

// *******IMPLEMENTATIONS*******
// TODO: Implement the above functions below using the approaches
//       discussed in class and specified in the homework assignment.

template<typename T>
std::ostream& operator<<(std::ostream& output, const ArraySeq<T>& array)
{
  for (int i = 0; i < array.size(); i++)
  {
    output << array[i];
    if (array.size() > 1 and i < array.size() - 1)
      output << ", ";
  }
  return output;
}

// Default constructor
template<typename T>
ArraySeq<T>::ArraySeq()
{
  T* new_array = new T[capacity*2];
}

// Copy constructor
template<typename T>
ArraySeq<T>::ArraySeq(const ArraySeq& rhs)
{
    *this = rhs;
}

// Move constructor
template<typename T>
ArraySeq<T>::ArraySeq(ArraySeq&& rhs)
{
    *this = std::move(rhs);
}

// Copy assignment operator
template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(const ArraySeq& rhs)
{
    if (this != &rhs) //if error, make *this instead of this
    {
        make_empty();
        for(int i = 0; i < rhs.size(); i++)
            insert(rhs[i] , i);
    }
    return *this;
}

// Move assignment operator
template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(ArraySeq&& rhs)
{
    if (this != &rhs)
    {
        make_empty();
        capacity = rhs.capacity;
        rhs.capacity = 0;
        count = rhs.count;
        rhs.count = 0;
        array = rhs.array;
        rhs.array = nullptr;
    }
    return *this;
}
  
// Destructor
template<typename T>
ArraySeq<T>::~ArraySeq()
{
    make_empty();
}
  
// Returns the number of elements in the sequence
template<typename T>
int ArraySeq<T>::size() const
{
    return count;
}

// Tests if the sequence is empty
template<typename T>
bool ArraySeq<T>::empty() const
{
    return size() == 0;
}

// Returns a reference to the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
T&  ArraySeq<T>::operator [](int index)
{
    if (index >= count or index < 0) //if error change to > count
        throw std::out_of_range("ArraySeq<T>::operator[](int)");
    else
        return array[index];
}

// Returns a constant address to the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
const T& ArraySeq<T>::operator [](int index) const
{
    if (index >= count or index < 0) //if error change to > count
        throw std::out_of_range("ArraySeq<T>::operator[](int)");
    else
        return array[index];
}

// Extends the sequence by inserting the element at the given
// index. Throws out_of_range if the index is invalid.
template<typename T>
void ArraySeq<T>::insert(const T& elem, int index)
{
    /*
    // check for valid index
    if (index > capacity)
        throw std::out_of_range("ArraySeq<T>::insert(const T&, int)");
    if (count == 0)
        capacity = 1;
    else if (count == capacity)
        resize();  
    for(int i = index; i < count; i++) 
        array[i+1] = array[i];
    array[index] = elem;
    ++count;
    */
    //insert that kinda works but is bad
    if(index < 0 or index > size())
        throw std::out_of_range("ArraySeq<T>::insert(const T&, int)");
    if(empty()) 
    {
        capacity = 16;
        array = new T[capacity];
    }
    else if(size() == capacity)
        resize();
    if(size() == index)
        array[index] = elem;
    else 
    {
        for(int i = size(); i >= index; i--) 
            array[i+1] = array[i];
        array[index] = elem;
    }
    count++;
}

// Shrinks the sequence by removing the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
void ArraySeq<T>::erase(int index)
{
    //check for valid index
    if (count == 0)
        throw std::out_of_range("ArraySeq<T>::erase(int)");
    if (index < 0 || index >= count) //if getting arrayErase errors, this is the problem. make > count instead
        throw std::out_of_range("ArraySeq<T>::erase(int)");
    //actual algorithm
    if(index < count && index >= 0)
    {
        for(int i = index; i < count - 1; i++)
            array[i] = array[i+1];
    }
    --count;
}

// Returns true if the element is in the sequence, and false
// otherwise.
template<typename T>
bool ArraySeq<T>::contains(const T& elem) const
{
    bool found = false;
        for (int i = 0; i < count and !found; ++i)
        {
            if (array[i] == elem)
                found = true;
        }
    return found;
}

// helper to double the capacity of the array
template<typename T>
void ArraySeq<T>::resize()
{
    capacity = 2 * capacity;
    T *temp_list = new T[capacity];
    for (int i = 0; i < size(); i++) 
        temp_list[i] = array[i];
    delete []array;
    array = temp_list;
}
  
// helper to delete the array list (called by destructor and copy
// constructor)
template<typename T>
void ArraySeq<T>::make_empty()
{
    delete []array;
}

// implements merge sort over current sequence
template<typename T>
void ArraySeq<T>::merge_sort()
{
    merge_sort(0, count -1);
}

// implements quick sort over current sequence
template<typename T>
void ArraySeq<T>::quick_sort()
{
    quick_sort(0, count -1);
}

// helper functions for merge and quick sort
template<typename T>
void ArraySeq<T>::merge_sort(int start, int end)
{
    if(start < end)
    {
        int mid = (start + end) / 2;
        merge_sort(start, mid);
        merge_sort(mid + 1, end);

    //merge
    T tmpArray[(end - start) + 1];
        int first1 = start;
        int first2 = mid + 1;
        int i = 0;
        while ((first1 <= mid) and (first2 <= end))
        {
            if (array[first1] < array[first2])
                tmpArray[i++] = array[first1++];
            else 
                tmpArray[i++] = array[first2++];
        }
        while (first1 <= mid)
            tmpArray[i++] = array[first1++];
        while (first2 <= end)
            tmpArray[i++] = array[first2++];
        for (int j = 0; j <= (end - start); ++j)
            array[start +j] = tmpArray[j];
    }
}

template<typename T>
void ArraySeq<T>::quick_sort(int start, int end)
{
    if (start < end )
    {
        int pivot_val = array[start];
        int end_p1 = start;
        T swap_var = 0;
        for (int i = start +1; i <= end; ++i)
        {
            if (array[i] < pivot_val)
            {
                end_p1 = end_p1 + 1;
                //swap(array[i], array[end_p1])
                swap_var = array[i];
                array[i] = array[end_p1];
                array[end_p1] = swap_var;
            }
        }
        //swap(array[start], array[end_p1]) 
        swap_var = array[start];
        array[start] = array[end_p1];
        array[end_p1] = swap_var;
        quick_sort(start, end_p1 - 1);
        quick_sort(end_p1 + 1, end);
    }
}

template<typename T>
void ArraySeq<T>::sort()
{
    merge_sort();
}

#endif
