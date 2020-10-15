/*
 * shortestpath.cpp
 * 1. use Dijkstra  single source shortest path algorithms.
 * 2. find the max shortest path, which is the time when whole 
 *    empire knows the message.
 * 
 *
 */
 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

#define MAXDIST  1000000  //define as infinit 

/*************************************************
 *  Find the max one in shortest paths from a single
 *  source to all other nodes in a connected Graph.
 *  
 *  Precondition: no negative edges in Graph.
 * 
 *  done[i] : record whether shortest time from capitol
 *            to ctiy i is caculated ok.
 *  dist[i] : recoard the calculated shortest time
 *            for city i.
 *  apply Dijkstra algorithms.
 *  time complexity is O(n*n)
*************************************************/
int minTime(vector<vector<int> > &a, int n)
{
    int ret = 0;
    vector<bool> done(n, false);
    vector<int>  dist(n, MAXDIST);
    dist[0] = 0;
    for (int j = 0; j < n; ++j)
    {
        //find the min path 
        int u = -1, minDist = MAXDIST;
        for (int i = 0; i < n; i++)
        {
            if (!done[i] && dist[i] < minDist)
            {
                u = i; minDist = dist[i];
            }
        }
        done[u] = true;
        
        if (dist[u] > ret) 
        {    ret = dist[u];  } //record max shortest path.
        
        //update
        for (int v = 0; v < n; v++)
        {
            if (!done[v] && a[u][v] > 0 && dist[u] + a[u][v] < dist[v])
            {
                dist[v] = dist[u] + a[u][v];
            }
        }      
    }
    
    return ret;
}

int main()
{
	int n;
	scanf("%d", &n);
	if (n <= 0)
	{
	    printf("-1\n");
	    return 0;
	}
	if (n == 1) 
	{
	    printf("0\n");
	    return 0;
	}
	vector<vector<int> > matrix(n, vector<int>(n,0));
	for (int i = 1; i < n; i++)
	{
	    for (int j = 0; j < i; j++)
	    {
	        int w = 0;
	        char buf[32];
	        scanf("%s", buf);
	        if (strcmp("x", buf) == 0)
	        {
	            w = 0;
	        }
	        else
	        {   w = atoi(buf);
	        }
	        matrix[i][j] = w;
	        matrix[j][i] = w;
	        //cout << w << " "; //check input
	    }
	    cout << std::endl;
	}
	printf("%d\n", minTime(matrix,n));
	return 0;
}
