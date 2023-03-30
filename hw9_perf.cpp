//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw8_perf.cpp
// DATE: Fall 2021
// DESC: Simple performance test driver for HW-8. To run from the
//       command line use:
//          ./hw8_perf 
//       which will print out the corresponding HW-8 timing data. To
//       save this data to a file, run the command:
//          ./hw8_perf > output.dat
//       This file can then be used by the plotting script to generate
//       the corresponding performance graphs.
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "util.h"
#include "arrayseq.h"
#include "map.h"
#include "bstmap.h"
#include "avlmap.h"
#include "binminheap.h"

using namespace std;
using namespace std::chrono;


double timed_insert(Map<int,int>& m, int key);
double timed_insert(MinHeap<int,int>& m, int key);
double timed_erase(Map<int,int>& m, int key);
double timed_erase(MinHeap<int,int>& m, int key);
double timed_sorted_keys(const Map<int,int>& m);
double timed_sorted_keys(const MinHeap<int,int>& m);

// test parameters
const int start = 0;
const int step = 15000;
const int stop = 150000; 
const int runs = 1;


int main(int argc, char* argv[])
{
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // output data header
  cout << "# All times in milliseconds (msec)" << endl;
  cout << "# Column 1 = input data size" << endl;

  cout << "# Column 2 = bst map insert shuffled" << endl;
  cout << "# Column 3 = avl map insert shuffled" << endl;
  cout << "# Column 4 = min heap map insert shuffled" << endl;
  
  cout << "# Column 5 = bst map erase shuffled" << endl;
  cout << "# Column 6 = avl map erase shuffled" << endl;  
  cout << "# Column 7 = min heap map erase shuffled" << endl;

  cout << "# Column 8 = bst map sorted keys shuffled" << endl;
  cout << "# Column 9 = avl map sorted keys shuffled" << endl;
  cout << "# Column 10 = min heap map sorted keys shuffled" << endl;


  // generate shuffled data
  ArraySeq<int> keys, vals;
  for (int i = 2; i <= stop*2; i += 2) {
    keys.insert(i, keys.size());
    vals.insert(i, vals.size());
  }
  faro_shuffle(keys, 7);
  // faro_shuffle(vals, 2);

  // generate the timing data
  for (int n = start; n <= stop; n += step) {
    // load shuffled data
    BSTMap<int,int> m1;
    AVLMap<int,int> m2;
    MinHeap<int,int> m3;

    for (int i = 0; i < n; ++i) {
      m1.insert(keys[i], vals[i]);
      m2.insert(keys[i], vals[i]);
      m3.insert(keys[i], vals[i]);
    }

    int med = n;

    // insert and erase (three cases for binsearch to be fair)
    double c2 = timed_insert(m1, med + 1);    
    double c5 = timed_erase(m1, med + 1);
    double c3 = timed_insert(m2, med + 1);
    double c6 = timed_erase(m2, med + 1);
    double c4 = timed_insert(m3, med + 1);
    double c7 = timed_erase(m3, med + 1);

    assert(m1.size() == n);
    assert(m2.size() == n);
    assert(m3.size() == n);
    
    // sort
    double c8 = timed_sorted_keys(m1);
    double c9 = timed_sorted_keys(m2);
    double c10 = timed_sorted_keys(m3);

    cout << n
         << " " << c2 << " " << c3 << " " << c4
         << " " << c5 << " " << c6 << " " << c7 
         << " " << c8 << " " << c9 << " " << c10 
         << endl;
  }
  
}


// assumes keys are multiples of 2 and key to insert is odd
double timed_insert(Map<int,int>& m, int key)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.insert(key + (r * 2), key + (r * 2));
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

// removes the odd values inserted from timed_insert
double timed_erase(Map<int,int>& m, int key)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.erase(key + (r * 2));
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

double timed_sorted_keys(const Map<int,int>& m)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.sorted_keys();
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

// assumes keys are multiples of 2 and key to insert is odd
double timed_insert(MinHeap<int,int>& m, int key)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.insert(key + (r * 2), key + (r * 2));
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

// removes the odd values inserted from timed_insert
double timed_erase(MinHeap<int,int>& m, int key)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.remove_min();
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

double timed_sorted_keys(const MinHeap<int,int>& m)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.heap_sort();
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}



