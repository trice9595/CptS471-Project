
//compares letters and returns if they are a match or not
int getMatchScore(char a, char b)
{
	if(a == b)
	{
		return myParams.match;
	}
	else
	{
		return myParams.mismatch;
	}
}

int getMaxScore(int sScore, int iScore, int dScore)
{
	if(sScore >= iScore && sScore >= dScore)
	{
		return sScore;
	}
	else if(dScore >= iScore && dScore >= sScore)
	{
		return dScore;
	}
	else if(iScore >= sScore && iScore >= dScore)
	{
			return iScore;
	}
}

int S(int i, int j)
{
	int matchScore = 0, sScore = 0, iScore = 0, dScore = 0, max = -1;

	//check for max!!!
	
	if(i >= 1 && j >= 1)
	{
		matchScore = getMatchScore(sequences[HORIZONTAL_SEQUENCE][i - 1], sequences[VERTICAL_SEQUENCE][j - 1]);
		
		sScore = myGrid[i - 1][j - 1].s + matchScore;
		iScore = myGrid[i - 1][j - 1].i + matchScore;
		dScore = myGrid[i - 1][j - 1].d + matchScore;


		max = getMaxScore(sScore, iScore, dScore);

		if(max < 0 && localComparisons)
			return 0;
	
		return max;
	}
	//if cell reference is out of range
	else
	{
		return NEGATIVE_INFINITY;
	}
}

int D(int i, int j)
{
	int sScore, iScore, dScore;
	//check for max!!!
	if(i >= 0 && j >= 1)
	{
		sScore = myGrid[i][j - 1].s + myParams.opening + myParams.continuation;
		iScore = myGrid[i][j - 1].i + myParams.opening + myParams.continuation;
		dScore = myGrid[i][j - 1].d + myParams.continuation;
		

		return getMaxScore(sScore, iScore, dScore);
			
	}
	else
	{
		return NEGATIVE_INFINITY;
	}


}

int I(int i, int j)
{
	int sScore, iScore, dScore;
	//check for max!!!
	if(i >= 1 && j >= 0)
	{

		//
		sScore = myGrid[i - 1][j].s + myParams.opening + myParams.continuation;
		iScore = myGrid[i - 1][j].i + myParams.continuation;
		dScore = myGrid[i - 1][j].d + myParams.opening + myParams.continuation;

		return getMaxScore(sScore, iScore, dScore);

	}
	else
	{
		return NEGATIVE_INFINITY;
	}

		
}

int initializeGridSW()
{
	int i = 0, j = 0;
	
	printf("initializing grid...\n");
	
	
	myGrid[0][0].s = 0;
	myGrid[0][0].i = 0;
	myGrid[0][0].d = 0;

	myGrid[0][0].ma = 0;
	myGrid[0][0].mi = 0; 
	myGrid[0][0].h = 0;
	myGrid[0][0].g = 0;  

	for(i = 1; i <= sequenceLength[HORIZONTAL_SEQUENCE]; i++)
	{
		//fill leftmost column
		myGrid[i][0].s = 0;
		myGrid[i][0].i = 0;
		myGrid[i][0].d = 0;


		myGrid[i][0].ma = 0;
		myGrid[i][0].mi = 0; 
		myGrid[i][0].h = 1;
		myGrid[i][0].g = i;  
	}
	
	for(j = 1; j <= sequenceLength[VERTICAL_SEQUENCE]; j++)
	{
		//fill topmost row
		myGrid[0][j].s = 0;
		myGrid[0][j].i = 0;
		myGrid[0][j].d = 0;


		myGrid[0][j].ma = 0;
		myGrid[0][j].mi = 0; 
		myGrid[0][j].h = 1;
		myGrid[0][j].g = j; 
	}
	
	return 1;
}

