
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
#include<iostream>
#include<vector>
#include<climits>
#include<cfloat>
#include<cmath>
#include<cassert>
#include<limits>

using namespace std;

struct Point 
{
	int x;
	int y;
};

static double dist(Point pt1, Point pt2)
{
	return sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y));
}

float minDistanceHelper(const vector<Point> & points, int start, int end)
{
    assert(start <= end);
    if (start == end) return numeric_limits<float>::max();
    if (start + 1 == end)
        return sqrt((points[start].x - points[end].x) * (points[start].x - points[end].x) +
                    (points[start].y - points[end].y) * (points[start].y - points[end].y));

    int mid = (start + end) / 2;
    float d1 = minDistanceHelper(points, start, mid);
    float d2 = minDistanceHelper(points, mid + 1, end);
    float d = min(d1, d2);

    vector<Point> temp;
    for (int i = start; i <= mid; ++ i)
            if (abs(points[mid].x - points[i].x) <= d)
                temp.push_back(points[i]);
    for (int i = mid + 1; i <= end; ++ i)
            if (abs(points[mid].x - points[i].x) <= d)
                temp.push_back(points[i]);
    float minTemp = numeric_limits<float>::max();
    for (int i = 0; i < temp.size(); ++i)
    {
        for (int j = 0; j < temp.size(); ++j)
        {
            if (j == i) continue;
            float distij = dist(points[i], points[j]);
            if ( distij < minTemp)
                    minTemp = distij;
        }
    }
    return min(minTemp, d);
}

// Should be a generic one
float minDistance(const vector<Point> &points)
{
    assert(!points.empty() && points.size() > 1);
    if (points.size() == 2)
    {
        return sqrt((points[0].x - points[1].x) * (points[0].x - points[1].x) +
                    (points[0].y - points[1].y) * (points[0].y - points[1].y));
    }

    // Sort all points in X dimension.

    // Recursivly solve subproblems
    return minDistanceHelper(points, 0, points.size() - 1);
}

/*************************************************
 * Function: Given a two retangles on 2D plane, 
 * calculate whether these two retangles overlapped. 
 *   
 * Param[in]:  lt1, left top point of first rectangle 
 * Param[in]:  rb1, right bottom point of first rectangle 
 * Param[in]:  lt2, left top point of second rectangle 
 * Param[in]:  rb2, right bottom point of second rectangle 
 *   
 * Retrun: bool, indicating whether overlapped. 
 *   
 * Notice:   
 * Ideas:  two retangles do not overlapped if and 
 * only if one above another or one at left side of
 * another.
*************************************************/
bool isTwoRectangleOverlapped(Point &lt1, Point &rb1, Point &lt2, Point &rb2)
{
	if (lt1.y < rb2.y || lt2.y < rb1.y) return false; //one over another
	if (lt1.x > rb2.x || lt2.x > rb1.x) return false; //one at another's side
	return true;
}


static double triangleCost(vector<Point> &points, int i, int k, int j)
{
	double cost = 0.0;
	return dist(points[i], points[k])+dist(points[k], points[j])+dist(points[i], points[j]);
}

/*************************************************
 * Function: Given an array of points which stand 
 * for a polygon, we need to trianglize it.  
 *   
 * Param[in]:  points, array of 2D points 
 * Param[in]:  i, starting index of point array, included 
 * Param[in]:  j, ending index of point array, included 
 *   
 * Retrun: int, min cost of triangulation 
 *   
 * Notice:   
 * Ideas: recursive   
*************************************************/
double minTriangleCut(vector<Point> &points, int i, int j)
{
	if (j < i + 2) return 0; //less than 3 points
	double ret = DBL_MAX;
	for (int k = i + 1; k < j; ++k)
	{
		ret = (ret, minTriangleCut(points, i, k) + minTriangleCut(points, k, j) + triangleCost(points, i, k, j));
	}
	return ret;	
}

int main()
{
	return 0;
}
