
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

#include<cstdio>
#include<vector>
#include<deque>
#include<set>
#include <glog/logging.h>

using namespace std;

/************************************************************************************
 * Function:
 *   Given an array containing only 1 and 0, an integer m. Flip m 0s at most so that 
 *   number of consecutive 1s is maximized.
 *   
 * Param[in]:  nums array of '1' '0' 
 * Param[in]:  max number of flipping 0 to 1 
 *   
 * Retrun:
 *   "index vector* indicating which elements to flip.
 *   
 * Notice:   
 * Ideas:  sliding window.
************************************************************************************/
vector<int> flips(vector<int> &nums, int m)
{
	vector<int> ret;
	deque<int> que;
	int n = nums.size();
	int p = 0, q = 0;
	int zeros = 0;
	int widest = 0, width = 0;
	while (q < n)
	{
		//enlarge right side
		while (zeros <= m && q < n)
		{
			if (nums[q] == 0) que.push_back(q), ++zeros;
			++q;
		}

		//check and update
		if (q >= n)
		{
			while (!que.empty()) ret.push_back(que.front()), que.pop_front();
			return ret;
		}
		width = q - p;
		if (widest < width)
		{
			widest = width;
		}

		//shrink left side
		for (; p <= q && nums[p] != 0; ++p);
		if (nums[p] == 0) que.pop_front(), --zeros;
	}
	while (!que.empty()) ret.push_back(que.front()), que.pop_front();
	return ret;
}

/*************************************************
 * Function: reorder two array in asending order
 * array nums contains values while array index
 * contains corresponding index;
 * array 2 3 5 1
 * index 1 2 4 3
 *   
 * Param[in]: nums, value array  
 * Param[in]: index, index array 
 *   
 * Retrun: void 
 *   
 * Notice:   
*************************************************/
void reorderIndex(vector<int> &nums, vector<int> &index)
{
	int n = nums.size();
	if (n <= 1) return; //< no need to reorder
	for (int i = 0; i < n; i++)
	{
		while (index[i] != i) //disorder
		{
			int oldNum = nums[i];
			int oldIdx = index[i];
			nums[i] = nums[index[i]];
			index[i] = index[index[i]];
			nums[index[i]] = oldNum;
			index[index[i]] = oldIdx;
		}
	}
}

/***********************************************************************
 * Function:
 *   Given an integer array, find the number of strictly increased subarrays
 *   in that array.
 *   
 * Param[in]:  array, integer array 
 * Retrun:     int, subarray number  
 *   
 * Notice:   
***********************************************************************/
int NumberOfStrictlyIncreasedSubarrays(const vector<int> &array)
{
	int n = array.size();
	if (n <= 0) return 0;
	int ret = 0, len = 1, i;
	
	for (i = 0; i < n - 1; i++)
	{
		if (array[i + 1] > array[i])
			++len; 
		else
		{
			ret += len * (len + 1) / 2; len = 1;
		}
	}
	if (n > 1)
		ret += len * (len + 1) / 2;
	return ret;
}

/*********************************************************************
 * Function: 
 *   
 * Param[in]:   
 *   
 * Retrun: int, the length of longest increasing subsequence
 * Ideas:  
 * Notice:   
 * How to test it?
*********************************************************************/
int longestIncreasingSubsequence(const vector<int> &nums)
{
    int n = nums.size();
    if (n <= 0) return 0;
    int ret = 1;
    vector<int> subOpt(n, 1);

    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (nums[i] > nums[j] && subOpt[j] + 1 > subOpt[i])
            {    
                subOpt[i] = subOpt[j] + 1; 
                if (subOpt[i] > ret) ret = subOpt[i];
            }
        }
    }
    return ret;
}

/**************************************************************
 * Function:
 *   Given two sorted integer array, find all elements appears in both arrays.
 *   
 * Param[in]: array
 * Param[in]: array
 *   
 * Retrun: array, intersecting elements 
 * Ideas:  
 * Notice:  Two array must be sorted. 
**************************************************************/
vector<int> intersectOfSortedArray(const vector<int> &a, const vector<int> &b)
{
	vector<int> ret;
	int m = a.size(), n = b.size();
	int i, j;
	for (i = 0, j = 0; i < m && j < n;)
	{
		if (a[i] < b[j]) ++i;
		else if (a[i] > b[j]) ++j;
		else
		{
			ret.push_back(a[i]);	
			++i; ++j;
		}
	}
	return ret;
}

