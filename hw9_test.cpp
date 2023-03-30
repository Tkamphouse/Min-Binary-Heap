//---------------------------------------------------------------------------
// NAME:
// FILE: hw8_test.cpp
// DATE: Fall 2021
// DESC: 
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "arrayseq.h"
#include "binminheap.h"

using namespace std;


//----------------------------------------------------------------------
// Basic Tests for the MinHeap implementation of Map
//----------------------------------------------------------------------

TEST(BasicMinHeapTests, EmptyCheck)
{
  MinHeap<char,int> m;
  ASSERT_EQ(true, m.empty());
  ASSERT_EQ(0, m.size());
}

TEST(BasicMinHeapTests, InsertCheck)
{
  MinHeap<char,int> m;
  
  m.insert('c', 40);
  m.insert('b', 20);
  m.insert('a', 30);
  m.insert('e', 10);
  m.insert('h', 60);
  m.insert('f', 50);
  m.insert('g', 80);
  m.insert('d', 70);
  ASSERT_EQ(false, m.empty());
  ASSERT_EQ(8, m.size());
}

TEST(BasicMinHeapTests, FindMinCheck)
{
  MinHeap<char,int> m;
  
  m.insert('c', 40);
  m.insert('e', 10);
  m.insert('h', 60);
  m.insert('f', 50);
  m.insert('g', 80);
  m.insert('d', 70);
  ASSERT_EQ('c', m.find_min());
  m.insert('b', 20);
  ASSERT_EQ('b', m.find_min());
  m.insert('a', 30);
  ASSERT_EQ('a', m.find_min());
}

TEST(BasicMinHeapTests, RemoveMinCheck)
{
  MinHeap<char,int> m;
  int size = 10;
  for (int i = 0; i < size; ++i)
    m.insert('a' + i, 10 * (i + 1));
  ASSERT_EQ(false, m.empty());
  ASSERT_EQ(size, m.size());
  ASSERT_EQ('a', m.find_min());
  m.remove_min();
  ASSERT_EQ(size - 1, m.size());
  ASSERT_EQ('b', m.find_min());
  m.remove_min();
  m.remove_min();
  ASSERT_EQ(size - 3, m.size());
  ASSERT_EQ('d', m.find_min());
  m.remove_min();
  ASSERT_EQ(size - 4, m.size());
  ASSERT_EQ('e', m.find_min());
  //small amount of elements, and no elements
  MinHeap<char,int> m2;
  EXPECT_THROW(m2.remove_min(), std::out_of_range);
  m2.insert('b', 20);
  ASSERT_EQ(1, m2.size());
  m2.remove_min();
  ASSERT_EQ(0, m2.size());
  m2.insert('b', 20);
  m2.insert('a', 10);
  ASSERT_EQ(2, m2.size());
  m2.remove_min();
  ASSERT_EQ(1, m2.size());
  ASSERT_EQ('b', m2.find_min());
}

TEST(BasicMinHeapTests, HeapSortCheck)
{
  MinHeap<char,int> m;
  ArraySeq<char> k;

  m.insert('a', 00);
  m.insert('e', 40);
  m.insert('c', 20);
  m.insert('b', 10);
  m.insert('d', 30);
  m.insert('g', 60);
  m.insert('f', 50);
  m.insert('h', 70);
  ASSERT_EQ(8, m.size());  
  k = m.heap_sort();
  ASSERT_EQ(8, k.size());  
  for (int i = 0; i < 8; ++i)
    ASSERT_EQ('a' + i, k[i]);
}

TEST(BasicMinHeapTests, DestructorCheck)
{
  MinHeap<char,int>* m = new MinHeap<char,int>;
  EXPECT_NO_THROW(delete m);
  m = new MinHeap<char,int>;
  m->insert('a', 1);
  EXPECT_NO_THROW(delete m);
  m = new MinHeap<char,int>;
  for (char c = 'a'; c <= 'z'; ++c)
    m->insert(c, (int)(c - 'a'));
  EXPECT_NO_THROW(delete m);
  m = new MinHeap<char,int>;
  m->insert('e', 40);
  m->insert('c', 20);
  m->insert('b', 10);
  m->insert('d', 30);
  m->insert('g', 60);
  m->insert('f', 50);
  m->insert('h', 70);
  EXPECT_NO_THROW(delete m);  
}

