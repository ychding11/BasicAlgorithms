/*
 * recursion.cpp
 * demostrate recursion algorithms to solve some classic problems, such as
 * 8-queens.
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
#include <cassert>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*************************************************
 *  The class is to solver N Queens problem.
 *
 *  NOTE: max N supported is 32.
*************************************************/
class NQueensSolver 
{
private:
	// for example 4(0100) -- 3
	// an integer only 1 bit set in it's
	// binary format. The map stores 
	// <integer, corresponding bit index>
    map<int, int> columnMap;

private:
    bool checkPath(vector<int>& path)
    {
    	// check the new position is valid.
	// new position is represented by 
	// num2.
        int curRow = path.size() -1;
        int num2   = path[curRow];
        for(int i = 0; i < curRow; i++)
        {
            int num1    = path[i];
            int deltRow = curRow - i;
	    // use bit operation to check collision
            if(num2 & num1 || num2 & (num1 << deltRow) || num2 & (num1 >> deltRow)) return false;
        }
        return true;
    }

	// convert current solution into string format
    vector<string> path2Board( vector<int>& curPath)
    {
        int n = curPath.size();
        vector<string> ret(n, string(n, '.')); /* n == 0 is ok */
        for(int i = 0; i < n; ++i)
        {
            int col = columnMap[curPath[i]];  
            ret[i][col] = 'Q';
        }
        return ret;
    }

    /*********************************************************************
     * Function:
	 *   search NxN chessboard to find all possible solutions.
     *   
     * Param[in]:  n, int NxN chessboard 
     * Param[in]:  curRow, int currently searched row 
     * Param[out]: allPath, array all feasible solutions 
     * Param[out]: curPath, array current feasible solutions 
     *   
     * Retrun:void 
     * Ideas: search NxN chessboard with constrains. 
     * Notice:  How to check whether constrains are meet. 
    *********************************************************************/
    void solveNQueensHelper(vector<vector<string> >& allPath, vector<int>& curPath, int n, int curRow)
    {
        /* stop search condition */
        if(curRow == n)
		{
			allPath.push_back(path2Board(curPath));
			return;  
		}
        
        /* search column: each row search from 0 ==> n-1 */
        for(int j = 0; j < n; j++)
        {
            int curNum = 1 << j;
            curPath.push_back(curNum); /* test current column position */
            
            /* current path ok, search for next row */
            if(true == checkPath(curPath))  
            {
			    solveNQueensHelper(allPath, curPath, n, curRow + 1);
			}
            
            curPath.pop_back(); /* remove current column positon, test next column position */
        }
    }
    
public:  
    
    /***********************************************************************
     *  The public interface is to solver N Queens problem.
     *
     *  It returns all possible chessboard.
     *  chessboard is describled by a vector<string> while queen is represented by char 'Q'
     ***********************************************************************/
    vector<vector<string> > solveNQueens(int n) 
    {
        vector<vector<string> > allPaths;
        vector<int> curPath;
        for(int i = 0; i < n; ++i)
        { 
            columnMap[1 << i] = n-1-i;
        }
        solveNQueensHelper(allPaths, curPath, n, 0);
        
        return allPaths;
    }
};

/*************************************************
 * just call the demo string.
*************************************************/
int main(int argc, char** argv)
{
	int n;
	NQueensSolver solver;
	while (true)
	{
		cout << "Enter Queen Number:";
		cin >> n;
		if (-1 == n)
		{
			cout << "Game Over." << std::endl;
			return 0;
		}
		solver.solveNQueens(n);
	}
  
  return 0;
}

