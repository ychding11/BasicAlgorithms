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
#include<stack>
#include<vector>
#include<climits>
#include<cstdio>
#include<deque>
#include<unordered_set> //only in c++11 or above

#include <glog/logging.h>

using namespace std;

template<typename T>
static T mymin(T a, T b)
{
	return a < b ? a : b;
}

template<typename T>
struct TTreeNode
{
	T val;
	TTreeNode *left, *right;
	TTreeNode(T v) : val(v), left(nullptr), right(nullptr) {}
};

typedef TTreeNode<int> TreeNode;

/*************************************************
 * Function: Given an integer sequence, judge whether
 * it is a valid pre-order traversal of BST.
 *   
 * Param[in]:  integer sequence	 
 *   
 * Retrun: bool value indicating valid or not 
 *   
 * Notice:   
 * Ideas:  use stack 
*************************************************/
bool isValidBSTpreOrderSequence (const vector<int> &seq)
{
	if (seq.empty()) return true; // empty tree case
	int rootVal = INT_MIN;
	stack<int> st;
	for (unsigned int i = 0; i < seq.size(); i++)
	{
		if (seq[i] < rootVal) return false;
		while (!st.empty() && st.top() < seq[i]) // eat right subtree node
		{
			rootVal = seq[i];
			st.pop();
		}
		st.push(seq[i]);
	}
	return true;
}

/************************************************************************
 * Function:
 *   For a node, print all its ancestors in BST.
 *   
 * Param[in]: root of a bst   
 * Param[in]: searched node 
 *   
 * Retrun: void 
 *   
 * Notice:  suppose the searched node is in root 
 * Ideas: use stack implement in-order traversal 
************************************************************************/
void printAncestors(TreeNode *root, TreeNode *e)
{
	if (!root || !e) return;
	stack<TreeNode*> st;
	while (true)
	{
		while (root && root->val != e->val)
		{
			st.push(root);
			root = root->left;
		}
		if (root && root->val == e->val) break; // simple case
		if (st.top()->right == NULL) //here, stack top elements has no left child
		{
			TreeNode *temp = st.top(); st.pop();
			while (!st.empty() && st.top()->right == temp)
			{
				temp = st.top(); st.pop();
			}

		}	
		root = st.empty()? NULL : st.top()->right;
	}
	//all elements in stack now are ancestors of searched node
	while (!st.empty()) 
	{
		printf("%d ", st.top()->val);
		st.pop();
	}
	printf("\n");
}

/**************************************************************************
 * Function:
 *   print elements in a binary tree in post order by iterative way.
 *   
 * Param[in]:  binary tree root 
 *   
 * Retrun: void
 *   
 * Notice:  implements iterative method by two stacks 
**************************************************************************/
void postOrderIterativeTraversal(TreeNode * root)
{
	if (!root) return;
	stack<TreeNode*> stk1, stk2;
	stk1.push(root);
	while (!stk1.empty())
	{
		TreeNode *temp = stk1.top(); stk1.pop();
		stk2.push(temp);
		if (temp->left) stk1.push(temp->left);
		if (temp->right) stk1.push(temp->right);
	}
	while (!stk2.empty())
	{
		printf("%d ", stk2.top()->val);
		stk2.pop();
	}
	printf("\n");
}

/**************************************************************************
 * Function: Judge whether a binary tree is complete
 *   
 * Param[in]:  root of binary tree 
 *   
 * Retrun: bool  
 *   
 * Ideas:  Define tree node with both left and right
 * child as a full node. In level order traversal,
 * once a non-full node is visited, all following
 * nodes should be leaf nodes for complete bianry
 * tree. we take this property to do the jugement.
 * 
 * Notice:  For a complete binary tree, a node has
 * no left child imply it has no right node.
**************************************************************************/
bool isCompleteBinaryTree(const TreeNode *root)
{
	if (!root) return true; // empty tree is complete
	bool noneFull = false;
	deque<const TreeNode*> que;
	que.push_back(root);
	// do "level order" traversal. It has some difference
	// with normal "level order".
	while (!que.empty())
	{
		const TreeNode *cur = que.front(); que.pop_front();
		if (!cur->left)
			noneFull = true;
		else
		{
			if (noneFull) return false;// seen non-full node before	
			que.push_back(cur->left);
		}
		if (!cur->right)
			noneFull = true;
		else
		{
			if (noneFull) return false;// seen non-full node before	
			que.push_back(cur->right);
		}
	}
	return true;
}

