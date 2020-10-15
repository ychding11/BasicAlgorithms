
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

using std::cout;
using std::cin;
using std::endl;

/*************************************************
 Write a program that prompts the user for an integer,
 then prints the numbers from 0 to that integer (inclusive).
 You cannot use the following keywords:
     if  else  do  while  goto  for  break  
     continue  switch  default  try  throw  catch
 You also cannot use setjmp and longjmp (if you know what these are).
 You also cannot use the ?: operator (it's essentially an 'if-else' statement). 

 * Ideas: apply rational operator  
 * Notice:  initial call to the function should be
 * printNumber(0, maxNum); && maxNum >= 0
*************************************************/
bool printNumber(int num, int maxNum)
{
	cout << num << endl;
	return (num >= maxNum || printNumber(num + 1, maxNum));
}

int main ()
{
	int maxNum;
	cout << "input a positive integer." << endl;
	cin >> maxNum;
	printNumber(0, maxNum);
}
