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
 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

#include <glog/logging.h>

#include "list.h"
#include "profiler.h"

using std::cin;
using std::cout;

//#define PERFORMANCE_METER

//#define ENTER_FUNCTION logger << ">>>>" << __FUNCTION__ << std::endl
//#define EXIT_FUNCTION  logger << "<<<<" << __FUNCTION__ << std::endl

#define ENTER_FUNCTION 
#define EXIT_FUNCTION 

/*************************************************
 *  ListAlgorithms class -- a collection of classic
 *  list algorithms.
 *  NOTE: .
*************************************************/
ListNode* reverseList(ListNode* head)
{
    if (!head || !head->next) //< empty node or single node 
    {
        return head;
    }
    ListNode tempHead(0), *hd = &tempHead;
    hd->next = NULL; //< it's not needed because of ListNode constructor
    while (head)
    {
        ListNode *cur = head; // operation order is important
        head = head->next;
        cur->next = hd->next;
        hd->next = cur;
    }
    return tempHead.next;
}
    
/**************************************************************
    *  rotateRight. 
    *  example:
    *  1->2->3->4->5->NULL and k = 2.
    *  4->5->1->2->3->NULL.
	*  Idea: 
	*  1. find cut point and glue two list parts in new order.
	*  2. if k is large, it should mod list length n. so a big k is valid.
**************************************************************/
ListNode *rotateRight(ListNode *head, int k) 
{
    again:  
    if (!head || !head->next || k <= 0) //check param
    {   return head;    }
        
    ListNode *p = head;
    int n = 0, m = k;
    while (p && m > 0) {    n++; p = p->next; m--; }
    if (p == NULL)     {    k = k % n; goto again; }
    if (m <= 0)
    {
        ListNode *cur = head, *ret = NULL;
        while (p && p->next) {  cur = cur->next; p = p->next; }
        ret = cur->next; cur->next = NULL; //find 'cut point' and cut
        if (p) p->next = head;
        return ret;
    }
}
    
/*************************************************
  *  removeNthFromEnd. 
  *  example:
  *  1->2->3->4->5->NULL and n = 2.
  *  1->2->3->5->NULL.
  *  It applys trick that get Nth node from List End.
*************************************************/
ListNode* removeNthFromEnd(ListNode* head, int n) 
{
    CHECK((head != nullptr) && (n > 0));
    ListNode *p, *q, *prv;
    p = q = head; prv = nullptr;
    int i = 0;
    for (i = 0; q && i < n; i++, q = q->next); //move n step from head-->tail
    if (!q && i < n)
    {
		LOG(ERROR) << "Error, Invalid Param n = " << n;
        return head;
    }
    while (q) //continue moving p && q start moving
    {   
        prv = p; p = p->next;  
        q = q->next; 
    }

	//< if parameter is valid, p pointer to node to delete
    if (!prv)
    { 
        ListNode *ret = p->next;
        delete p; /* delete Node p */
        return ret;
    }
    else 
    { 
        prv->next = p->next; 
        ListNode *temp = p; 
        delete temp; /* delete Node p*/
        return head;
    }
}

/************************************************************
 *  Helper function contruct a linked list from a vector.
 *  Constructed list order is reversed.
************************************************************/
ListNode* constructList(const vector<int> &nums)
{
    ListNode tempHead(0), *head = &tempHead;
    for (auto e : nums)
    {
        ListNode *temp = new ListNode(e);
        if (temp)
        {
            temp->next = head->next;
            head->next = temp;
        }
        else
        {
			LOG(FATAL) << "Out of memory.";
            return tempHead.next;
        }
    }
    return tempHead.next;
}

/************************************************************
 *  Helper function to destruct a linked list
 *  Return: num of element deleted.
 *  SUPPOSE: all list Node is allocated by new operator.
************************************************************/
uint32_t destructList(ListNode *head)
{
	uint32_t num = 0;
    while (head)
    {
        ListNode *cur = head;
        head = head->next;
        delete cur;
		++num;
    }
	return num;
}

/*************************************************
 *  Test function for Reverse List algorithm
 *  param: n  elements
*************************************************/
bool reverseListTester(int n)
{
    CHECK(n >= 0); // element number check

	core::CPUProfiler profiler("List reverse test");

	vector<int> nums(n, 0);
	srand(time(NULL)); //rand seed
	for (int i = 0; i < n; i++)
	{
		nums[i] = rand() % n;
	}
	ListNode *head = constructList(nums);

	//< check test data is in right order.
	int c = n - 1;
	ListNode *tempHead = head;
	while (tempHead)
	{
		if (tempHead->val != nums[c])
		{
			LOG(ERROR) << "Single List order is error.";
			return false;
		}
		tempHead = tempHead->next;
		--c;
	}
	CHECK(c == -1);

    ListNode *result = reverseList(head); 
    c = 0; tempHead = result;
    while (tempHead)
    {
        if (tempHead->val != nums[c])
        {
			LOG(ERROR) << "Reverse Algorithm is wrong. Element mismatch @index=" << c;
            return false;
        }
        tempHead = tempHead->next;
        ++c;
    }
	CHECK(c==n);
	CHECK(destructList(result) == n); // release memory
	LOG(ERROR) << "Reverse Algorithm is correct.";
	return true;
}

std::unordered_map<std::string, core::ProfilerEntry> core::CPUProfiler::ProfilerData;

//#if !defined(BUILD_LIBRARY)
/*************************************************
 * list algorithm tester.
*************************************************/
int main(int argc, char** argv)
{
  core::CPUProfiler::begin();

  ENTER_FUNCTION;

  int n;  //input size
  while (true)
  {
    cout << "Enter elements number:";
    cin >> n;
    if (0 >= n)
    {
        cout << "Game Over.";
		break;
    }
    reverseListTester(n);
  }
  EXIT_FUNCTION;
  auto report = core::CPUProfiler::end();
  LOG(INFO) << report;
  return 0;
}
//#endif
