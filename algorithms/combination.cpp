/*
 * combination.cpp
 * demostrate recursion algorithms that how to generate all possible combinations
 * of a set.
 *
 * Source File
 *
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
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

#if !defined(BUILD_LIB)
#include "Logger.h"
#endif

using namespace std;

#define PERFORMANCE_METER

/*************************************************
 *  The class is to generate all possible
 *  combinations.
*************************************************/
class Combination
{
public:
    /*
     * Given a set of n elements [1, n], generate all
     * possible combinations of k elements from
     * the set.
     */
    vector<vector<int> > combine(int n, int k)
    {
        vector<vector<int> > result;
        vector<int> tmp;
        combineHelper(1, n, k, tmp, result);
        return result;  //call copy constrctor here.
    }

    void combineHelper(int begin, int end, int n, vector<int> &tmp, vector<vector<int> > &result)
    {
        /* search termination condition
         *  : we have picked n elements. */
        if (n == 0)
        {  result.push_back(tmp); return; }
        for (int i = begin; i <= end; i++)
        {
            tmp.push_back(i);
            combineHelper(i + 1, end, n - 1, tmp, result);
            tmp.pop_back();
        }
    }
};

void printResult(const vector<vector<int> > &ret)
{
    int m = ret.size();
    for (int i = 0; i < m; i++)
    {
        int n = ret[i].size();
        cout << "[ ";
        for (int j = 0; j < n; j++)
        {
            cout << ret[i][j] << " ";
        }
        cout << "]" << std::endl;
    }
}

#if !defined(BUILD_LIB)
/*************************************************
 * just a simple tesing
*************************************************/
int main(int argc, char** argv)
{
  logger.setLevel(DEBUG);
  logger.setLineLevel(DEBUG);
  ENTER_FUNCTION;

  int n, k;
  Combination cmb;
  while (true)
  {
    cout << "Enter set size and selected elements:";
    cin >> n >> k;
    if (-1 == n)
    {
        cout << "Game Over." << std::endl;
        return 0;
    }

    vector<vector<int> > ret = cmb.combine(n, k);
    cout << "All possible combinations:" << std::endl;
    printResult(ret);
  }

  EXIT_FUNCTION;
  return 0;
}
#endif

/*************************************************
 * Function: This is a helper function. it's a
 * recursive search for all possilbe subset sum.
 * And check whether requirements is meet.
 *
 * Param[in]:
 *
 * Retrun: min absolute value.
 * Ideas: traverse all possible subset recursively.
 * Notice:
*************************************************/
static int minSubsetDifferenceHelper(const vector<int> &nums, int sum, int subSum, unsigned int curIndex)
{
    // search end & calcuate two set's sum's difference absolute value
    if (curIndex == nums.size())
    {
        return abs((sum - subSum) - subSum);
    }
    return min(minSubsetDifferenceHelper(nums, sum, subSum + nums[curIndex], curIndex + 1),
               minSubsetDifferenceHelper(nums, sum, subSum, curIndex + 1));
}

/*************************************************
 * Function: Subset sum Problem. There is a
 * partition which make two subset difference's
 * absolute value minized.
 *
 * Param[in]:
 *
 * Retrun:
 * Ideas:
 * Notice:  It needs to calculate the sum.
*************************************************/
int minSubsetDifference(const vector<int> &nums)
{
   int sum = 0; //suppose int is enough for storing sum.
   for (unsigned int i = 0; i < nums.size(); ++i) sum += nums[i];
   // do actual search work here.
   return minSubsetDifferenceHelper(nums, sum, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Subset sum problem.  --Recursive solution. list all possible subset and check them one by one.
// NOTE: nums may contain both positive and nagetive numbers.
// if only positive numbs contained, the seach can be optimized.
bool subsetExistHelper(const vector<int> &nums, int targetSum, unsigned int index, int tempSum, bool &found);
bool subsetExist(const vector<int> &nums, int targetSum)
{
    if (nums.empty()) return false; // empty set has no subset.
    bool found = false;
    return subsetExistHelper(nums, targetSum, 0, 0, found);
}

bool subsetExistHelper(const vector<int> &nums, int targetSum, unsigned int index, int tempSum, bool &found)
{
    if (index >= nums.size())
    {
       if (tempSum == targetSum) found = true; // How about static local varible?
       return found;
    }

    return found || (subsetExistHelper(nums, targetSum, index + 1, tempSum + nums[index], found)) ||
                    (subsetExistHelper(nums, targetSum, index + 1, tempSum, found));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Coin Game.
//

int coinGameHelper(const vector<int> &coins, int start, int end);
int coinGame(const vector<int> &coins)
{
    int n = coins.size();
    return (n > 0 && !(n & 0x1)) && coinGameHelper(coins, 0, n - 1);
}

int coinGameHelper(const vector<int> &coins, int start, int end)
{
    if (start == end) return coins[start];
    if (start + 1 == end) return max(coins[start], coins[end]);
    return max( coins[start] + min(coinGameHelper(coins, start + 1, end - 1), coinGameHelper(coins, start + 2, end)),
                coins[end] + min(coinGameHelper(coins, start + 1, end - 1), coinGameHelper(coins, start, end - 2)));
}

/*! \brief how many binary trees are there for n nodes
 *  C(n) = C(0)C(n-1) + C(1)C(n-2) + ... + C(n-1)C(0)
 *  It's an Catalan number. see following link for details
 *  http://www.geeksforgeeks.org/applications-of-catalan-numbers/
 *  Cn = combine(2n, n) / (n + 1);
 *  Cn = (n + 2) / 2  * (n + 3) / 3 ... * (n + k) / k
 *  C0 = 1， C1 = 1;
 */
uint64_t catalanNumber(uint32_t n)
{
    if (n == 0 || n == 1) return 1;
    uint64_t a = 1, b = 1;
    for (uint32_t k = 2; k <= n; ++k)
    {
        a *= n + k; b *= k;
    }
    return a / b;
}
