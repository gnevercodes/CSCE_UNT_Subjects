#include "minheap.hpp"
#include <climits>
#include <stdio.h>
#include <iostream>

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

MinHeap::MinHeap(int size) {
	heap_size = 0;
	capacity = size;
	harr = new int[size];
}
MinHeap::~MinHeap() {}

int MinHeap::left(int parent) {
  int i = parent*2 +1;
  return (i < heap_size) ? i: -1;
}

int MinHeap::right(int parent) {
  int i= parent*2 + 2;
  return (i < heap_size) ? i:-1;
}

int MinHeap::parent(int child) {
  if (child != 0) {
    int i = (child - 1) >> 1;
    return i;
  }
  return -1;
}

int MinHeap::size() { return heap_size; }

void MinHeap::insert(int element) {
    if (heap_size == capacity) {
        cout << "Cannot insert key" << endl;
        return;
    }

    // Insert the new key at the end
    int i = heap_size;
    harr[i] = element;
    heap_size++;

    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)] > harr[i]) {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

int MinHeap::extractMin() {

   if (heap_size <= 0)
      {
            cout<<"There are no elements in the heap\n"<<endl;
            return INT_MAX;
      }

        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }

        int root = harr[0];
        harr[0] = harr[--heap_size];
        MinHeapify(0);
    
        return root;

}

void MinHeap::MinHeapify(int i){

  int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && l>0 && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && r>0 && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }

}

void MinHeap::display() {
  cout<<"MinHeap:- ";
  cout << heap_size << endl;
  for(int i = 0; i < heap_size; i++){
	cout << harr[i] << " ";
  }
  cout << endl;
}


void MinHeap::heapsort(vector<int>& A,int n) {

  MinHeap *hp= new MinHeap(n);

  // Inserting elements from vector to heap
    for(int i=0;i<n;i++)
      hp->insert(A[i]);

       for(int i=hp->heap_size-1;i>=0;i--)
   {
      A[i]=hp->extractMin();
   }

   n--;

   delete hp;

}
