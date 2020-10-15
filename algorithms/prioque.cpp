/*
 * prioque.cpp
 *
 * Source File
 *
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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include "Logger.h"

#define PERFORMANCE_METER

typedef enum tagLogLevel
{
LOG_LEVEL_ERR,
LOG_LEVEL_INFO,
LOG_LEVEL_DBG,
LOG_LEVLE_ALL,
} LogLevel;

LogLevel gCurLoglevel = LOG_LEVLE_ALL;

#define LOG_D(fmt, ...)  do { if (gCurLoglevel >= LOG_LEVEL_DBG)  fprintf(stdout, "[ DEBUG ] "fmt,##__VA_ARGS__ ); } while(0)
#define LOG_E(fmt, ...)  do { if (gCurLoglevel >= LOG_LEVEL_ERR)  fprintf(stdout, "[ ERROR ] "fmt,##__VA_ARGS__ ); } while(0)
#define LOG_I(fmt, ...)  do { if (gCurLoglevel >= LOG_LEVEL_INFO) fprintf(stdout, "[ INFO ] "fmt,##__VA_ARGS__ ); } while(0)

#define DATA_SET_SIZE (1000 * 10000)

int gRawDataSet[DATA_SET_SIZE];
int gDataSetCount = 0;

void prepare_random_data()
{	
    ENTER_FUNCTION;
    
	#ifdef PERFORMANCE_METER
	time_t tm1, tm2;
	time(&tm1); /* get current time */
	#endif
	
	srand(time(NULL)); //rand seed
	for (int i = 0; i < DATA_SET_SIZE; i++ )
	{		
		gRawDataSet[i] = rand() % DATA_SET_SIZE;
	}
	
	#ifdef PERFORMANCE_METER
	time(&tm2);
	double seconds = difftime(tm2, tm1); /* return double */
	printf("[Prepare data time] = %.lf seconds!\n", seconds);
	#endif
	
	EXIT_FUNCTION;
}

template <class DataType>
bool is_sorted(DataType a[], int n)
{
	assert(a != NULL && n > 1);
	for (int i = 0; i < n - 1; i++)
	{	
	    if (a[i] > a[i + 1]) 
	    {
	        return false;
	    }
	}
	return true;
}

template <class DataType>
void display(DataType a[], int n)
{
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	for (int i = 0; i < n; i++)
	{
		if ((i) % 10 == 0) printf("+");
		printf("%4d ", a[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

/*************************************************
 *  priority queue  template.
 *  it is a MIN heap.
 *  implement two interfaces:
 *  1. insert().
 *  2. extract_min().
 *  NOTE: implementation in class definition will
 *        be regarded as inline function.
*************************************************/
template <class T>
class PriQueue
{
private:
	T *_p;
	int _n;
	int _maxsize;
	
private:
	void swap(int i, int j)
	{ T temp = _p[i]; _p[i] = _p[j]; _p[j] = temp;	}

public:
	PriQueue(int m)
	:_maxsize(m)
	, _n(0)
	{
	    _p = new T[_maxsize + 1]; //not very good. try{}catch()
	} /* heap sort : one extra space needed! */
	
	~PriQueue() 
	{ 
	    if (NULL != _p) delete []_p; 
	}
	
	void insert(T t)
	{
		int i, p;
		_p[++_n] = t; /* insert elements to tail, shift up to adjust the heap*/
		for (i = _n; i > 1 && _p[p = i / 2] > _p[i]; i = p) 
		{ 
		    swap(p, i); 
		}
	}
	
	T extract_min()
	{
		int i, c;
		T t = _p[1];
		_p[1] = _p[_n--]; /* 1. remove the min element in _p[1], 2. replace it with elements in tail, shit down to adjust */
		for (i = 1; (c = 2 * i) <= _n; i = c)
		{
			if ( (c + 1) <= _n && _p[c + 1] < _p[c]) c++;
			if ( _p[i] < _p[c]) break;
			swap(i, c);
		}
		return t;
	}
};

/* use template in template, */
template <class T>
static void prioque_sort(T a[], int m)
{
	ENTER_FUNCTION;
	PriQueue<T> prique(m); //use template.
	
	#ifdef PERFORMANCE_METER
	clock_t clk1, clk2;
	clk1 = clock(); /* get current clcok ticks elapsed since epoch */
	#endif

	for (int j = 0; j < m; j++)
	{	
		prique.insert(a[j]); 
	}
	for (int j = 0; j < m; j++)
	{	
		a[j] = prique.extract_min(); 
	}

	#ifdef PERFORMANCE_METER
	clk2 = clock();
	float seconds = ((float)(clk2 - clk1)) / CLOCKS_PER_SEC; /* calculate in seconds units */
	printf("[Sort time] = %ld ticks, %.4f seconds!\tsort %d elements!\n", clk2 - clk1, seconds, m);
	#endif

	EXIT_FUNCTION;	
}

int main(int argc, char** argv)
{
    logger.setLevel(DEBUG);
    logger.setLineLevel(INFO);
    ENTER_FUNCTION;
    
  	int m, n;
  	if (argc != 3)
  	{
        printf("Usage Error!\n""%s [input size]  [test count]\n", argv[0]); 
   	 	return -1;
 	 }
	m = atoi(argv[1]);  /* input count*/
	n = atoi(argv[2]);  /* test iterations */
	
	logger << "m = " << m << "n = " << n << std::endl;
    if (m < 0 || n < 0) //bugs here.
    {
        printf("ERROR, input error. line : %d\n", __LINE__);
        return -2;
    }
	for (int i = 0; i < n; i++)
	{
		PriQueue<int> prique(m);
		prepare_random_data();
		//printf("Before\t Sorted ?  %d\n", is_sorted(gRawDataSet,m));
		//display(gRawDataSet,DATA_SET_SIZE);
		prioque_sort(gRawDataSet, m);
		if (true == is_sorted(gRawDataSet,m))
		{
		    printf("Algorithm correct.\n");
		}
		else
		{
		    printf("Algorithm incorrect.\n");
		}		
		//display(gRawDataSet,DATA_SET_SIZE);
		printf("===================== Test Case: %d Complete ======================\n", i);	
	}
    EXIT_FUNCTION;
    return 0;
}

