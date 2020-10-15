#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;

typedef enum tagLogLevel
{
LOG_LEVEL_ERR,
LOG_LEVEL_INFO,
LOG_LEVEL_DBG,
LOG_LEVLE_ALL,
} LogLevel;

LogLevel gCurLoglevel = LOG_LEVLE_ALL;

#define LOG_D(fmt, ...)  do { if (gCurLoglevel >= LOG_LEVEL_DBG) fprintf(stdout,"[ DEBUG ] "fmt,##__VA_ARGS__ ); } while(0)
#define LOG_E(fmt, ...)  do { if (gCurLoglevel >= LOG_LEVEL_ERR) fprintf(stdout,"[ ERROR ] "fmt,##__VA_ARGS__ ); } while(0)
#define LOG_I(fmt, ...)  do { if (gCurLoglevel >= LOG_LEVEL_INFO) fprintf(stdout,"[ INFO ] "fmt,##__VA_ARGS__ ); } while(0)

#define MAX_WORD_LEN 128

int main()
{
	char key[MAX_WORD_LEN], word[MAX_WORD_LEN], PreKey[MAX_WORD_LEN];
	int  count = 0;
	strcpy(PreKey, "");  // PreKey[0] = 0
	while ((scanf("%s %s", key,word)) != EOF)
	{
		//the condition determine output newline or not.
		if ((strcmp(key, PreKey) != 0) && count > 0) 
		{
			printf("\n");  
		}
		strcpy(PreKey, key);
		count++;
		printf("%s ", word);		
	}
	printf("\n");
	return 0;
}

