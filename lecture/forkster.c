//author: yusuf sahillioglu
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>


int i, ysf = 7;
void doSomeWork(char* name)
{
	if (strcmp(name, "child") == 0)
		ysf = 888888;


	for (i = 0; i < 5; i++)
	{
		sleep(1);
		printf("done iter %d by %s observer this global %d \n", i, name, ysf);
	}
}

void main()
{
	
	printf("I'm process with id %d\n", getpid());

sleep(4);

	pid_t pid = fork();

	if (pid < 0)
		printf("fork failed\n");
	else if (pid  == 0)
	{
		printf("fork returned with %d for child\n", pid);
		sleep(12);
		doSomeWork("child");
		exit(0);
	}
	else
		printf("fork returned with %d for parent\n", pid);

//sleep(12); //zombie process demo
		
	doSomeWork("parent");

	pid_t exitStatus;
	printf("fhi there\n");
	pid_t childid = wait(&exitStatus);
	printf("parent finished; child w/ id %d has exit stat = %d\n", childid, exitStatus);
sleep(12);



//	int i;
//	for (i = 0; i < 2; i++)
//	{
//		fork();
//		printf("%d: my pid = %d\n", i, getpid());
//	}
//	sleep(1);
//	printf("mmmmmmmmmy pid  %d\n", getpid());
}

/*int main (int argc, char* argv[])
{
	printf("forkster.c; my pid = %d\n", getpid());

	printf("my argumentssssssss: \n");
	
int i;
	for (i = 0; i < argc; i++)
		printf("%s, ", argv[i]);
	printf("\n");

	return 0;
}*/
