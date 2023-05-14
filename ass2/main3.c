#include <pthread.h>
#include <stdio.h>

#define m 4
#define n 4

int Mat1[m][n] = {
    {1,2,3,4},
    {5,6,7,8},
	{9,10,11,12},
	{13,14,15,16},
};
int Mat2[m][n] = {
    {4,3,2,1},
    {8,7,6,5},
	{12,11,10,9},
	{16,15,14,13},
};
int Mat[m][n];

pthread_mutex_t myMutex;

void* doSum() 
{
	int i,j;
	
	for (j=0; j<n; j++) {
		pthread_mutex_lock(&myMutex);
		for (i=0; i<m; i++)
			Mat[i][j] = Mat1[i][j] + Mat2[i][j];
		pthread_mutex_unlock(&myMutex);
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
