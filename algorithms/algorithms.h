/*
 * Copyright (C) 2014-2016  Yaochuang Ding - <ych_ding@163.com>
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
 
#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

#include <vector>
#include <set>
#include <string>
#include "dataSource.h"
#include "search.h"
#include "bits.h"

using std::vector;
using std::set;
using std::string;

/*! \brief search a rotated sorted array, return index.
 * 
 */
template<typename T>
int searchRotatedSortedArray(const vector<T> & a, int low, int high, const T &target)
{
    if (low > high) return -1; // no such element.
    int mid = (low + high) / 2;
    if (a[mid] == target) return mid;
    if (a[mid] > a[low]) // a[low, ..., mid] sorted
    {
        if (target >= a[low] && target <= a[mid]) // target in range.
            return searchRotatedSortedArray(a, low, mid - 1, target);
        else
            return searchRotatedSortedArray(a, mid + 1, high, target);
    }
    else
    {
        if (target >= a[mid] && target <= a[high]) // target in range.
            return searchRotatedSortedArray(a, mid + 1, high, target);
        else
            return searchRotatedSortedArray(a, low, mid - 1, target);
    }
}

int sqrtOfPerfectSquare(int n);

void permutation(string str, int i, int j, set<string> &ret);
/* 
 * Given a set of n elements [1, n], generate all
 * possible combinations of k elements from 
 * the set.
 */
vector<vector<int> > combine(int n, int k);

/*************************************************
 * Function: Subset sum Problem. 
 * Retrun: 
 * Ideas:  
 * Notice:  It needs to calculate the sum. 
*************************************************/
int minSubsetDifference(const vector<int> &nums);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Subset sum problem.  --Recursive solution. list all possible subset and check them one by one.
//
bool subsetExist(const vector<int> &nums, int targetSum);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Coin Game. 
int coinGame(const vector<int> &coins);
#endif
