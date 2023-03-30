//author: yusuf sahillioglu
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fds2[2], fds1[2];
	pid_t pid;
	char buf[100];

	pipe(fds2);
	pipe(fds1);
	//-1 means error


	pid = fork();

	if (pid == 0) //child
	{
		//write to pipe2 instead of to stderr
		dup2(fds2[1], fileno(stderr));
		close(fds2[0]);

		fprintf(stderr, "3 + 4\n");
		fflush(stderr);




		dup2(fds1[0], fileno(stdin));
		close(fds1[1]);


		fgets(buf, 100, stdin);
		
		printf("lazy child got the result from parent: %s", buf);

	}
	else //parent
	{
		//read from pipe2 instead of from default stdin
		dup2(fds2[0], fileno(stdin));
		close(fds2[1]);

		

		dup2(fds1[1], fileno(stdout));
		close(fds1[0]);

		

		execlp("bc", "bc", NULL);

		//printf("sdsdfsdfsdf\n");	
	}



	return 0;
}
