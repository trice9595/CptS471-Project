//file for grid read, write functions

typedef struct
{
	int s;
	int i;
	int d;
	int ma = 0;
	int mi = 0;
	int h = 0;
	int g = 0;
}dp_cell;


typedef void (*cellReadFunc)(int i, int j);
typedef void (*cellWriteFunc)(int i, int j, int score);

typedef struct
{
	int horizontal_length;
	int vertical_length;

	//get score function pointers
	cellReadFunc get_sScore;
	cellReadFunc get_dScore;
	cellReadFunc get_iScore;

	//set score function pointers
	cellWriteFunc set_sScore;
	cellWriteFunc set_dScore;
	cellWriteFunc set_iScore;

	//counter incrementers
	cellWriteFunc setMatchCount;
	cellWriteFunc setMismatchCount;
	cellWriteFunc setContinuousGapCount;
	cellWriteFunc setOpeningGapCount;

	dp_cell** cells;
}matrix

typedef struct
{
	//string 1
	//string 2

	//string length 1
	//string length 2

	matrix scoreMatrix;


}stringAlignment

int cellIsInRange(int i, int j)
{
	if(matrix.cells != NULL && i < matrix.horizontal_length && j < matrix.vertical_length)
		return 1;
	else
		return 0;
}

//alloc grid function
int makeMatrix(int length1, int length2)
{
	int i = 0;


	if(matrix.cells == NULL)
	{
		matrix.cells = (dp_cell**)malloc(length1*sizeof(dp_cell*));
		for(i = 0; i < length1; i++)
			matrix.cells[i] = (dp_cell*)malloc(length2*sizeof(dp_cell));

		matrix.horizontal_length = length1;
		matrix.vertical_length = length2;

		return 1;
	}
	else
	{
		return -1;
	}
}

int deleteMatrix()
{
	int i = 0;

	if(matrix.cells != NULL)
	{
		for(i = 0; i < matrix.horizontal_length; i++)
			free(matrix.cells[i]);
		free(matrix.cells);

		matrix.horizontal_length = 0;
		matrix.vertical_length = 0;

		return 1;
	}
	else
	{
		return -1;
	}
}

int setMatrix_MatchCount(int i, int j, int count)
{


}


//get cell score functions
int getMatrix_sScore(int i, int j)
{
	if(cellIsInRange(i, j))
		return matrix.cells[i][j].s;
	else
	{
		printf("Invalid cell access\n");
		return NEGATIVE_INFINITY;
	}
}

int getMatrix_dScore(int i, int j)
{
	if(cellIsInRange(i, j))
		return matrix.cells[i][j].d;
	else
	{
		printf("Invalid cell access\n");
		return NEGATIVE_INFINITY;
	}
}

int getMatrix_iScore(int i, int j)
{
	if(cellIsInRange(i, j))
		return matrix.cells[i][j].i;
	else
	{
		printf("Invalid cell access\n");
		return NEGATIVE_INFINITY;
	}
}

//set cell score functions
int setMatrix_sScore(int i, int j, int score)
{
	if(cellIsInRange(i, j))
	{
		matrix.cells[i][j].s = score;
		return 1;
	}
	else
	{
		printf("Invalid cell access\n");
		return -1;
	}
}

int setMatrix_dScore(int i, int j, int score)
{
	if(cellIsInRange(i, j))
	{
		matrix.cells[i][j].d = score;
		return 1;
	}
	else
	{
		printf("Invalid cell access\n");
		return -1;
	}
}


int setMatrix_iScore(int i, int j, int score)
{
	if(cellIsInRange(i, j))
	{
		matrix.cells[i][j].i = score;
		return 1;
	}
	else
	{ 
		printf("Invalid cell access\n");
		return -1;
	}
}

