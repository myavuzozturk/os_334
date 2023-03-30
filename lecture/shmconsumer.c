//author: yusuf sahillioglu
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 1024

int main()
{
	key_t key = 1234;
	int shmid;
	char* shm, *s, c;


	shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);
	//-1 means error

	shm = (char *) shmat(shmid, NULL, 0);
	
	s = shm;

	for ( ; *s != 'z'; s++)
		printf("%c", *s);


	//alert the producer that i did sth
	*shm = '*';



	shmdt(shm);


	return 0;
}
