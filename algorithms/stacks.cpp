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

#include<string>
#include<cstdio>
#include<iostream>
#include<stack>
#include<vector>

using namespace std;

/*************************************************
 * Function: Given a string containing only '{' and
 * '}', calculate the min reversal number needed to
 * make brackets match.
 *   
 * Param[in]:  exp, string 
 *   
 * Retrun: int, min reversal count 
 *   
 * Notice:   
*************************************************/
int minReversalCount(const string& exp)
{
	int n = exp.length();
	if (n <= 0) return 0;
	if (n & 0x1) return -1; //only even length is valid
	stack<char> st;
	//remove matched brackets by stack
	for (int i = 0; i < n; i++)
	{
		if (!st.empty() && exp[i] == '}')
		{
			if (st.top() == '{')
				st.pop();
			else
				st.push(exp[i]);
		}
		else
		{
			st.push(exp[i]);
		}
	}

	// remaining elements in stack may be '}}{{', '}{{{' 
	// '}}}{'.
	int lefted = st.size(); // remaining number must be even.
	int m = 0;
	while (!st.empty())
	{
		if (st.top() == '{') ++m;
		st.pop();
	}
	return (lefted >> 1) + (m & 0x1);
}

/*************************************************
 * Function: Given stock price array, calculate 
 * span day number for each day's price.
 *   
 * Param[in]:  prices, stock price array 
 *   
 * Retrun: vecotr<int>, span day number for each 
 * price. span day, for example  [4 1 2 3] for price
 * 3 span day number is 3. stock prices <= current 
 *   
 * Notice:   
*************************************************/
vector<int> caculateStockSpan(const vector<int> &prices)
{
	int n = prices.size();
	if (n <= 0) return vector<int>();
	vector<int> spans(n, 1); //default value is 1
	stack<int> st; st.push(0);
	for (int i = 1; i < n; i++)
	{
		while (!st.empty() && prices[st.top()] <= prices[i])
		{
			st.pop();
		}
		spans[i] = st.empty() ? i + 1 : i - st.top();
		st.push(i);
	}
	return spans;
}

/*************************************************
 * Function: stub  
 *   
 * Param[in]:   
 *   
 * Retrun: 
 * Notice:   
*************************************************/
int main()
{
	string exp = "{{}{";
	printf("%d\n", minReversalCount(exp));
	return 0;
}
