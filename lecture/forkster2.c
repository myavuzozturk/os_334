//author: yusuf sahillioglu
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
//	system("ls -l"); //it does fork() behind the scene


	printf("execster.c; my pidddddddd = %d\n", getpid());

	char* argvs[] = {"forkster", "7", "sdfsdfs", "8888", NULL};
	execvp("./forkster", argvs); //never returns back

//char* argvs2[] = {"ls", NULL};
//execvp("/bin/ls", argvs2); //never returns back

//execlp("/bin/ls", "ls", NULL); //never returns back


	printf("never reacher here unless exec fails\n");

	return 0;
}
