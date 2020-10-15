/*
 * txtextractor.cpp
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
#include <cstring>
#include <string>
#include <map>
#include <ctime>
#include <cassert>
#include "Logger.h"

//using namespace std;

#define BUFSIZE 1024
#define LINE_TO_STRING(x) #x

#define DELIMETER "():.,'?-! \n;"

typedef enum tagLogLevel
{
LOG_LEVEL_ERR,
LOG_LEVEL_INFO,
LOG_LEVEL_DBG,
LOG_LEVEL_ALL,
} LogLevel;

LogLevel gCurLoglevel = LOG_LEVEL_ERR; //set the current log level

#define LOG_D(fmt, ...)  do { if (gCurLoglevel >= LOG_LEVEL_DBG)  fprintf(stdout, "[ debug ] "fmt,##__VA_ARGS__ ); } while(0)
#define LOG_E(fmt, ...)  do { if (gCurLoglevel >= LOG_LEVEL_ERR)  fprintf(stdout, "[ ERROR ] "fmt,##__VA_ARGS__ ); } while(0)
#define LOG_I(fmt, ...)  do { if (gCurLoglevel >= LOG_LEVEL_INFO) fprintf(stdout, "[ INFO ] "fmt,##__VA_ARGS__ ); } while(0)

char to_lowcase(char ch)
{
    if (ch >= 'a' && ch <= 'z') return ch;
    else if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 'a';
    else return -1;
}

/*************************************************
 *  count lines in a txt file.
 *  fgets takes newline ('\n') as a valid character 
 *  reference: 
 *  http://www.cplusplus.com/reference/cstdio/fgets/?kw=fgets
*************************************************/
static unsigned int count_line(char *filename)
{
    int lines = 0;
    char buf[BUFSIZE] = { 0 };
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (NULL == fp)
    {
        printf("Open [ %s ] error!  line:%d\n", filename, __LINE__);
        return -1;
    }
    while (fgets(buf, BUFSIZE, fp)) 
    {
        if ( strlen(buf) == BUFSIZE - 1 && 
             buf[BUFSIZE-2] != '\n')
        { /* do nothing , no new line in buffer */}
        else
        { lines++; }
    }
    return lines;
}

/*************************************************
 *  struct Hash node 
 *  used to count word frequency 
*************************************************/
typedef struct node
{
char *word;
int   count;
struct node *next;
} node;

#define NHASH 29989  // hash bucket number, a prime number
#define MULT 31      // used in hash function, prime number

node* bucket[NHASH]; // hash bucket

/*************************************************
 * Hash function: turn a string(word) into an  interger. 
 * The int used as an index to locate hash bucket.
*************************************************/
static unsigned int hash(char *str)
{
    assert(str != NULL);
    unsigned int n = 0;
    for (; *str; str++)
    { n = MULT * n + *str; }
    return n % NHASH;
}

/*************************************************
 * insert a word into hash bucket.
 * use linked list to solve confilicts.
 * NOTE: ensure no space in word.
 * what is different between 13 and '\n'
*************************************************/
void insert_word(char *word)
{
    assert(word != NULL);
    if (!*word || (*word == ' ') || (*word == 13)) //empty string || contains space or newline
    {
        logger << "Invalid word: <" << word << "> to insert." << std::endl;
        return;
    }
    node* p = NULL;
    int index = hash(word);
    for(p = bucket[index]; p != NULL; p = p->next)
    {
        if (strcmp(p->word, word) == 0) // word already in bucket
        {
            p->count++; 
            return;
        }
    }
    p = (node*)malloc(sizeof(struct node));
    p->count = 1;
    p->word = (char*)malloc(sizeof(word) + 1);
    strcpy(p->word, word);
    p->next = bucket[index]; //put new hash node into bucket.
    bucket[index] = p;
    logger << "Insert word: <" << word << "> (" << (int)*word << ") OK." << std::endl;
}

