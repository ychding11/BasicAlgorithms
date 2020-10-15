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
 
#ifndef DATASOURCE_H_
#define DATASOURCE_H_

#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cassert>

using std::vector;
using std::set;

class DataSource
{
public:

#define DATASET_SIZE (10 * 10000)

    DataSource()
    {
       srand(time(NULL)); /* initialize random seed */
    }

    void updateRandSeed(void)
    {
       srand(time(NULL)); /* initialize random seed */
    }

    // 
    template<typename T>
    void fillInData(vector<T> &nums, int maxValue = RAND_MAX); //<cstdlib>

    template<typename T>
    void fillInDistinctData(vector<T> &nums, int maxValue = RAND_MAX); //<cstdlib>

    template<typename T>
    void fillInSortedData(vector<T> &nums, int maxValue = RAND_MAX);

    //
    template<typename T>
    vector<T> dataSetExlude(const set<T> &nums, int maxValue = RAND_MAX);
};
    template<typename T>
    void DataSource::fillInData(vector<T> &nums, int maxValue)
    {
       assert(!nums.empty()); 
       int n = nums.size();
       for (auto &a : nums)
       {
           a = rand() % maxValue; // rand() return integer
       }
    }
    
    template<typename T>
    void DataSource::fillInDistinctData(vector<T> &nums, int maxValue)
    {
       assert(!nums.empty()); 
       set<T> sets;
       int i = 0, n = nums.size();
       while (i < n)
       {
           int a = rand() % maxValue; // rand() return integer
           auto ret = sets.insert(a);
           if (ret.second == true) ++i;
       }
       i = 0;       
       for (auto a : sets)
       {
           nums[i++] = a;
       }
    }

    template<typename T>
    void DataSource::fillInSortedData(vector<T> &nums, int maxValue)
    {

    }

    template<typename T>
    vector<T> DataSource::dataSetExlude(const set<T> &nums, int maxValue)
    {
        assert(!nums.empty());
        const int n = nums.size();
        vector<T> ret(n, 0);
        int i = 0;
        while (i < n)
        {
            int temp = rand() % maxValue;
            auto it = nums.find(temp);
            if (it == nums.end()) // not found
            {
                ret[i++] = temp;
            }
        }
        return ret;
    }

#endif