/********************************************************************
 * Function:
 *   Caculate given binary tree height by level order traversal.
 *   
 * Param[in]: root, the root node of binary tree 
 *   
 * Retrun: int, the height of bianry tree 
 *   
 * Ideas:   
 * Notice: How to tell different levels and
 * increase tree height.
********************************************************************/
int binaryTreeHeightByLevel(const TreeNode *root)
{
	int height = 0;
	if (!root) return 0;
	deque<const TreeNode*> que;
	que.push_back(root);
	que.push_back(NULL); // insert NULL to identify levels
	while (!que.empty())
	{
		const TreeNode *cur = que.front(); que.pop_front();
		if (cur == NULL)
		{
			++height;
			if (!que.empty()) que.push_back(NULL);
	    }
		else // ONLY non-null node enqueue.
		{
			if (cur->left) que.push_back(cur->left);
			if (cur->right) que.push_back(cur->right);
		}
	}
	return height;
}

/*******************************************************************************
 * Function:
 *   Given a binary search tree and two nodes v1 and v2,
 *   find the lowest commom ancestor node of v1 and v2.
 *   
 * Param[in]:  root, root node of BST 
 * Param[in]:  v1, BST node value  
 * Param[in]:  v2, BST node value 
 *   
 * Retrun: lowest common ancestor TreeNode 
 *   
 * Ideas:
 *  exploits property of BST. It's a recursion solution.
 * Assumption:
 *   The binary tree is BST, node v1, v2 be in the tree
*******************************************************************************/
const TreeNode* lowestCommAncestor(const TreeNode *root, int v1, int v2)
{
	if (!root) return nullptr;
	if (root->val > v1 && root->val > v2) return lowestCommAncestor(root->left, v1, v2);
	if (root->val < v1 && root->val < v2) return lowestCommAncestor(root->right, v1, v2);
	return root;
}

/*************************************************************************
 * Function: Calculate the minimum depth of binary tree.
 *
 * Define:
 *   minimum depth: number of nodes on the shortest path from root to leaf.
 *   
 * Param[in]:  root, root node of binary search tree 
 * Retrun:     minimum depth of binary tree. 
 *   
 * Notice: It's a recursive solution. 
 *     1
 *  2    
 *  The minimum depth of the above tree is 2 not 1.
 *
 * This solution perfectly demostrates the beauty of recursion.
*************************************************************************/
int minDepth(const TreeNode *root)
{
	if (!root) return 0;
	if (!root->left) return minDepth(root->right) + 1;
	if (!root->right) return minDepth(root->left) + 1;
	return mymin(minDepth(root->left), minDepth(root->right)) + 1;
}

/*************************************************
 * Function: Define queue item to solve top
 * view visible binary tree node set problem.
 *   
 * Notice:   
*************************************************/
struct queue_item
{
	const TreeNode* node;
	int horizonalDistance;
	queue_item(const TreeNode *nd, int hd) : node(nd), horizonalDistance(hd)
	{  }
};

