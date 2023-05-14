#include <pthread.h>
#include <stdio.h>

#define d 2
#define m 4
#define s 1

int Mat[m][m] = {
    // {1,2,3,4},
    // {5,6,7,8},
	// {9,10,11,12},
	// {13,14,15,16},
	{7,6,5,3},
    {8,2,4,5},
	{7,3,1,9},
	{2,1,0,8},
};

void doRowShift() 
{
	int firstRow[m], i, j, k;
	for (k=1; k<=s; k++) {
		for (j=0; j<m; j++)
			firstRow[j] = Mat[0][j];
		for (j=0; j<m; j++) {
			for (i=0; i<(m-1); i++)
				Mat[i][j] = Mat[i+1][j];
		}
		for (j=0; j<m; j++)
			Mat[m-1][j] = firstRow[j];
	}
}

void doColShift() 
{
	int lastCol[m], i, j, k;
	for (k=1; k<=s; k++) {
		for (i=0; i<m; i++)
			lastCol[i] = Mat[i][m-1];
		for (i=0; i<m; i++) {
			for (j=(m-1); j>=1; j--)
				Mat[i][j] = Mat[i][j-1];
		}
		for (i=0; i<m; i++)
			Mat[i][0] = lastCol[i];
	}
}

int main(int argc, char* argv[]) 
{
	doRowShift();
	doColShift();
	for (int i=0; i<m; i++) {
		for (int j=0; j<m; j++)
    		printf("%d ", Mat[i][j]);
		printf("\n");
	}
	return 0;
}