/************************************************************************************
* Function:
*   Given a mxn array, each cell of the array contains an integer number.
*   Caculcate the number of paths from left up to bottom right with constraint
*   that path sum equal to K
*
* Param[in]:
* Param[in]:
* Param[in]:
* Param[in]:
* Param[in]:
*
* Retrun: int, path number
* Ideas: Recursion on a matrix. Each move has two choices.
* Notice: Handle boundary.
* TODO: any better solutions ?
**************************************************************************************/
int pathNumberWithK(const vector<vector<int>> &a, int m, int n, int c, const int K)
{
    if (m < 0 || n < 0) return 0;
    if (m == 0 && n == 0)
    {
        if (c + a[m][n] == K) return 1; // !caution
        else return 0;
    }
    return pathNumberWithK(a, m - 1, n, c + a[m][n], K) +
        pathNumberWithK(a, m, n - 1, c + a[m][n], K);
}

template<typename T>
int AllPathOn2D(const std::vector<std::vector<T>>& a, int m, int n, std::vector<T> path, std::vector<std::vector<T>>& paths)
{
    if (m < 0 || n < 0) return 0; //< out of range
    if (m == 0 && n == 0)
    {
        path.emplace_back(a[0][0]);
        paths.emplace_back(path);
        return 1; // !caution
    }
    path.emplace_back(a[m][n]);
    return AllPathOn2D(a, m - 1, n, path, paths) +
        AllPathOn2D(a, m, n - 1, path, paths);
}

template<typename T>
int PathSumEquatoK(const T **a, int m, int n, int c, const int K)
{
    if (m < 0 || n < 0) return 0; //< out of range
    if (m == 0 && n == 0)
    {
        if (c + a[m][n] == K) return 1; // !caution
        else return 0; //< invalid
    }
    return PathSumEquatoK(a, m - 1, n, c + a[m][n], K) +
        PathSumEquatoK(a, m, n - 1, c + a[m][n], K);
}


/*********************************************************************************
 * Function:
 *
 * Param[in]:
 * Param[in]:
 *
 * Retrun: int, all possible coin change method
 * Ideas: I can apply tree structure to explain
 * my solution. 'money' as root, each edge has
 * a value corresponding to coins[i], a new node
 * is generated by substrabt current weight value
 * from current node, if the substrabtion is 0,
 * then you get a terminal node. the terminal
 * node number is result.
 *
 * Notice: The solutions has some defact. For
 * example, {4, [1, 2, 3]} as input. there are
 * <1, 1, 1, 1,> <1, 1, 2>, <2, 2>, <1, 3> totally
 * 4 methods.
 * But use the following solution, it gives 7 methods.
 * The additional methods are <3, 1>, <2, 1, 1> and
 * <1, 2, 1>
*********************************************************************************/
int coinChange(int money, const vector<int> &coins)
{
	if (money == 0) return 1; // !Caution money >= 0 is always true
	int num = 0;
	int n = coins.size();    // assume n > 0
	CHECK(n > 0);
	for (int i = 0; i < n; ++i)
	{
		if (coins[i] <= money)
		{
			num += coinChange(money - coins[i], coins);
		}
	}
	return num;
}

//< list all possible solutions: [1 1 5] and [5 1 1] are two solutions.
int coinChange2(int money, const vector<int> &coins, std::vector<int>& solution, std::vector<std::vector<int>>& solutions)
{
	if (money == 0)
	{
		solutions.push_back(solution);
		return 1; // !Caution money >= 0 is always true
	}

	int num = 0;
	for (int i = 0; i < coins.size(); ++i)
	{
		if (coins[i] <= money)
		{
			solution.push_back(coins[i]);
			num += coinChange2(money - coins[i], coins, solution, solutions);
			solution.pop_back();
		}
	}
	return num;
}

//< list all possible solutions: [1 1 5] and [5 1 1] are one solutions.
int coinChange3(int money, const vector<int> &coins, std::vector<int>& solution, std::vector<std::vector<int>>& solutions)
{
	if (money == 0)
	{
		solutions.push_back(solution);
		return 1; // !Caution money >= 0 is always true
	}

	int num = 0;
	for (int i = 0; i < coins.size(); ++i)
	{
		if (coins[i] <= money && (solution.size() > 0 ? coins[i] >= solution.back():true))
		{
			solution.push_back(coins[i]);
			num += coinChange3(money - coins[i], coins, solution, solutions);
			solution.pop_back();
		}
	}
	return num;
}