int initializeGridNW()
{
	int i = 0, j = 0;
	
	printf("initializing grid...\n");
	
	myGrid[0][0].s = 0;
	myGrid[0][0].i = 0;
	myGrid[0][0].d = 0;
	myGrid[0][0].ma = 0;
	myGrid[0][0].mi = 0; 
	myGrid[0][0].h = 0;
	myGrid[0][0].g = 0;  
	
	for(i = 1; i <= sequenceLength[HORIZONTAL_SEQUENCE]; i++)
	{
		//fill leftmost column
		myGrid[i][0].s = NEGATIVE_INFINITY;
		myGrid[i][0].i = myParams.opening + myParams.continuation*i;
		myGrid[i][0].d = NEGATIVE_INFINITY;

		myGrid[i][0].ma = 0;
		myGrid[i][0].mi = 0; 
		myGrid[i][0].h = 1;
		myGrid[i][0].g = i;  
	
	}
	
	for(j = 1; j <= sequenceLength[VERTICAL_SEQUENCE]; j++)
	{
		//fill topmost row
		myGrid[0][j].s = NEGATIVE_INFINITY;
		myGrid[0][j].i = NEGATIVE_INFINITY;
		myGrid[0][j].d = myParams.opening + myParams.continuation*j;


		myGrid[0][j].ma = 0;
		myGrid[0][j].mi = 0; 
		myGrid[0][j].h = 1;
		myGrid[0][j].g = j; 
	}
	
	return 1;
}


int globalOptimal()
{


	int sScore = myGrid[sequenceLength[HORIZONTAL_SEQUENCE]][sequenceLength[VERTICAL_SEQUENCE]].s;
	int iScore = myGrid[sequenceLength[HORIZONTAL_SEQUENCE]][sequenceLength[VERTICAL_SEQUENCE]].i;
	int dScore = myGrid[sequenceLength[HORIZONTAL_SEQUENCE]][sequenceLength[VERTICAL_SEQUENCE]].d;

	return getMaxScore(sScore, iScore, dScore);
}


//fills grid with s, d, and i values and returns optimal score
int fillGrid(int* maxI, int* maxJ)
{
	int sScore, iScore, dScore, j, i, maxScore = -1;

	printf("filling grid...\n");
	for(int i = 1; i <= sequenceLength[HORIZONTAL_SEQUENCE]; i++)
	{
		//printf("i - %d\n", i);
		for(int j = 1; j <= sequenceLength[VERTICAL_SEQUENCE]; j++)
		{
			myGrid[i][j].s = S(i, j);
			myGrid[i][j].i = I(i, j);
			myGrid[i][j].d = D(i, j);
			
			if(maxI != NULL && maxJ != NULL)
			{
				if(maxScore < myGrid[i][j].s)
				{
					maxScore = myGrid[i][j].s;
					*maxI = i;
					*maxJ = j;
				}
				if(maxScore < myGrid[i][j].i)
				{
					maxScore = myGrid[i][j].s;
					*maxI = i;
					*maxJ = j;
				}
				if(maxScore < myGrid[i][j].d)
				{
					maxScore = myGrid[i][j].s;
					*maxI = i;
					*maxJ = j;
				}
			}
		}
	}

	if(maxI != NULL && maxJ != NULL)
		return maxScore;
	else
		return globalOptimal();
	
}

int sMove(int* i, int* j)
{
	int alignmentPlace = sequenceLength[ALIGNMENT_SEQUENCE];
	if(sequences[HORIZONTAL_SEQUENCE][*i - 1] == sequences[VERTICAL_SEQUENCE][*j - 1])
	{

		sequences[ALIGNMENT_SEQUENCE][alignmentPlace] = 'm';
		matches++;
	}
	else
	{
		//printf("s | %c != %c\n", sequences[HORIZONTAL_SEQUENCE][i - 1], sequences[VERTICAL_SEQUENCE][j - 1]);
	
		sequences[ALIGNMENT_SEQUENCE][alignmentPlace] = 'x';
		mismatches++;
	}
	
	
	*i = *i - 1;
	*j = *j - 1;
	
}

int addGap(int *h, char gapType, char *prevMove)
{
	sequences[ALIGNMENT_SEQUENCE][sequenceLength[ALIGNMENT_SEQUENCE]] = gapType;
	
	gaps++;
	
	if(*prevMove != gapType)
		openings++;
	
	*h = *h - 1;
	
	*prevMove = gapType;
}

