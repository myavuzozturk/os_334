#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define d 4
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

pthread_mutex_t myMutex;
sem_t mutex;
sem_t barrier;
int count=0, n=d;

void* doShifts() 
{
	int i, j, k;

	// Row shift
	int firstRow[m];
	for (k=1; k<=s; k++) {
		for (j=0; j<m; j++)
			firstRow[j] = Mat[0][j];
		for (j=0; j<m; j++) {
			for (i=0; i<(m-1); i++) {
				pthread_mutex_lock(&myMutex);
				Mat[i][j] = Mat[i+1][j];
				if ((i+1)%(m/d)==0)
					pthread_mutex_unlock(&myMutex);
			}
		}
		for (j=0; j<m; j++)
			Mat[m-1][j] = firstRow[j];
	}

	sem_wait(&mutex);
	count++;
	sem_post(&mutex);
	if(count==n)
		sem_post(&barrier);
	sem_wait(&barrier);
	sem_post(&barrier);

	// Col shift
	int lastCol[m];
	for (k=1; k<=s; k++) {
		for (i=0; i<m; i++)
			lastCol[i] = Mat[i][m-1];
		for (i=0; i<m; i++) {
			for (j=(m-1); j>=1; j--) {
				pthread_mutex_lock(&myMutex);
				Mat[i][j] = Mat[i][j-1];
				if ((i+1)%(m/d)==0)
					pthread_mutex_unlock(&myMutex);
			}
		}
		for (i=0; i<m; i++)
			Mat[i][0] = lastCol[i];
	}
}

int main(int argc, char* argv[]) 
{
	pthread_t threads[d];
	sem_init(&mutex, 0, 1);
	sem_init(&barrier, 0, 0);
	int i,j;

	for (i=0; i<d; i++)
		pthread_create(&threads[i], NULL, doShifts, NULL);
	for (i=0; i<d; i++)
		pthread_join(threads[i], NULL);

	doShifts();

	for (i=0; i<m; i++) {
		for (j=0; j<m; j++)
    		printf("%d ", Mat[i][j]);
		printf("\n");
	}
	return 0;
}