/*********************************************************************************
 * Function:
 *   Given a set, a vaue K, does exist a subset whose sum is equal to K ?
 *
 * This is a recursion solution
*********************************************************************************/
bool subsetSumEqualK(const vector<int> &nums, int K,  int index, int curSum, bool &found)
{
    if (index >= nums.size()) //< search end condition
    {
       if (curSum == K) found = true; // How about static local varible?
       return found;
    }

    return found || (subsetSumEqualK(nums, K, index + 1, curSum + nums[index], found)) ||
                    (subsetSumEqualK(nums, K, index + 1, curSum, found));
}
bool SubsetSumEqualK(const vector<int> &nums, int K)
{
	bool found = false;
	return subsetSumEqualK(nums, K, 0, 0, found);
}


/*********************************************************************************
 * Function:
 *   Caculate the suqare root of a perfect squre. if NOT a perfect square return -1. 
 *
 * This is a recursion solution
*********************************************************************************/
int SqrtOfPerfectSquare(int n)
{
	CHECK(n >= 0); // perfect squre >= 0
	int low = 0, high = n;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (mid * mid > n) high = mid - 1;
		else if (mid * mid < n) low = mid + 1;
		else return mid;
	}
	return -1; // n is not a perfect squre.
}

/*********************************************************************************
 * Function:
 *   count number of 1 in binary format of an integer number n 
 *
 * This is a recursion solution
*********************************************************************************/
int BitOnes(unsigned long n)
{
	int c = 0;
	while (n)
	{
		++c;
		n = n & (n - 1);
	}
	return c;
}

/*********************************************************************************
 * Function:
 *   get all permutation string of string str. duplidates should be removed. 
 *
 * It is a recursion solution
*********************************************************************************/
void PermutateStr(std::string str, int i, int j, std::set<string> &ret)
{
	if (str.empty()) //< NO need to permutation
		return;

    if (i == j) //< termination condition
    {
        ret.insert(str);
        return;
    }

	auto test = [&str, i ](int k)
	{
		if (str[i] == str[k]) return str;
		std::string temp = str;
		char c = temp[i];
		temp[i] = temp[k];
		temp[k] = c;
		return temp;
	};
        
    for (int k = i; k <= j; ++k)
    {
        PermutateStr(test(k), i + 1, j, ret);
    }
}

inline int LowestBitSet(unsigned long n)
{
    int bits = sizeof(n) * 8, i;
    for (i = 0; i < bits && !(n & (1 << i)); ++i);
    return i;
}

/*********************************************************************************
 * Function:
 *   an array of number, all number occur twice except one, find that number.
*********************************************************************************/
inline int UnpairNumber(const vector<int> &nums)
{
	int ret = 0;
	for (auto a : nums) ret ^= a;
	return ret;
}

/*********************************************************************************
 * Function:
 *   an array of number, all number occur twice except two, find the pair.
*********************************************************************************/
inline std::pair<int,int> UnpairNumbers(const vector<int> &nums)
{
	int ret = 0;
	for (auto a : nums) ret ^= a;
	ret = ret & (1 << LowestBitSet(ret));
	int x = 0;
	int y = 0;
	for (auto a : nums)
	{
		if (ret & a) x ^= a;
		else y ^= a;
	}
	return std::pair<int, int>{x,y};
}

//< 2's complement code
inline unsigned long IncreaseOne(unsigned long n)
{
	return -(~n);
}


/*************************************************
 * Binary Search Function
 * search 't' in data array 'a'
 * It is a very excellent algorithm.
*************************************************/
template <typename T>
int binSearch(T a[], int n, T t)
{
    CHECK(a != nullptr && n > 0);
    
    int l, u, m;
    l = -1; u = n;
    LOG(INFO) << "l = " << l << " u = " << u;
    while (l + 1 != u)
    {
        m = (l + u) / 2;
        LOG(INFO) << "m = " << m;
        if (a[m] < t)
        {    l = m; }
        else
        {    u = m; }
        LOG(INFO) << "l = " << l << " u = " << u;
    }
    int idx = u;
    if (idx >= n || a[idx] != t)
    {    
        LOG(INFO) << "Not Find target " << t;
        return -1;    
    }
    return idx;
}

#include "thirdparty/gtest/gtest.h"
#include<bitset>

