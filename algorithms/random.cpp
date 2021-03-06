/*
 * random.cpp
 * a test data generator.
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
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <set>
#include <vector>
//#include "dataSource.h"

#if !defined(BUILD_LIB)
#include "Logger.h"
#endif

using namespace std;


#if defined(LOG_MACRO)

typedef enum tagLogLevel
{
LOG_LEVEL_ERR,
LOG_LEVEL_INFO,
LOG_LEVEL_DBG,
LOG_LEVEL_ALL,
} LogLevel;

LogLevel gCurLoglevel = LOG_LEVEL_ERR;

#define LOG_D(fmt, ...)  do{if (gCurLoglevel >= LOG_LEVEL_DBG) fprintf(stdout, " [ DEBUG ] " fmt,##__VA_ARGS__ ); }while(0)
#define LOG_E(fmt, ...)  do{if (gCurLoglevel >= LOG_LEVEL_ERR) fprintf(stdout, " [ ERROR ] " fmt,##__VA_ARGS__ ); }while(0)
#define LOG_I(fmt, ...)  do{if (gCurLoglevel >= LOG_LEVEL_INFO) fprintf(stdout, " [ INFO ] " fmt,##__VA_ARGS__ ); }while(0)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int DataType;
#endif

#if !defined(BUILD_LIB)

#define BUFSIZE 1024
#define LINE_TO_STRING(x) #x 
#define FILE_AND_LINE (__FILE__ ":" LINE_TO_STRING(__LINE__)) 

#define PERFORMANCE_METER
#define DATA_SET_SIZE (50 * 10000)

static int gRawDataSet[DATA_SET_SIZE];
static int gDataSetCount = 0;

/*************************************************
 *  generate the random integer numbers, put it to
 *  stdout. DATA_SET_SIZE is the number count.
 *   
 *  implementation: just call rand() in libc.
 *  rand(): Returns a pseudo-random integral number in the range  0 to RAND_MAX
 *  This number is generated by an algorithm that returns a sequence of 
 *  apparently non-related numbers each time it is called. 

 *  This algorithm uses a seed to generate the series, 
 *  which should be initialized to some distinctive 
 *  value using function srand.
 *  http://www.cplusplus.com/reference/cstdlib/rand/?kw=rand  
 *  for details.
*************************************************/
void gen_randint(void)
{   
   ENTER_FUNCTION;

   #ifdef PERFORMANCE_METER
   time_t tm1, tm2;
   time(&tm1); /* get current time */
   #endif
   
   for (int i = 0; i < DATA_SET_SIZE; i++ )
   {
      printf("%d ", rand());
   }
   printf("\n");
   
   #ifdef PERFORMANCE_METER
   time(&tm2);
   double seconds = difftime(tm2, tm1); /* return double */
   printf("[generate %d random integers time] = %.lf seconds!\n", DATA_SET_SIZE, seconds);
   #endif
   
   EXIT_FUNCTION;
}

/*************************************************
 *  generate m distinct sorted random numbers in 
 *  range [0, n). put the random numbers to stdout.
 *  stdout. 
 *   
 *  implementation: refer to "programming pearls".
*************************************************/
void gen_sorted_randint(int n, int m)
{
   ENTER_FUNCTION;
   
   #ifdef PERFORMANCE_METER
   time_t tm1, tm2;
   time(&tm1); /* get current time */
   #endif
        
   int i;
   for (i = 0; i < n; i++) //sorted number i from 0 to n - 1
   {   
      //determine whether to output i.      
      if (rand() % (n - i) < m) 
      {   
         m--;  printf("%4u ", i);      
      }
   }
   printf("\n");
   
   #ifdef PERFORMANCE_METER
   time(&tm2);
   double seconds = difftime(tm2, tm1); /* return double */
   printf("[generate %d sorted random integer time] %.lf s!\n", m, seconds);
   #endif
   
   EXIT_FUNCTION;
}
 
