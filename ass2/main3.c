#include <pthread.h>
#include <stdio.h>

#define m 4
#define n 4
#define k 4
#define x 2

int Mat1[m][n] = {
    {1,2,3,4},
    {5,6,7,8},
	{9,10,11,12},
	{13,14,15,16},
};
int Mat2[n][k] = {
    {4,3,2,1},
    {8,7,6,5},
	{12,11,10,9},
	{16,15,14,13},
};
int Mat[m][k];
int sum;

pthread_mutex_t myMutex;

void* doDotProd(int offset, int i1, int j2)
{
	int aa, i;
	int start = offset*n;
	int end = offset*n + n;

	int locSum = 0, a, b;
	for (i=0; i<n; i++) {
		a = Mat1[i1][i];
		b = Mat1[i][j2];
		for (aa=start; aa<end; aa++)
			locSum += a*b;
	}

	pthread_mutex_lock(&myMutex);
	sum += locSum;
	pthread_mutex_unlock(&myMutex);
}

void* writeSum() 
{
	pthread_t threads[m];
	int i,j,l;
	for (i=0; i<x; i++)
		pthread_create(&threads[i], NULL, doDotProd, NULL);
	for (i=0; i<m; i++)
		pthread_join(threads[i], NULL);
	
	for (j=0; j<n; j++) {
		for (i=0; i<m; i++) {
			pthread_mutex_lock(&myMutex);
			for (l=0; l<k; l++)
				doDotProd(m/x, i, l);
				Mat[i][l] = sum;
			pthread_mutex_unlock(&myMutex);
		}
	}
}

int main(int argc, char* argv[]) 
{
	pthread_t threads[m];
	int i,j;

	for (i=0; i<m; i++)
		pthread_create(&threads[i], NULL, doSum, NULL);
	for (i=0; i<m; i++)
		pthread_join(threads[i], NULL);

	doSum();

	for (i=0; i<m; i++) {
		for (j=0; j<m; j++)
    		printf("%d ", Mat[i][j]);
		printf("\n");
	}
	return 0;
}
