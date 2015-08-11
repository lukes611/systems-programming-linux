#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <math.h>








int readline(char * line, int max)
{
	int c = 0;
	char ch;

	scanf("%c", &ch);
	while(1)
	{
		scanf("%c", &ch);
		if(ch == '\n')
		{
			line[c] = '\0';
			break;
		}
		line[c] = ch;
		c++;
	}
	return c;
}

int strTok(char * s, char delim, char* toks[], int max_toks)
{
	int phase = 0;
	int c = 0;
	int bc = 0;
	while(1)
	{
		char ch = s[c];
		if(phase == 0)
		{
			toks[bc] = &s[c];
			phase = 1;
			bc++;
			if(bc == max_toks) break;
		}else if(ch == delim)
		{
			s[c] = '\0';
			phase = 0;
		}else if(ch == '\0')
		{
			break;
		}
		c++;
	}
	return bc;
}

int intCmpA(const void * p1, const void * p2)
{
	int p1i = *((int * ) p1);
	int p2i = *((int * ) p2);
	if(p1i <= p2i)
	{
		return 1;
	}
	return 0;
}

int main()
{
	char line[1000];
	printf("enter a list of integers separated by a space bar: ");
	readline(line, 1000);
	printf("you entered: %s\n", line);
	char * toks[200];

	int ne = strTok(line, ' ', toks, 200);
	int * ints = new int[ne];
	for(int i = 0; i < ne; i++)
	{
		int n = atoi(toks[i]);
		ints[i] = n;
	}

	qsort((void*) ints, ne, sizeof(int), &intCmpA);
	printf("values:");
	int sum = 0;
	for(int i = 0; i < ne; i++)
	{
		printf("% i +", ints[i]);
		sum += ints[i];
	}
	printf("\b = %i\n", sum);
	delete [] ints;
	return 0;
}
