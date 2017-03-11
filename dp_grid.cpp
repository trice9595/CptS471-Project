


class DP_Cell
{
	protected:
		int sScore;
		int iScore;
		int dScore;
		int matches = 0;
		int mismatches = 0;
		int openings = 0;
		int gaps = 0;

}

class DP_Grid
{
	friend class DP_Cell;

	int horizontal_length;
	int vertical_length;

	//get score function pointers
	int get_sScore(int i, int j){}
	int get_dScore(int i, int j){}
	int get_iScore(int i, int j){}

	//set score function pointers
	int set_sScore(int i, int j, int score){}
	int set_dScore(int i, int j, int score){}
	int set_iScore(int i, int j, int score){}

	//counter incrementers
	int setMatchCount(int i, int j, int score){}
	int setMismatchCount(int i, int j, int score){}
	int setContinuousGapCount(int i, int j, int score){}
	int setOpeningGapCount(int i, int j, int score){}

}

enum AlignmentType { none, local, global };

class Alignment
{
	DP_Grid grid;

	AlignmentType type = none;

	string horizontal_sequence;
	string vertical_sequence;
	string alignment_sequence;

	int horizontal_length;
	int vertical_length;
	int alignment_length;



}