TEST(BasicMinHeapTests, CopyConstructorCheck)
{
  // copy empty seq
  MinHeap<char,int> m1;
  MinHeap<char,int> m2(m1);
  ASSERT_EQ(m1.size(), m2.size());
  // copy one-element seq
  m1.insert('a', 1);
  ASSERT_NE(m1.size(), m2.size());
  m2.insert('c', 3);
  m2.insert('b', 2);
  m2.insert('d', 4);
  MinHeap<char,int> m3(m2);
  ASSERT_EQ(m2.size(), m3.size());
  ASSERT_EQ(true, m2.find_min() == 'b');
  ASSERT_EQ(true, m3.find_min() == 'b');
  // remove item and check two seqs are different
  m3.remove_min();
  ASSERT_NE(m2.size(), m3.size());
}

TEST(BasicMinHeapTests, CopyAssignmentCheck)
{
  MinHeap<char,int> m1;
  MinHeap<char,int> m2;
  // both empty
  m2 = m1;                
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(0, m2.size());
  // add to m1 (shouldn't change m2)
  m1.insert('a', 0);
  m1.insert('b', 1);
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(0, m2.size());
  ASSERT_EQ(true, m1.find_min() == 'a');
  // assign m 1 to itself (shouldn't change anything)
  m1 = m1;
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m1.find_min() == 'a');
  // add items to m2 and assign m2 to m1
  m2.insert('d', 1);
  m2.insert('c', 0);
  m2.insert('e', 2);
  m1 = m2;
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(3, m1.size());
  ASSERT_EQ(true, m1.find_min() == 'c' and m2.find_min() == 'c');
  // add to m1 (shouldn't change m2)
  m1.insert('a', 3);
  ASSERT_EQ(4, m1.size());
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(false, m2.find_min() == 'a');
  ASSERT_EQ(true, m1.find_min() == 'a');
}

TEST(BasicMinHeapTests, MoveConstructorCheck)
{
  // move empty map
  MinHeap<char,int> m1;
  MinHeap<char,int> m2(std::move(m1));
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(0, m2.size());
  // move one-element ma[
  MinHeap<char,int> m3;
  m3.insert('a', 1);
  ASSERT_EQ(1, m3.size());
  ASSERT_EQ(true, m3.find_min() == 'a');
  MinHeap<char,int> m4(std::move(m3));
  ASSERT_EQ(0, m3.size());
  ASSERT_EQ(1, m4.size());
  ASSERT_EQ(true, m4.find_min() == 'a');
  // add item to new m (to ensure correct move)
  m4.insert('b', 2);
  ASSERT_EQ(0, m3.size());
  ASSERT_EQ(2, m4.size());
  ASSERT_EQ(true, m4.find_min() == 'a');
  m4.remove_min();
  ASSERT_EQ(true, m4.find_min() == 'b');
}

TEST(BasicMinHeapTests, MoveAssignmentCheck)
{
  // create a map
  MinHeap<char,int> m1;
  m1.insert('w', 2);
  m1.insert('l', 1);
  m1.insert('c', 3);
  ASSERT_EQ(3, m1.size());
  // and another
  MinHeap<char,int> m2;
  m2.insert('d', 4);
  ASSERT_EQ(1, m2.size());
  // move first to second
  m2 = std::move(m1);
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(true, m2.find_min() == 'c');
  m1.insert('a', 6);
  m1.insert('b', 5);
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m1.find_min() == 'a');
  ASSERT_EQ(false, m2.find_min() == 'a');
  // create an empty map
  MinHeap<char,int> m3;
  ASSERT_EQ(0, m3.size());
  // move second to third
  m3 = std::move(m2);
  ASSERT_EQ(3, m3.size());
  ASSERT_EQ(0, m2.size());
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m3.find_min() == 'c');
  EXPECT_THROW(m2.find_min(), std::out_of_range);
}


//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
