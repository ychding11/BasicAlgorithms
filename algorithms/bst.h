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
#include <iostream>

using std::vector;
using std::cout;

#define PERFORMANCE_METER

template <typename T>
struct BstNode 
{
    T val;
    BstNode *left, *right;
    BstNode(T x) : val(x), left(NULL), right(NULL) { }
};

template <typename T>
class BstTree
{
private:
BstNode<T>* _root;

public:
BstTree(BstNode<T> *root = NULL) :_root(root) { }
BstTree(const BstTree<T> &rhs);
~BstTree() { }

BstTree* copy() const; // copy constructor
BstTree& operator=(const BstTree<T> &rhs);
bool insert(T elem);
bool remove(T elem);
bool remove(BstNode<T> *node);
BstNode<T>* find(T elem) const;
bool isIdentical(const BstTree<T> &rhs) const;
BstNode<T>* root() const { return _root; }

friend ostream& operator<<(ostream &os, const BstTree<T> &tree);

private:
bool isIdentical(const BstNode<T> *tree1, const BstNode<T> *tree2) const;
BstNode<T>* insert(T elem, BstNode<T> *root);
void printTree(BstNode<T> *root, ostream &os);
BstNode<T>* find(T elem, BstNode<T> *root) const;
BstNode<T>* preOderCopy(const BstNode<T> *root) const;
};

template <typename T>
bool BstTree<T>::isIdentical(const BstTree<T> &rhs) const
{
    return isIdentical(_root, rhs._root);
}

template <typename T>
bool BstTree<T>::isIdentical(const BstNode<T> *tree1, const BstNode<T> *tree2) const
{
    if (!tree1 && !tree2) return true;
    if ( (!tree1 && tree2) || (tree1 && !tree2) ) return false;
    if (isIdentical(tree1->left, tree2->left) && isIdentical(tree1->right, tree2->right))
        return tree1->val == tree2->val;
}

template <typename T>
BstTree<T>::BstTree(const BstTree<T> &rhs)
{
    _root = preOderCopy(rhs._root);
}
template <typename T>
BstNode<T>* BstTree<T>::preOderCopy(const BstNode<T> *root) const
{
   if (!root) return NULL;
   BstNode<T> *temp = new BstNode<T>(root->val);
   temp->left = preOderCopy(root->left);
   temp->right = preOderCopy(root->right);
   return temp;
}

template <typename T>
BstNode<T>* BstTree<T>::find(T elem) const
{
    return find(elem, _root);
}

template <typename T>
BstNode<T>* BstTree<T>::find(T elem, BstNode<T> *root) const
{
    if (!root) return NULL;
    if (root->val == elem) return root;
    else if (root->val < elem) return find(elem, root->right);
    else return find(elem, root->left);
}

template <typename T>
ostream& operator<<(ostream &os, const BstTree<T> &tree)
{
    printTree(tree._root, os);
    return os;
}

template <typename T>
void BstTree<T>::printTree(BstNode<T> *root, ostream &os)
{
    if (!root) return;
    printTree(root->left, os);
    os << root->val << std::endl;
    printTree(root->right, os);
}

template <typename T>
bool BstTree<T>::insert(T elem)
{
    _root = insert(elem, _root);
    return _root != NULL;
}

template <typename T>
BstNode<T>* BstTree<T>::insert(T elem, BstNode<T> *root)
{
    if (!root) return new BstNode<T>(elem);
    if (elem < _root->val)
    {
        BstNode *temp = insert(elem, _root->left);
        !temp ? return NULL; : _root->left = temp;
    }
    else if (elem > _root->val)
    {
        BstNode *temp = insert(elem, _root->right);
        !temp ? return NULL; : _root->right = temp;
    }
    else
    {
        return NULL; // already exist.
    }
    return root;
}