/*************************************************
 * Function: Generate visible binary tree node set
 * when looking from top side.
 *   
 * Param[in]:root, the root node of binary tree. 
 *   
 * Retrun: binary tree node set visible from top side. 
 *   
 * Ideas:  Level order traversal. Define horizontal
 * distance to judge whether a node is visible from
 * top side, STL set<int> is to detect duplicate
 * horizonal distance. A node with duplicate horizontal 
 * distance is not visible from top side.
 * horizontal distance of root node is set to 0.
 * left child -1, right child +1.
 * Notice:   
*************************************************/
vector<const TreeNode*> topViewVisibleSet(const TreeNode *root)
{
	vector<const TreeNode*> ret;
	if (!root) return vector<const TreeNode*>();
	unordered_set<int> horizonalDistanceSet;
	deque<queue_item*> que;
	que.push_back(new queue_item(root, 0));
	while (!que.empty())
	{
		queue_item *cur = que.front(); que.pop_front();
		int hd = cur->horizonalDistance;
		const TreeNode *curNode = cur->node;
		// NOTE handle memory leak here
		if (horizonalDistanceSet.find(hd) == horizonalDistanceSet.end())
		{
			horizonalDistanceSet.insert(hd);
			ret.push_back(curNode);
		}

		if (curNode->left)
			que.push_back(new queue_item(curNode->left, hd - 1));
		if (curNode->right)
			que.push_back(new queue_item(curNode->right, hd + 1));
	}
	return ret;
}

/*************************************************
 * Function: in-order traversal 
 *   
 * Param[in]: root, root node of binay tree. 
 *   
 * Retrun: vector, in-order traversal sequence 
 *   
 * Notice:   
*************************************************/
vector<int> inOrderTraversal(const TreeNode *root)
{
	vector<int> ret;
	if (!root) return vector<int>();
	vector<int> lc = inOrderTraversal(root->left);
	ret.insert(ret.end(), lc.begin(), lc.end());
	ret.push_back(root->val);
	vector<int> rc = inOrderTraversal(root->right);
	ret.insert(ret.end(), rc.begin(), rc.end());
	return ret;
}

/*************************************************
 * Function: Post-order traversal 
 *   
 * Param[in]: root, root node of binary tree. 
 *   
 * Retrun: vector, post-order traversal sequence 
 *   
 * Notice:   
*************************************************/
vector<int> postOrderTraversal(const TreeNode *root)
{
	vector<int> ret;
	if (!root) return vector<int>();
	vector<int> lc = postOrderTraversal(root->left);
	ret.insert(ret.end(), lc.begin(), lc.end());
	vector<int> rc = postOrderTraversal(root->right);
	ret.insert(ret.end(), rc.begin(), rc.end());
	ret.push_back(root->val);
	return ret;
}

/**************************************************************************
 * Function: Determine whether sub is a  subarray of a.
 *   
 * Param[in]: a
 * Param[in]: sub 
 *   
 * Retrun: bool, indicating whether sub is a subarray of a.
**************************************************************************/
bool subArray(const vector<int> &a, const vector<int> &sub)
{
	int m = a.size(), n = sub.size();
	if (n > m) return false;
	int i, j;
	for (i = 0; i <= m -n; ++i)
	{
		for (j = 0; j < n; ++j)
			if (sub[j] != a[i + j]) break;
		if (j >= n) return true;
	}
	return false;
}

/***************************************************************************
 * Function: Determine whether binary tree root2 is a sub tree of binary tree root1.
 *   
 * Param[in]: root1   
 * Param[in]: root2
 *   
 * Retrun: bool, indicating whether root2 is a subtree
 * of root1.
 *   
 * Idea:
 *   1. binary tree root2 is a subtree of root1 imply the in-order traversal sequence is subarray 
 * of root1's in-order traversal sequence.
 *   2. rule 1 is true for post-order traversal sequence.
 * Notice:   
***************************************************************************/
bool isSubTree(const TreeNode *root1, const TreeNode *root2)
{
	vector<int> seq1, seq2;
	seq1 = inOrderTraversal(root1);
	seq2 = inOrderTraversal(root2);
	if (!subArray(seq1, seq2)) return false;
	seq1 = postOrderTraversal(root1);
	seq2 = postOrderTraversal(root2);
	if (!subArray(seq1, seq2)) return false;
	return true;
}