TEST(Misc, BitOperations)
{
	std::bitset<32> bits;
	EXPECT_EQ(32, LowestBitSet(bits.to_ulong()));
	bits[6] = 1;
	EXPECT_EQ(6, LowestBitSet(bits.to_ulong()));

	std::vector<int>nums{1,1,2,2,3,3,9};
	EXPECT_EQ(9, UnpairNumber(nums));

	nums = {1,1,2,2,3,3,9,13};
	std::pair<int, int> expected{13,9};
	EXPECT_EQ(expected, UnpairNumbers(nums));

	EXPECT_EQ(11, IncreaseOne(10));
	EXPECT_EQ(1001, IncreaseOne(1000));
	EXPECT_EQ(899, IncreaseOne(898));
}

TEST(Misc, PermutateStr)
{
	std::string str{ "abc" };
	std::set<string> expected{"abc", "acb", "bac", "bca", "cba", "cab"};
	std::set<string> ret;
	PermutateStr(str, 0,2,ret);
	EXPECT_EQ(expected, ret);
}

TEST(Misc, BitOnes)
{
	std::bitset<32> bits;
	for (unsigned int i = 0; i < 32; ++i)
	{
		bits[i] = 1;
	    EXPECT_EQ(i+1, BitOnes(bits.to_ulong()));
	}
}

TEST(Misc, PerfectSqure)
{
	EXPECT_EQ(6, SqrtOfPerfectSquare(6*6));
	EXPECT_EQ(3, SqrtOfPerfectSquare(3*3));
	EXPECT_EQ(0, SqrtOfPerfectSquare(0*3));
	EXPECT_EQ(-1, SqrtOfPerfectSquare(5*3));
}

TEST(Recursion, SetSum)
{
	std::vector<int> set{1, -1, 2, 3, -2};
	EXPECT_EQ(true, SubsetSumEqualK(set, 6));
	EXPECT_EQ(false, SubsetSumEqualK(set, 7));
}

TEST(Recursion, CoinChange)
{
	std::vector<int> coins = {1, 5, 10};
	//std::vector<int> coins = {1, 5, };
	auto num = coinChange(3, coins);
	EXPECT_EQ(1, num);

	num = coinChange(5, coins);
	EXPECT_EQ(2, num);

	num = coinChange(6, coins);
	EXPECT_EQ(3, num);

	num = coinChange(7, coins);
	EXPECT_EQ(4, num);
}

TEST(Recursion, CoinChange2)
{
	std::vector<int> coins = {1, 5, 10};

	auto printSolution = [](int n, const std::vector<int>& item)
	{
		printf("-solution for %d: [", n);
		for (auto it = item.begin(); it != item.end(); ++it)
			printf("%d ", *it);
		printf("]\n");
	};

	std::vector<int> solution;
	std::vector<std::vector<int>> solutions;
    auto num = coinChange2(3, coins, solution, solutions);
	EXPECT_EQ(num, solutions.size());
	for (auto it = solutions.begin(); it != solutions.end(); ++it)
	{
		printSolution(3, *it);
	}
	solutions.clear();

    num = coinChange2(7, coins, solution, solutions);
	EXPECT_EQ(num, solutions.size());
	for (auto it = solutions.begin(); it != solutions.end(); ++it)
	{
		printSolution(7, *it);
	}
	solutions.clear();

    num = coinChange2(10, coins, solution, solutions);
	EXPECT_EQ(num, solutions.size());
	for (auto it = solutions.begin(); it != solutions.end(); ++it)
	{
		printSolution(10, *it);
	}
}

TEST(Recursion, CoinChange3)
{
	std::vector<int> coins = {1, 5, 10};

	auto printSolution = [](int n, const std::vector<int>& item)
	{
		printf("-solution for %d: [", n);
		for (auto it = item.begin(); it != item.end(); ++it)
			printf("%d ", *it);
		printf("]\n");
	};

	std::vector<int> solution;
	std::vector<std::vector<int>> solutions;
    auto num = coinChange3(7, coins, solution, solutions);
	EXPECT_EQ(num, solutions.size());
	for (auto it = solutions.begin(); it != solutions.end(); ++it)
	{
		printSolution(7, *it);
	}
	solutions.clear();

    num = coinChange3(10, coins, solution, solutions);
	EXPECT_EQ(num, solutions.size());
	for (auto it = solutions.begin(); it != solutions.end(); ++it)
	{
		printSolution(10, *it);
	}
}

TEST(PathOnGrid, AllPathOn2D)
{
    std::vector<std::vector<int>> a{ {1,2,3}, {4, 5, 6}, {7, 8, 9} };
    std::vector<int> path;
    std::vector<std::vector<int>> paths;

    auto n = AllPathOn2D<int>(a, 2, 2, path, paths);
    EXPECT_EQ(6, n);

}
