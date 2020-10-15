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

#include<cstdio>
#include<cassert>
#include<vector>
#include<iostream>
#include<fstream>
#include<stack>
 
using namespace std;
 
// Define this structure
// to implement Kruskal algorithms.
struct Edge
{
    int u, v, w;
    // Constructor
    Edge(int uu = 0, int vv = 0, int ww = 0)
    : u(uu), v(vv), w(ww) { }
};

struct UnionFind
{
public:
   struct SetElement
   {
        int rank, parent;

        // Constructor
        SetElement(int r = 0, int p = 0)
        :rank(r), parent(p) { }
   };

private:
    vector<SetElement> sets;

public:
   // Constructor
   UnionFind(int elements = 0) :sets(elements, SetElement()) { }

    // Find element's root in a 
    // tree structure.
    int find(int index) const
    {
        int parentIndex = sets[index].parent;
        if (sets[index].parent == index) return index;
        else find(parentIndex);
    }

    bool Union(int x, int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx == rooty) return false;
        if (sets[rootx].rank < sets[rooty].rank)
        {
            sets[rootx].parent = sets[rooty].parent;
        }
        else if (sets[rootx].rank > sets[rooty].rank)
        {
            sets[rooty].parent = sets[rootx].parent;
        }
        else
        {
            sets[rootx].parent = sets[rooty].parent;
            sets[rooty].rank++;
        }
        return true;
    }
};

class Graph
{
public:
    Graph(int vetexs = 0);  // Constructor

    void addEdge(int u, int v, int w = 1) // Add an edge to graph
    {
        mAdjList[u].push_back(v); 
        mEdgeSet.push_back(Edge(u, v, w));
        ++mEdges;
        // when constructing graph must specify vertex number.
    }

    void DFS(int s);  // Traversal graph by DFS from a given source s
    bool isConnected(int s, int d) const;
    
    // this implementation is definition
    // based. It's not an optimal one.
    bool isStronglyConnected() const
    {
        for (int i = 0; i < mVertex; ++i)
            for (int j = 0; j < mVertex; ++j)
                    if (!isConnected(i,j)) return false;
        return true;
    }

    /*! \brief M-Colouring problem.Return value indicate whether
        there is a feasible solution.If so, Store it in colours.
    */
    bool mColour(int m, vector<int> &colours);
    friend ostream& operator<<(ostream& os, const Graph &graph);
    friend istream& operator>>(istream& is, Graph &graph);
private:
    bool mColourHelper(int v, int m, vector<int> &colours);
    /*! \brief test colour is ok for vertex v */
    bool isColourOK(int v, int colour, const vector<int> &colours);

private:
    int mVertex, mEdges;    
    vector<vector<int>> mAdjList;    // adjacency vectors
    vector<Edge> mEdgeSet;
};
 
ostream& operator<<(ostream& os, const Graph &graph)
{
   os << "- Graph Info:" << std::endl;
   os << "- Vertex Number: " << graph.mVertex << std::endl;
   os << "- Edge Number: "   << graph.mEdges << std::endl;
   for (auto a : graph.mEdgeSet)
   {
        os << "- " << a.u << " " << a.v << " " << a.w << std::endl;
   }
   os << std::endl;
}

istream& operator>>(istream& is, Graph &graph)
{
    int edges;
    is >> graph.mVertex;
    is >> edges;
    vector<vector<int>> temp(graph.mVertex, vector<int>());    // adjacency vectors
    graph.mAdjList = temp;
    while (edges > 0)
    {
        int u, v, w;
        is >> u >> v >> w;
        graph.addEdge(u, v, w);
        --edges;
    }
}


Graph::Graph(int vertex)
: mVertex(vertex)
, mEdges(0)
, mAdjList(vertex, vector<int>())
, mEdgeSet()
{ }
 
bool Graph::isColourOK(int v, int colour, const vector<int> &colours)
{
    for (auto a : mAdjList[v])
    {
        if (colours[a] == colour) return false;
    }
    return true;
}

bool Graph::mColourHelper(int v, int m, vector<int> &colours)
{
    if (v == mVertex) return true; // all vertex coloured.
    for (int i = 0; i < m; ++i)
    {
        if (isColourOK(v, i, colours))
        {
            colours[i] = i;
            if (mColourHelper(v + 1, m, colours)) return false;
            colours[i] = -1; // not needed.
        }
    }
    return false;
}

bool Graph::mColour(int m, vector<int> &colours)
{
    return mColourHelper(0, m, colours);
}

void Graph::DFS(int s)
{
    assert(s >=0 && s < mVertex);
	vector<int> visited(mVertex,false);
	stack<int> stack;
    stack.push(s);
	visited[s] = true; // mark 
	while (!stack.empty())
	{
		int cur = stack.top(); stack.pop();

		cout << cur << " "; // ONLY access vertice from stack top
 
	    //vector<int>::iterator i;
        for (auto i = mAdjList[cur].begin(); i != mAdjList[cur].end(); ++i)
        {
            if (!visited[*i])
            {
                stack.push(*i);
                visited[*i] = true;
            }
        }
    }
}

bool Graph::isConnected(int s, int d) const
{
    assert( s>=0 && s < mVertex && d >= 0 && d < mVertex);
    if (s == d) return true; // default: a node connected to itself

	vector<int> visited(mVertex,false);
	stack<int> stack;
    stack.push(s);
	visited[s] = true; // mark 
	while (!stack.empty())
    {
		int cur = stack.top(); stack.pop();
        if (cur == d) return true; 
	    //vector<int>::iterator i;
        for (auto i = mAdjList[cur].begin(); i != mAdjList[cur].end(); ++i)
        {
            if (!visited[*i])
            {
                stack.push(*i);
                visited[*i] = true;
            }
        }
    }
    return false;
}
 
/*************************************************
 * Function: 
 *   
 * Param[in]:   
 * Param[out]:   
 *   
 * Retrun: 
 *   
 * Notice:   
*************************************************/
int main()
{
    Graph g(6);  //  6 vertices in graph
    /*
     *        0             5
     *     1     2
     *     3     4
     */
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 1);
    g.addEdge(2, 0);
    g.addEdge(2, 4);
    g.addEdge(4, 2);
 
    cout << g;

    cout << "Following is Depth First Traversal "
            "(starting from vertex 0) \n";
    g.DFS(0);
	cout << std::endl;

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            printf("Node %d ---> Node %d conneted? %d\n", i, j, g.isConnected(i, j));
        }
    }

    fstream test("graph.txt");
    Graph graph;
    test >> graph;
    cout << graph;

	return 0;
}