/******************************************************************
 * Function: Find the min distance in a binary tree. 
 * Item distance refers to from root node to leaf node.
 *   
 * Param[in]:  root, binary tree root 
 * Param[in]:  int, record current level 
 * Param[out]: int, min distance  
 *   
 * Retrun: void 
 * Ideas:  
 * Notice:   
******************************************************************/
void minDistance(const TreeNode *root, int level, int &minDist)
{
	if (!root) return;
	// check point && search end
	if (!root->left && !root->right && level < minDist) 
	{	minDist = level; return; }
	minDistance(root->left, level + 1, minDist);
	minDistance(root->right, level + 1, minDist);
}

/*************************************************
 * Function: 
 *   
 * Param[in]:   
 * Param[in]:   
 * Param[out]:   
 *   
 * Retrun: int, current node's level 
 * Idea: In binary tree root, define starting node's
 * level = 0. 
 * Notice:  For example search node 3 upward, mark level
 * value for each node.
 *    1(1)
 *   /  \
 *  2   3(0)
 *     /  \
 *    4   5
 *    /    \
 *   6     7 
 *   /      \
 *  8       9
*************************************************/
int minDistanceUpward(const TreeNode *root, const TreeNode *node, int &dist)
{
	if (!root) return -1;
	if (root == node) return 0;
	int level = minDistanceUpward(root->left, node, dist);
	if (level != -1) // node resides in current node's left subtree.
	{
		// search in current node's right subtree.
		minDistance(root->right, level + 2, dist); //!Caution, update right level
		return level + 1;
	}
	level = minDistanceUpward(root->right, node, dist);
	if (level != -1)
	{
		minDistance(root->left, level + 2, dist);
		return level + 1;
	}
	return -1;
}

/*************************************************
 * Function: Given a binary tree and a node in that
 * tree, find the closest distance to leaf from that
 * node.
 *   
 * Param[in]:  root, binary tree root 
 * Param[in]:  node, node in binary tree 
 *   
 * Retrun: int, min distance 
 *   
 * Notice: Search should have two directions:
 * 1. downward to leaf node
 * 2. upward to leaft node in other subtree.
*************************************************/
int minDistanceToLeaf(const TreeNode *root, const TreeNode *node)
{
	int ret = INT_MAX;
	minDistance(node, 0, ret);
	minDistanceUpward(root, node, ret);
	return ret;
}

/**************************************************************************
 * Function: Count single-valued subtrees in a  binary tree.
 *  "Single Valued subtree" only contains one value in subtree.
 *
 * Param[in]: root, root node of binary tree. 
 * Param[out]: count, single valued subtree number. 
 *   
 * Retrun: bool, indicating if the current tree is
 * a single valued binary tree.
 *   
 * Notice:  subtree number, a leaf node is a subtree.
 *    2
 *  2   2 
 *  A tree itself is also a subtree.
**************************************************************************/
bool isSingleValued(TreeNode *root, int &count)
{
	if (!root) return true;
	bool leftSingled = isSingleValued(root->left, count);
	bool rightSingled = isSingleValued(root->right, count);
	if (leftSingled == false || rightSingled == false) return false;
	if (root->left && root->val != root->left->val) return false;
	if (root->right && root->val != root->right->val) return false;
	++count; //< record the number of subtree until now
	return true;
}

/**************************************************************************
 * Function: Given two binary search tree, Print common 
 * nodes of two binary trees.
 *   
 * Param[in]:   
 * Param[in]:   
 *   
 * Retrun: void 
 * Ideas: Find intersect elements of two sorted 
 * array. Time Complexity is O(m + n) 
 * Notice: The idea is only suitable for BST 
**************************************************************************/
void printCommonNodeOfBinaryTree(const TreeNode *root1, const TreeNode *root2)
{
}

