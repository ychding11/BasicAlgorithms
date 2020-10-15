/*
 * topsort.cpp
 * demostrate directed graph algorithms such as toplogical sort
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
#include <deque>
#include <iostream>
#include "Logger.h"

using namespace std;

#define PERFORMANCE_METER

/*************************************************
 *  The class CourseJudge.
 *
 *  indegrees[] is the key info for toplogic sort.
 *  NOTE: it needs c++11 support.
*************************************************/
class CourseJudge 
{
public:
    /*************************************************
     *  apply toplogical sort to judge whether the
     *  course plan is possible.
     *  input param: numCourses
     *  input param: prerequisites, course dependency
     *               list. It's an edge in Graph.
	 *               Format: [first] <--- [second]
     *  NOTE: .
    *************************************************/
    bool canFinish(int numCourses, vector<pair<int, int> >& prerequisites) 
    {
        int n = numCourses;
        vector<int> indegrees(n, 0); //init all indegrees to zero.
        vector<vector<int> > adjlist(n, vector<int>(0));
        
        /* build adjlist and indegrees from prerequisites */
        for (auto a : prerequisites)
        {
            adjlist[a.second].push_back(a.first);
            indegrees[a.first]++;
        }
        
        //toplogical sort with the help of queue
        deque<int> que;
        for (int i = 0; i < n; i++) // pick all 0 indegrees node
        {
            if (indegrees[i] == 0) que.push_back(i);
        }
       
		// for example, such an input {3, [1-->2-->3-->2]}
        while (!que.empty()) // when queue empty, loop ends
        {
            int u = que.front(); que.pop_front();
            for (auto v : adjlist[u]) //update indgree vector
            {
                if (--indegrees[v] == 0) que.push_back(v);
            }
        }
        
        for (auto v : indegrees) // if no loop in graph, all node's indegree should be 0
        {
            if (v > 0) return false;
        }
        return true;
    }
};

/*************************************************
 * a simple tester.
 * 
 * NEED IMPROVE
*************************************************/
int main(int argc, char** argv)
{
  logger.setLevel(DEBUG);
  logger.setLineLevel(DEBUG);
  ENTER_FUNCTION;
  
  int n;
  CourseJudge solver;
  while (true)
  {
    cout << "Enter course number:";
    cin >> n;
    if (-1 == n)
    {
        cout << "Game Over." << std::endl;
        return 0;
    }
    vector<pair<int, int> > depends; //HOW TO BUILD LIST EFFICENTLY?
    solver.canFinish(n, depends);
  }
  
  EXIT_FUNCTION;
  return 0;
}

