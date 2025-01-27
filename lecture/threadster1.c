//author: yusuf sahillioglu
//a dot b = a1*b1 + a2*b2 + .. + a4000*b4000 = 4000 sinca all 1

#include <pthread.h>
#include <stdio.h>

//whole vector will be of size NUMTHREADS*VECLEN
#define NUMTHREADS 40
#define VECLEN 100

pthread_mutex_t myMutex;
double* a, * b, sum;

void* doDotProduct(void* p)
{
	int offset = (int) p, i,
		start = offset * VECLEN, end = offset * VECLEN + VECLEN;



	double locSum = 0.0;
	for (i = start; i < end; i++)
//	{
		locSum += a[i]*b[i]; //no mutual exclusion needed (read-only)
	

//printf("a b: %f %f\n", a[i], b[i]);
//}

	pthread_mutex_lock(&myMutex);
	sum += locSum;
	pthread_mutex_unlock(&myMutex);

//	pthread_exit(0);
}

int main(int argc, char* argv[])
{
	pthread_t threads[NUMTHREADS];

	a = (double*) malloc(NUMTHREADS*VECLEN * sizeof(double));
	b = (double*) malloc(NUMTHREADS*VECLEN * sizeof(double));
	int i;
	for (i = 0; i < NUMTHREADS*VECLEN; i++)
	{
		a[i] = 1.0;
		b[i] = 1.0;
	}
	sum = 0;

	for (i = 0; i < NUMTHREADS*VECLEN; i++)
		printf("aaaa b: %f %f\n", a[i], b[i]);


	pthread_mutex_init(&myMutex, NULL);


	for (i = 0; i < NUMTHREADS; i++)
		pthread_create(&threads[i], NULL, doDotProduct, (int) i);
	
	for (i = 0; i < NUMTHREADS; i++)
		pthread_join(threads[i], NULL);

	printf("dotProd = %f\n", sum); //remember this event


	sum = 0;
	for (i = 0; i < NUMTHREADS*VECLEN; i++)
		sum += a[i]*b[i];
	printf("seq dotProd = %f\n", sum);


	return 0;
}