int retrace(int iStart, int jStart)
{
	int iScore, dScore, sScore, k = 0, openingNeeded = 0, prevScore = 0;
	int i = iStart;
	int j = jStart;
	char prevMove = '\0';
	
	int alignmentSequenceEnd;
	
	//alignment sequence length set to 0
	sequenceLength[ALIGNMENT_SEQUENCE] = -1;
	
	alignmentSequenceEnd = sequenceLength[HORIZONTAL_SEQUENCE] + sequenceLength[VERTICAL_SEQUENCE];
	
	sequences[ALIGNMENT_SEQUENCE][alignmentSequenceEnd + 1] = '\0';

	printf("retracing grid...\n");
	do{

	
		sScore = myGrid[i][j].s;
		iScore = myGrid[i][j].i;
		dScore = myGrid[i][j].d;
		

		sequenceLength[ALIGNMENT_SEQUENCE]++;
		
		//if dScore is best
		if(sScore >= dScore && sScore >= iScore) 
		{
			sMove(&i, &j);

			prevMove = 's';
			prevScore = sScore;

		}
		//if iScore is best
		else if(iScore >= sScore && iScore >= dScore)
		{
			//printf("i\n");
			addGap(&i, 'i', &prevMove);
			
			prevScore = iScore;
		}
		//if sScore is best
		else if(dScore >= sScore && dScore >= iScore)
		{
			//printf("d\n");
			addGap(&j, 'd', &prevMove);

			prevScore = dScore;
		}

		
		
		if(i == 0 && j == 0)
			break;

	}while(i >= 0 && j >= 0);
	
	
	return 1;
}

//only needed for testing
int get_num_digits(int x)
{
	int num_digits = 1, n = x;

	if(x < -9)
		return 3;

	if(x < 0)
		return 2;

	if(x < 10)
		return 1;

	if(x < 100)
		return 2;

	if(x < 1000)
		return 3;
}

void print_grid()
{
	int i = 0, j = 0, row = 0, num_spaces = 0, n = 0;
	char* spaces = "    ";


	for(j = 0; j <= sequenceLength[VERTICAL_SEQUENCE]; j++)
	{

		for(i = 0; i <= sequenceLength[HORIZONTAL_SEQUENCE] + 1; i++)
		{
			num_spaces = get_num_digits(i) + get_num_digits(j) - 2;
			printf("   %c      ", sequences[HORIZONTAL_SEQUENCE][i - 1]);
		}
		printf("\n");

		for(i = 0; i <= sequenceLength[HORIZONTAL_SEQUENCE]; i++)
		{
			num_spaces = get_num_digits(myGrid[i][j].s) - 1;
			printf("s%s%d    ", spaces + num_spaces, myGrid[i][j].s);
		}
		printf("\n");

		for(i = 0; i <= sequenceLength[HORIZONTAL_SEQUENCE]; i++)
		{
			num_spaces = get_num_digits(myGrid[i][j].i) - 1;
			printf("i%s%d    ", spaces + num_spaces, myGrid[i][j].i);
		}
		printf("\n");

		for(i = 0; i <= sequenceLength[HORIZONTAL_SEQUENCE]; i++)
		{
			num_spaces = get_num_digits(myGrid[i][j].d) - 1;
			printf("d%s%d    ", spaces + num_spaces, myGrid[i][j].d);
		}
		/*printf("\n");
		for(i = 0; i <= sequenceLength[HORIZONTAL_SEQUENCE]; i++)
		{
			printf("t%s%c    ", spaces, myGrid[i][j].t);
		}*/
		printf("\n");
		printf("\n");
	}
}

int needlemanWunsch()
{
	int globalOptimum, i = 0;
	
	localComparisons = false;
	
	makeGrid(sequenceLength[HORIZONTAL_SEQUENCE], sequenceLength[VERTICAL_SEQUENCE]);
	
	initializeGridNW();
	
	fillGrid(NULL, NULL);
	//print_grid();
	
	globalOptimum = globalOptimal();
	
	//add one for first empty row and columen
	retrace(sequenceLength[HORIZONTAL_SEQUENCE], sequenceLength[VERTICAL_SEQUENCE]);
	

	
	return globalOptimum;
}


int smithWaterman()
{
	int x = -1, y = -1;
	int* maxI = &x, *maxJ = &y;
	int localOptimum, i = 0;
	
	localComparisons = true;

	makeGrid(sequenceLength[HORIZONTAL_SEQUENCE], sequenceLength[VERTICAL_SEQUENCE]);
	
	initializeGridSW();
	
	localOptimum = fillGrid(maxI, maxJ);
	
	retrace(*maxI, *maxJ);



	
	localComparisons = false;
	
	return localOptimum;
}