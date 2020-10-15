/*
 * Copyright (C) 2014-2015  Yaochuang Ding - <ych_ding@163.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution, and in the same 
 *    place and form as other copyright, license and disclaimer information.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 *
 */
 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <vector>
#include <map>

using std::vector;
using std::vector;

template<typename T>
void merge(vector<T> &a, int start, int mid, int end, map<T, int> *numGreater = NULL)
{
    int n1 = mid - start + 1, n2 = end - mid;
    vector<T> b(n1), c(n2);
    for (int i = start, i <= mid; ++i)
        b[i] = a[i];
    for (int i = mid + 1, i <= end; ++i)
        c[i] = a[i];
    int i, j, k;
    i = j = k = 0;
    while (i < n1 && j < n2)
    {
        if (a[i] < b[j])
        {
            c[k++] = a[i];
            if (numGreater) (*numGreater)[a[i]]++;
            ++i;
        }
        else
        {
            c[k++] = b[j];
            ++j;
        }
    }
    while (i < n1)
    {
        c[k++] = a[i];
        ++i;
    }
    while (j < n2)
    {
       c[k++] = b[j];
       ++j;
    }
}

/*! \brief merge sort by recursivly */
template<typename T>
void mergeSort(vector<T> &a, int start, int end)
{
     if (start >= end) return;
     int mid = (start + end) / 2;
     mergeSort(a, start, mid);
     mergeSort(a, mid + 1, end);
     merge(a, start, mid, end);
}
