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

#include<iostream>
#include<cstdio>
#include<vector>
#include<unordered_map> // only C++11 support

using namespace std;

/*************************************************
 * Function:  Given an array of integers, determine
 * whether it can be divided into groups and each 
 * group can be divide by k.
 *   
 * Param[in]:  array, integers
 * Param[in]:  int, dividor factor 
 *   
 * Retrun: bool value depending on whether it can 
 * be divided.
 *   
 * Notice: how about an empty number array ?   
 * Ideas: store reminder infomation and search in
 * second pass.
*************************************************/
bool canDivideGroupsByK(const vector<int>& nums, int k)
{
	int n = nums.size();
	// ?? {[1, 2, 3], 3} {[1, 2, 3], 6}
	if (n ^ 0x1) return false; //odd number cannot divide into groups
	unordered_map<int, int> reminderFreqs;
	for (int i = 0; i < n; i++)
	{
		reminderFreqs[nums[i] % k]++;
	}
	for (int i = 0; i < n; i++)
	{
		int rem = nums[i] % k;
		if (rem + rem == k)
		{
			if (reminderFreqs[rem] & 0x1) return false;
		}
		else
		{
			if (reminderFreqs[rem] != reminderFreqs[k - rem]) return false;
		}
	}
	return true;
}

/*************************************************
 * Function: Given an array of integers, try to 
 * find four elements a, b, c and d such that
 * a+b=c+d. The function determines whether such
 * four elemnts exist.
 *   
 * Param[in]: array, nums
 *   
 * Retrun: bool indicating whether pairs exist
 * Notice: Suppose no duplicates. [1, 2, 1] is 
 * an invalid input.
 * Ideas:  Loop all possible pairs and store<pair 
 * sum,pair itself> as an map entry. for each new
 * pair search its sum in map first, if got one such
 * four elements exist.
*************************************************/
bool arePairsExist(const vector<int> &nums)
{
	int n = nums.size();
	if (n < 4) return false; // rule out invalid vector
	unordered_map<int, pair<int, int>> map;
	for (int i = 0; i < n; i++) // loop possible pairs
	{
		for (int j = i + 1; j < n; j++)
		{
			int sum = nums[i] + nums[j];
			if (map.find(sum) == map.end())
			{
				map[sum] =  make_pair(i, j); // insert new map entry
			}
			else
			{
				printf("Found it (%d, %d) (%d, %d)\n", nums[i], nums[j], nums[map[sum].first], nums[map[sum].second]);
				return true;
			}
		}
	}
	return false;
}

/*************************************************
 * Function: Given an array of integers, find the
 * max length of subarray and the subarray's sum
 * equal to zero.
 *   
 * Param[in]:  array, nums  
 *   
 * Retrun: int, max length of subarray. 
 *   
 * Ideas:   
 * Notice:  how about sequence [-2 -1 0 1 2] 
 * ==> [-2, -3, -3, -2, 0] sum = 0 is a special
 * [1, 2, 0, 1, 2] ==> [1, 3, 3, 4, 6]
 * case.
*************************************************/
int maxLenOfSubarray(const vector<int> &nums)
{
	int n = nums.size();
	unordered_map<int, int> indexMap;
	int sum = 0, maxLen = 0;
	for (int i = 0; i < n; i++)
	{
		sum += nums[i];
		if (sum == 0) maxLen = i + 1; // no need to compare with maxLen
		else
		{
		    if (indexMap.find(sum) != indexMap.end())
		    	maxLen = (i- indexMap[sum]) > maxLen ? (i- indexMap[sum]) : maxLen ;
     		else
	     		indexMap[sum] = i;
		}

	}
	return maxLen;
}

/*************************************************
 * Function: Print all pairs in an integer array 
 * where pair sum equals to certain value.
 *   
 * Param[in]:  array, integers 
 * Param[in]:  int, pair sum 
 *   
 * Retrun: void 
 * Ideas: Store and Search, Hash to accelerate
 * Notice: Suppose no duplicates in array.
 * For example {[1 2 3 2], 5} is invalid.
*************************************************/
void printPair(const vector<int> &nums, int x)
{
	int n = nums.size();
	if (n < 2) return ;// no pair exists
	unordered_map<int, int> sumIdxMap;
	for(int i = 0; i < n; i++)
	{
		int temp = x - nums[i];
		if (sumIdxMap.find(temp) != sumIdxMap.end())
		{
			//got it
			printf("pair found: [%d, %d], <%d, %d>", 
					sumIdxMap[temp], i, temp, nums[i]);
			sumIdxMap.erase(temp);
		}
		else
		{
			sumIdxMap[nums[i]] = i;
		}
	}
}

/*************************************************
 * Function:Given an integer array and a window 
 * size k, sliding window from left to right each
 * time one element, count the number of distinct
 * numbers in window.
 *   
 * Param[in]: array, integer 
 * Param[in]: int, window size   
 *   
 * Retrun: vector,recording distinct number count 
 * in each window.
 *   
 * Notice:   
*************************************************/
vector<int> distinctCountInWindow(const vector<int> nums, int k)
{
	int count = 0;
	int n = nums.size();
	if (n < k) return vector<int>(); //no enough elements for window
	vector<int> ret;
	unordered_map<int,int> elementFreqs;
	for (int i =0; i < k; i++)	//set up first window
	{
		if (elementFreqs.find(nums[i]) == elementFreqs.end())
		{
			elementFreqs[nums[i]] = 1; 
			++count;
		}
		else
		{
			elementFreqs[nums[i]]++;
		}
	}
	ret.push_back(count);

	//sliding window 
	for (int i = k; i < n; i++)
	{
		// remove leftmost element in previous window
		// because of fixed window length, it is easy 
		int prv = nums[i - k];
		if (elementFreqs[prv] == 1)
		{
			--count;
			elementFreqs.erase(prv);
		}
		else
		{
			elementFreqs[prv]--;
		}

		//sliding window toward right 
		if (elementFreqs.find(nums[i]) == elementFreqs.end())
		{
			elementFreqs[nums[i]] = 1; 
			++count;
		}
		else
		{
			elementFreqs[nums[i]]++;
		}
	    ret.push_back(count);
	}
	return ret;
}

int main()
{
	return 0;
}
