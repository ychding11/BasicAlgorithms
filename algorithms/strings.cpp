
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
#include<string>
#include<set>

using std::string;
using std::set;
using std::cout;
using std::endl;

// You are given a set<string> containing all of the words in the English
// language, all in lowercase.  Write a function that takes in a string prefix,
// then prints out all of the words in the set that have that string as
// a prefix.  However, if you iterate over an element of the set, you must
// print it out (that is, you can't just iterate over the set and print out
// words with the right prefixes.  You need to find a way to iterate over
// just those words with the right prefix)
/*************************************************
 * Function: 
 *   
 * Param[in]:  strs, STL set, string set. 
 * Param[in]:  prefix, string, the string prefix 
 * need to search.
 *   
 * Retrun: void 
 * Ideas:  
 *  The idea behind this solution is that for a given prefix,
    all words beginning with the prefix must come
    lexicographically after the prefix and before the prefix
    formed by increasing the last letter by one.
    For example,
    all words starting with "abd" come between "abd" and "abe."
 * Notice:  STL container set is a sorted container 
*************************************************/
void printStringsWithPrefix(const set<string> &strs, const string &prefix)
{
	if (prefix.empty()) // special case
	{ 
		// empty prefix matches all strings in the set
		for (auto it = strs.begin(); it != strs.end(); ++it)
			cout << *it << endl;
	}
	else // normal case
	{
		string stopPrefix = prefix; // start bound
		++stopPrefix[stopPrefix.length() - 1]; // ending bound
		for (auto it = strs.lower_bound(prefix); it != strs.lower_bound(stopPrefix); ++it)
			cout << *it << endl;
	}
}

/*! \brief find longest palindrome substring. */
string longestPalindromeSubstr(const string &str)
{
    if (str.empty()) return "";
    int n = str.size();
    int start = 0, end = 0;
    for (int i = 1; i < n; ++i)
    {
        int left = i - 1, right = i;
        while (left >= 0 && right < n && str[left] == str[right])
        {
            if (right - left > end - start)
            { start = left; end = right; }
            --left, ++right;
        }

        left = i - 1, right = i + 1;
        while (left >= 0 && right < n && str[left] == str[right])
        {
            if (right - left > end - start)
            { start = left; end = right; }
            --left, ++right;
        }
    }
    return str.substr(start, end - start + 1);
}

#if !defined(BUILD_LIB)
//This is just a test
int main()
{
	set<string> strs;
	strs.insert("abcdefg");
	strs.insert("abcdef");
	strs.insert("abcdeg");
	strs.insert("abcefg");
	strs.insert("bcdfg");
	strs.insert("bdfg");
	printStringsWithPrefix(strs, "abc");
    string str = "aaabaaa";
    std::cout << longestPalindromeSubstr(str) << std::endl;
}
#endif
