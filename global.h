#include <stdbool.h>
#include <math.h>

#define MAX_NAME_LENGTH 2048
#define MAX_SEQUENCE_LENGTH 65536

#define NEGATIVE_INFINITY -99//1147483647

#define HORIZONTAL_SEQUENCE 0
#define ALIGNMENT_SEQUENCE 1
#define VERTICAL_SEQUENCE 2

#define LINE_LENGTH 60


typedef struct
{
	int match;
	int mismatch;
	int opening;
	int continuation;
}params;


grid matrix;
params myParams; 
char sequences[3][MAX_SEQUENCE_LENGTH];
int sequenceLength[3];
char names[3][MAX_NAME_LENGTH];
int matches = 0;
int mismatches = 0;
int openings = 0;
int gaps = 0;

bool localComparisons = false;