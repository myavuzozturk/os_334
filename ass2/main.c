#include <pthread.h>
#include <stdio.h>

#define d 2
#define m 4
#define s 1

void doRowShift(int* pMat) {
	
	int firstRow[m]

	for (int i=0; i=m-1; i++) {
		if (i==0)
			firstRow[i] = Mat[i,j];
		for (int j=0; j=(m-1); j++)
			Mat[i][j] = Mat[(i-s)%m][j];
	}
}

int main(int argc, char* argv[])
{
	int Mat[m][m] = {
    	{1,2,3,4},
    	{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16},
	};
	doRowShift(&Mat[0][0]);
	for (int i=0; i<m; i++) {
		for (int j=0; j<m; j++)
    		printf("%d ", Mat[i][j]);
		printf("\n");
	}
	return 0;
}