/*************************************************
 * read lines from stdin && count all world
 * and its frequency.
 * 
 * define world : strings seperated by blank
 *                regardless of actual meaning. 
*************************************************/
static void count_word_freq()
{    
    char buf[128];       /* supose longest world 127 character */
    memset(bucket, 0, sizeof(bucket)); /* clear Hash Bucket */
    while (scanf("%s", buf) != EOF)  
    {    
        insert_word(buf); 
    }
    for (int i = 0; i < NHASH; i++)
    {
        for (node *p = bucket[i]; p != NULL; p = p->next)
        { 
            //printf("%64s\t%d\n", p->word, p->count); //print word and its frequency
            printf("%64s\n", p->word); //print word only
        }
    }
}

/*************************************************
 * read lines from stdin && count all distinct words
 * and its frequency.
 * printf reference:
 * http://www.cplusplus.com/reference/cstdio/printf/?kw=printf
 *
 * NOTE: it can seperate word by delimeter defined
 *       by user.
*************************************************/
static void distinctWords()
{    
    ENTER_FUNCTION;
    char wordBuf[128];        /* longest world 127 character */
    char lineBuf[2048];       /* longest line 2047 character */
    int lines = 0;
    int words = 0;
    memset(bucket, 0, sizeof(bucket)); /* clear Hash Bucket */
    
    //read a line from stdin
    while (fgets(lineBuf, 2048, stdin) != NULL)
    {
        lines++;
        char *p = strtok(lineBuf, DELIMETER);
        while (NULL != p)
        {    
            logger << "Get word: " << p << std::endl;
            insert_word(p);
            p = strtok(NULL, DELIMETER);
        }
    }
    
    sprintf(lineBuf, "contains %d lines", lines);
    logger << lineBuf << std::endl;
    sprintf(lineBuf, "contains %d words", words);
    logger << lineBuf << std::endl;
    
    for (int i = 0; i < NHASH; i++)
    {
        for (node *p = bucket[i]; p != NULL; p = p->next)
        { 
            //sprintf(lineBuf, "%-32s\t%3d\n", p->word, p->count);
            //logger << lineBuf << std::endl;
            printf("%s\n", p->word);
            ++words;
        }
    }
    printf("%d\n", words);
    EXIT_FUNCTION;
}

/*************************************************
 *  count word frequency 
 *  take advantage of C++ STL std::map<string, int>
 *  element in the container is sorted. So it is different
 *  self-defined version.
 *  http://www.cplusplus.com/reference/map/map/operator[]/
 *   
*************************************************/
static void count_word_freq3()
{ 
    ENTER_FUNCTION;   
    char wordBuf[128];        /* longest world 127 character */
    char lineBuf[2048];       /* longest line 2047 character */
    int lines = 0, words = 0;
    std::map<std::string, int> mapTable;
    std::map<std::string, int>::iterator i;
    
    while (fgets(lineBuf, 2048, stdin) != NULL)
    {
        lines++;
        char *p = strtok(lineBuf, DELIMETER);
        while (NULL != p)
        {    
            words++;
            logger << "Get word: " << p << std::endl;
            mapTable[std::string(p)]++;
            p = strtok(NULL, DELIMETER);
        }
    }
    
    sprintf(lineBuf, "contains %d lines", lines);
    logger << lineBuf << std::endl;
    sprintf(lineBuf, "contains %d words", words);
    logger << lineBuf << std::endl;
    
    for ( i = mapTable.begin(); i != mapTable.end(); i++)
    {
       sprintf(lineBuf, "%-32s\t%3d\n", (i->first).c_str(), i->second);
       logger << lineBuf << std::endl;
    }
    
    EXIT_FUNCTION;
}

/* cat file | program */
int main(int argc, char** argv)
{
  logger.setLevel(DEBUG);
  logger.setLineLevel(INFO);
  ENTER_FUNCTION;
  
  distinctWords();
  
  EXIT_FUNCTION;
  return 0;
}

