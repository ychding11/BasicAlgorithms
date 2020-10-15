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
 
#include <vector>

using std::vector;

#define PERFORMANCE_METER

/*************************************************
 *  ListNode struct.
 *  NOTE: member variable is public.
*************************************************/
struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) { }
};

/*! \brief reverse list */
ListNode* reverseList(ListNode* head);
    
/*************************************************
    *  rotateRight. 
    *  example:
    *  1->2->3->4->5->NULL and k = 2.
    *  4->5->1->2->3->NULL.
	*  Idea: 
	*  1. find right cut point and glue two list part
	*     in new order.
	*  2. if k is large, it should mod list length n.
	*     so a very big k is valid.
*************************************************/
ListNode *rotateRight(ListNode *head, int k);
    
    /*************************************************
    *  removeNthFromEnd. 
    *  example:
    *  1->2->3->4->5->NULL and n = 2.
    *  1->2->3->5->NULL.
	*  It applys trick that get Nth node from List End.
*************************************************/
ListNode* removeNthFromEnd(ListNode* head, int n);

/*! \brief  Helper function contruct a linked list from a vector.
*  Constructed list order is reversed.
*/
ListNode* constructList(const vector<int> &nums);

/*************************************************
*  Helper function
*  destruct a linked list from a vector.
*  NOTE: list order is reversed.
*  SUPPOSE all list Node is allocated by new operator.
*************************************************/
uint32_t destructList(ListNode *head);

/*************************************************
*  Tester function
*  reverseList algorithm tester.
*  param: n number of elements
*************************************************/
bool reverseListTester(int n);