//< There is No need to check parameters
template<typename T>
TTreeNode<T>* buildBST(const T a[], int p, int q)
{
	if (p > q)  return nullptr;
	if (p == q) return new TTreeNode<T>(a[q]);
	int m = (p + q) / 2;
	TTreeNode<T> *root = new TTreeNode<T>(a[m]);

	root->left = buildBST(a, p, m - 1);
	root->right = buildBST(a, m + 1, q);
	return root;
}

template<typename T>
int  releaseBST(TTreeNode<T> *root)
{
	if (!root) return 0;
	int nl = releaseBST(root->left);
	int nr = releaseBST(root->right);
	delete root;
	return nl + nr + 1;
}

//< reverse Binary Search Tree
TreeNode *reverseBST(TreeNode *root)
{
	if (!root) return nullptr;
	TreeNode *lc = reverseBST(root->left);
	TreeNode *rc = reverseBST(root->right);
	root->left  = rc;
	root->right = lc;
	return root;
}

#include <algorithm>

//< function object to generate an ascending sequence 
template<typename T>
struct AscendingNumber 
{
	AscendingNumber() { current = 0; }

	//< make it a function object
	T operator()() { return current++; }
private:
	T current;
};

#include "thirdparty/gtest/gtest.h"

TEST(TreeTest, inTraversal)
{
	AscendingNumber<int>  numberGenerator;
	std::vector<int> testData(100);
	std::generate(testData.begin(), testData.end(), numberGenerator);
	auto sorted = std::is_sorted(testData.begin(), testData.end());
	EXPECT_EQ(true, sorted);

	TTreeNode<int> *root = buildBST(testData.data(), 0, testData.size()-1);
	std::vector<int> inSequence = inOrderTraversal(root);
	EXPECT_EQ(true, inSequence == testData);


	EXPECT_EQ(100, releaseBST(root)); //< release BST 
}

TEST(TreeTest, reverse)
{
	AscendingNumber<int>  numberGenerator;
	std::vector<int> testData(100);
	std::generate(testData.begin(), testData.end(), numberGenerator);
	auto sorted = std::is_sorted(testData.begin(), testData.end());
	EXPECT_EQ(true, sorted);

	TTreeNode<int> *root = buildBST(testData.data(), 0, testData.size()-1);

	reverse(testData.begin(), testData.end()); //< reverse test data
	std::vector<int> inSequenceReverse = inOrderTraversal(reverseBST(root));
	EXPECT_EQ(true, inSequenceReverse == testData);

	EXPECT_EQ(100, releaseBST(root)); //< release BST 
}

TEST(TreeTest, subarray)
{
	AscendingNumber<int>  numberGenerator;
	std::vector<int> testData(100);
	std::generate(testData.begin(), testData.end(), numberGenerator);
	auto sorted = std::is_sorted(testData.begin(), testData.end());
	EXPECT_EQ(true, sorted); //< test data is expected

	std::vector<int> subvec{testData.begin()+10, testData.begin()+50};
	EXPECT_EQ(true, search(testData.begin(), testData.end(), subvec.begin(), subvec.end())!= testData.end());
	EXPECT_EQ(true, subArray(testData,subvec));
	subvec.push_back(-1);
	EXPECT_EQ(false, search(testData.begin(), testData.end(), subvec.begin(), subvec.end())!= testData.end());
	EXPECT_EQ(false, subArray(testData,subvec));
	

}

#if 0
int main()
{
	AscendingNumber<int>  numberGenerator;
	std::vector<int> testData(100);
	std::generate(testData.begin(), testData.end(), numberGenerator);
	LOG(INFO) << std::is_sorted(testData.begin(), testData.end());

	TTreeNode<int> *root = buildBST(testData.data(), 0, testData.size()-1);
	std::vector<int> inSequence = inOrderTraversal(root);
	LOG(INFO) << (inSequence == testData);

	return 0;
}
#endif

