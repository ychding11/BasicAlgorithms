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

 #ifndef SEARCH_H_
 #define SEARCH_H_

#include <vector>
#include <limits>

using std::vector;
using std::numeric_limits;

/*! \brief sear an odd presented element in array by binary search.
 *  element appears in pairs. [1, 2, 2, 1, 1] 
 */
template<typename T>
int oddPresentedElement(const vector<T> &elems, int low, int high)
{
    assert(low <= high);
    if (low > high)
    {
        return -1; // no such element.
    }
    if (low == high)
    {
        return low; // return element index
    }
    int mid = (low + high) >> 1;
    if (mid & 1) // odd index
    {
        if (elems[mid] == elems[mid - 1])
            return oddPresentedElement(elems, mid + 1, high);
        else
            return oddPresentedElement(elems, low, mid - 1);
    }
    else // even index
    {
        if (elems[mid] == elems[mid + 1])
            return oddPresentedElement(elems, mid + 2, high);
        else
            return oddPresentedElement(elems, low, mid);
    }
}

/*! \brief find max pair sum in an array.
 */
template <typename T>
T maxPairSum(const vector<T> &nums)
{
    int n = nums.size();
    assert(n >= 2);
    T a, b;
    a = b = numeric_limits<T>::min();
    for (int i = 0; i < n; ++i)
    {
        if (nums[i] > a)
        {
            if ( a > b) b = a;
        }
        else if (nums[i] > b)
        {
            b = nums[i];     
        }
    }
    return a + b;
}

/*! \brief Is there a pair sum equal to K, array is sorted and rotated. */
template<typename T>
bool isTherePairSumEqualK(const vector<T> &nums, T k)
{
    int n = nums.size();
    assert(n >= 2);
    T maxValue = numeric_limits<T>::min();
    int maxIndex, minIndex;
    maxIndex = minIndex = -1;
    for (int i = 0; i < n; ++i)
    {
        if (nums[i] > maxValue)
        {
            maxValue = nums[i];
            maxIndex = i;
        }
    }
    int j = maxIndex, i = (maxIndex + 1) % n;
    while (i != j) // is this right?
    {
        if (nums[i] + nums[j] == k) return true;
        else if (nums[i] + nums[j] > k) j = (j - 1 + n) % n;
        else i = (i + 1) % n;
    }
}

/*! \brief binary search with boundaries. */
template <typename T>
int binarySearch(const T *a, int low, int high, T target)
{
    assert(low <= high && low > 0); // only element contained is also valid.
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (a[mid] == target) return mid;
        else if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

template <typename T>
int binarySearchWithoutBound(const T *a, T target)
{
    int low, high; // int type is not a goog choice, maybe big number
    low = high = 1;
    while (a[high] < target) high = high << 1;
    if (a[high] == target) return high;
    low = high >> 1;
    return binarySearch(a, low, high, target);
}
 #endif
