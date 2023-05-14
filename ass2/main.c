#include <pthread.h>
#include <stdio.h>

#define d 2
#define m 4
#define s 1

void doRowShift(int* pMat) 
{
	int firstRow[m], i, j, k;
	// printf("%d \n",Mat[1][1]);
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

// void doColShift(int pMat) 
// {
// 	int lastCol[m], i, j, k;
// 	// printf("%d \n",Mat[1][1]);
// 	for (k=1; k<=s; k++) {
// 		for (i=0; i<m; i++)
// 			lastCol[i] = Mat[m-1][i];
// 		for (i=(m-1); i>=0; i--) {
// 			for (j=0; j<(m-1); j++)
// 				Mat[i][j] = Mat[i][j+1];
// 		}
// 		for (i=0; i<m; i++)
// 			Mat[i][m-1] = lastCol[i];
// 	}
// }

int main(int argc, char* argv[]) 
{
	int Mat[m][m] = {
    	{1,2,3,4},
    	{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16},
	};
	int* pMat = &Mat[0][0];
	doRowShift(pMat);
	// doColShift(Mat);
	for (int i=0; i<m; i++) {
		for (int j=0; j<m; j++)
    		printf("%d ", Mat[i][j]);
		printf("\n");
	}
	return 0;
}