/*************************************************
 *  generate m distinct sorted random numbers in 
 *  range [0, n). put the random numbers to stdout.
 *  stdout. 2nd EDITION
 *   
 *  implementation: use std::set<int> container.
 *  std::set<int> only contains distinct and sorted
 *  elements.
 *
 *  the idea is clear but needs some extra space.
*************************************************/
void gen_sorted_randint2(int n, int m)
{
   ENTER_FUNCTION;
   
   set<int> s;
   
   #ifdef PERFORMANCE_METER
   time_t tm1, tm2;
   time(&tm1); /* get current time */
   #endif
   
   // insert m random integers into set
   while (s.size() < (unsigned int)m)
   {
      s.insert(rand() % n);
   }
   set<int>::iterator i;
   for (i = s.begin(); i != s.end(); i++)
   {
      printf("%d ", *i);
   }
   printf("\n"); 
   
   #ifdef PERFORMANCE_METER
   time(&tm2);
   double seconds = difftime(tm2, tm1); /* return double */
   printf("[generate %d sorted random integer time] %.lf s!\n", m, seconds);
   #endif  
   
   EXIT_FUNCTION;
}

static int bigrand()
{   
    return RAND_MAX*rand() + rand();
}

/*************************************************
 *  Generate n distinct unsorted random integer in 
 *  range [l, u] .
 *  
 *  algorithm idea: a simple math formular.
*************************************************/
int randint(int l, int u)
{   
    return l + rand() % (u-l+1);
}

/*************************************************
 *  Generate n distinct unsorted random integer in 
 *  range [0, n) .
 *  
 *  algorithm idea:
 *  1. generate n ordered and distinct number.
 *  2. distort n numbers randomly.
*************************************************/
void gen_distinct_randint(int n)
{
   ENTER_FUNCTION;
   
   #ifdef PERFORMANCE_METER
   time_t tm1, tm2;
   time(&tm1); /* get current time */
   #endif
   
   int i;
   for (i = 0; i < n; i++)
   {
      gRawDataSet[i] = i;
   }
   for (i = 0; i < n; i++)
   {
      int idx = randint(i, n - 1);    //printf("idx = %d \n", idx);
      int temp = gRawDataSet[idx];    //swap elements
      gRawDataSet[idx] = gRawDataSet[i];
      gRawDataSet[i]   = temp;
      printf("%d ", gRawDataSet[i]);
   }
   printf("\n");
   
   #ifdef PERFORMANCE_METER
   time(&tm2);
   double seconds = difftime(tm2, tm1); /* return double */
   printf("[generate %d unsorted random integer time] %.lf s!\n", n, seconds);
   #endif 
   
   EXIT_FUNCTION;
}

int main(int argc, char** argv)
{  
    logger.setLevel(DEBUG);
    logger.setLineLevel(DEBUG);
    ENTER_FUNCTION;
    
    int n = -1;
    int m = -1;
    if (argc > 3)
    {
        printf("Usage Error!\n"
              "%s [range] [count]\n"
              "range is the range of single random integer."
              "count is the number of generated random integer." , argv[0]); 
        return -1;
    }
    if (3 == argc)
    {   
        /* generate m sorted distinct integer,
         * range in [0, n) */
        n = atoi(argv[1]);
        m = atoi(argv[2]);
        logger << "m = " << m << " n = " << n << std::endl;
        srand(time(NULL)); /* initialize random seed */
        gen_sorted_randint2(n, m);
    }
    else if (2 == argc)
    {
        /* generate n unsorted distinct integer. */
        n = atoi(argv[1]);
        logger << " n = " << n << std::endl;
        srand(time(NULL)); /* initialize random seed */
        gen_distinct_randint(n);
    }
    else if (1 == argc)
    {
       /* generate random integer without range specified.
        * the count is  DATA_SET_SIZE , the maximum count. */
       srand(time(NULL)); /* initialize random seed */
       gen_randint();
    }
    
    EXIT_FUNCTION;
    return 0;
}
#endif

