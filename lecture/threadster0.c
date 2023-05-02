//author: yusuf sahillioglu
#include <pthread.h>
#include <stdio.h>

typedef struct
{
	int tid, upper;
} MyData;

////pthread_mutex_t myMutex;

int sum;

void* runner(void* p)
{
	MyData* md = (MyData*) p;
	int i;

	printf("hi from thread w/ ysf-assigned id: %d\n", md->tid);

////pthread_mutex_lock(&myMutex);
	for (i = 1; i <= md->upper; i++)
		sum += i;
////pthread_mutex_unlock(&myMutex);

////////sleep(7);

	pthread_exit(0);
}

int main(int argc, char* argv[])
{
	pthread_t thread1, thread2;
	pthread_attr_t attr;
	int n = atoi(argv[1]); //go 'till 20000 to prevent integer overflow


	sum = 0;


	MyData md1, md2;
	md1.tid = 77;
	md1.upper = n;

//	md2.tid = 78;
//	md2.upper = n;

////	pthread_mutex_init(&myMutex, NULL);

	pthread_attr_init(&attr);
	pthread_create(&thread1, &attr, runner, (void*) &md1);
//	pthread_create(&thread2, &attr, runner, (void*) &md2);

//////	printf("enter an int to demonstrate i/o block:\n");
//////	scanf("%d", &n);
//////	printf("i/o done (thread already completed while the same process was blocked on i/o): %d\n", n);

	pthread_join(thread1, NULL/*eitStatus*/); //similar to wait() on child; block 'till runner() exits
//	pthread_join(thread2, NULL/*eitStatus*/);
////    pthread_mutex_destroy(&myMutex);

	printf("summmmmmm = %d\n", sum);

	return 0;
}
