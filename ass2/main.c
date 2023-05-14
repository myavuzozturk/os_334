#include <pthread.h>
#include <stdio.h>

#define d 2
#define m 4
#define s 1

void doRowShift(int Mat[m][m]) {
	
	int firstRow[m], i, j, k;
	// printf("%d \n",Mat[1][1]);
	// for (i=1; i<=s; i++) {
		for (j=0; j<m; j++)
			firstRow[j] = Mat[0][j];
		for (j=0; j<m; j++) {
			for (k=0; k<(m-1); k++)
				Mat[k][j] = Mat[k+1][j];
		}
		for (j=0; j<m; j++)
			Mat[m-1][j] = firstRow[j];
	// }
}

int main(int argc, char* argv[]) 
{
	int Mat[m][m] = {
    	{1,2,3,4},
    	{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16},
	};
	doRowShift(Mat);
	for (int i=0; i<m; i++) {
		for (int j=0; j<m; j++)
    		printf("%d ", Mat[i][j]);
		printf("\n");
	}
	return 0;
}

