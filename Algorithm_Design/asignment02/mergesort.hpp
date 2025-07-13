#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

// Implement mergesort algorithm here.
//  Merge two sorted subarrays A[l..m] and A[m+1..r]
void Merge(vector<int> &A, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = A[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[m + 1 + j];

    // Merge the temporary arrays back into A[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        A[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        A[k] = R[j];
        j++;
        k++;
    }
}

// Main function to implement merge sort
void Mergesort(vector<int> &A, int l, int r)
{
    if (l < r)
    {
        // Find the middle point
        int m = l + (r - l) / 2;

        // Sort first and second halves
        Mergesort(A, l, m);
        Mergesort(A, m + 1, r);

        // Merge the sorted halves
        Merge(A, l, m, r);
    }
}