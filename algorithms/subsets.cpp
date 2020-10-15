/*
 * subsets.cpp
 * demostrate recursion algorithms that how to generate all possible subsets
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
#include "Logger.h"

using namespace std;

#define PERFORMANCE_METER

/*************************************************
 *  The class is to generate subsets of a certain
 *  set.
*************************************************/
class SubsetsGen 
{
public:
    vector<vector<int> > subsets(vector<int>& nums) 
    {
        vector<vector<int> > ret;
        vector<int> temp;
        int n = nums.size();
        sort(nums.begin(), nums.end()); //assure subset is sorted.
        subsetsHelper(ret, temp, nums, 0, n);
        return ret;
    }
 
 private:   
    void subsetsHelper(vector<vector<int> > &ret, vector<int> temp, vector<int>& nums, int i, int n)
    {
        if (i >= n) { ret.push_back(temp); return; } // termination condition.
        
        subsetsHelper(ret, temp, nums, i + 1, n); //no elements selected and search.
        temp.push_back(nums[i]);  //select current elements and search.
        subsetsHelper(ret, temp, nums, i + 1, n);
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
/*************************************************
 * just call the demo string.
*************************************************/
int main(int argc, char** argv)
{
  logger.setLevel(DEBUG);
  logger.setLineLevel(DEBUG);
  ENTER_FUNCTION;
  
  int n;
  SubsetsGen generator;
  while (true)
  {
    cout << "Enter set size:";
    cin >> n;
    if (-1 == n)
    {
        cout << "Game Over." << std::endl;
        return 0;
    }
    vector<int> nums(n, 0);
    srand(time(NULL));
    cout << "Original vector: [ " ;
    for (int i = 0; i < n; i++)
    {
        nums[i] = rand() % 100;
        cout << nums[i] << " "; 
    }
    cout << "]" << std::endl;
    
    vector<vector<int> > ret = generator.subsets(nums);
    cout << "All possible subsets:" << std::endl; 
    printResult(ret);
  }
  
  EXIT_FUNCTION;
  return 0;
}

