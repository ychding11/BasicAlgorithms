
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

#include<iostream>
#include<vector>
#include<cassert>


namespace test
{

using std::vector;
using std::ostream;

#define printContainer(elements)   \
do {   \
    std::cout << "- " << #elements << " Elements: ";   \
    for (auto e : elements) std::cout << e << " ";  \
    std::cout << std::endl;   \
} while(0)

#define printTestName(name) \
{ \
    std::cout << "- Test " << #name << " Begins." << std::endl; \
}

#define printTestResult(success, fail) \
{ \
    std::cout << "- Test result : "    \
              << success << " cases success," \
              << fail << " cases fail." \
              << std::endl; \
}

#define printTestcaseResult(result, in, out, expect) \
{ \
    if (result) \
        std::cout << "- Testcase success.\n"; \
    else \
        std::cout << "- Testcase failed.\n"; \
    std::cout << "  input:\n  "; \
    in; \
    std::cout << "  output:\n  "; \
    out; \
    std::cout << "  expected:\n  "; \
    expect; \
    std::cout << "---------------\n"; \
}

template <typename T>
void printParam(T param)
{
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << param << "\n";
}

template <typename T, typename... Args>
void printParam(T param, Args... args)
{
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << param << " ";
    printParam(args...);
}

template <typename T>
ostream & operator<<(ostream &os, vector<T> nums)
{
    os << "vector elements: ";
    for (auto a : nums)
    {
        os << a << " ";
    }
    os << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// For subset problem test.
//

template<typename T>
void allSubsetSumHelper(const vector<T> &nums, unsigned int index, T tempSum, vector<T> &sums)
{
    if (index == nums.size()) { sums.push_back(tempSum); return; }
    allSubsetSumHelper(nums, index + 1, tempSum + nums[index], sums);
    allSubsetSumHelper(nums, index + 1, tempSum, sums);
}

template<typename T>
vector<T> allSubsetSum(const vector<T> &nums)
{
    vector<T> ret;
    allSubsetSumHelper(nums, 0, 0, ret);
    return ret;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T>
void reverseVector(vector<T> &nums, int i, int j)
{
    while (i < j)
    {
        T temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        ++i; --j;
    }
}

template<typename T>
void rotateRightByK(vector<T> &nums, int k)
{
    assert(k > 0);
    int n = nums.size();
    if (n <= 0 || k % n == 0) return;
    reverseVector(nums, 0, k - 1);
    reverseVector(nums, k, n - 1);
    reverseVector(nums, 0, n - 1);
}

}
