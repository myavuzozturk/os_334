//author: yusuf sahillioglu
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void myHandler(int sig)
{
	if (sig == SIGTERM)
		printf("ah what happened?\n");

	else if (sig == SIGINT)
		//printf("ah what happened?\n");
		write(fileno(stdout), "ah it hurts!\n", 13);

	else if (sig == SIGKILL)
		printf("no\n");

	else if (sig == SIGFPE)
	{
		printf("div by 00000000000\n");
		exit(-1);
	}


	else if (sig == SIGSEGV)
	{
		printf("seg falutttttttt\n");
		exit(-1);
	}

//exit(-1);
}

int main()
{
	
	struct sigaction sa;
	sa.sa_handler = myHandler; //user-level handler
	sa.sa_flags = SA_RESTART; //restart the system call (open,read,write) if signal delivered during that sys call
	sigemptyset(&sa.sa_mask); //ensure all signals recieved

	sigaction(SIGTERM, &sa, NULL);
 	//-1 if fails*/
//signal(SIGINT, myHandler); //unsafe

	sigaction(SIGINT, &sa, NULL); //override default SIGINT

//	if (sigaction(SIGKILL, &sa, NULL) == -1)
//		printf("errorrrrrrrrrrr\n");

	sigaction(SIGFPE, &sa, NULL); //override default SIGINT



	int i = 0, y;


	y = 8 / (i+1);

	char* seg;

	sigaction(SIGSEGV, &sa, NULL); //override default SIGINT



	seg[0] = 'X';


	while (1)
	{
		printf("%d\n", i++);
		sleep(1);
	}


	return 0;
}
