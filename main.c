#include "global.h"
#include "input_output.c"
#include "grid.c"
#include "alignment.c"



//TODO
//optimize space usage
//local report differentiated from global
//print nucleotide count at end of each line


int main(int argc, const char* argv[])
{
	int i = 0, optimum;
	
	FILE* fp = stdout;

	readFile(argv[1]);

	printInput(fp);

	if(argv[3] != NULL)
	{
		readParams(argv[3]);
	}
	else
	{
		myParams.match = 1;
		myParams.mismatch = -2;
		myParams.opening = -5;
		myParams.continuation = -2;
	}


	if(strcmp(argv[2], "1") == 0)
	{
		printf("beginning local alignment...\n");
		optimum = smithWaterman();
		printOutput(fp);
		printLocalReport(fp, optimum);
	}
	else if(strcmp(argv[2], "0") == 0)
	{
		printf("beginning global alignment...\n");
		optimum = needlemanWunsch();
		printOutput(fp);
		printGlobalReport(fp, optimum);
	}
	else
	{
		return 0;
	}

	
	close(fp);

	return 0;
}

/*
a c g t a c
- - - - - -
| | | | | |
*/

