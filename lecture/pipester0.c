//author: yusuf sahillioglu
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fds[2];
	pid_t pid;
	char buf[100];

	pipe(fds);
	//-1 means error

	printf("stdin/out/err uses descriptors %d/%d/%d\n", fileno(stdin), fileno(stdout), fileno(stderr));
	printf("my writing/reading end id: %d/%d\n", fds[1], fds[0]);


	pid = fork();

/*	if (pid == 0)
	{
		printf("child writes sth\n");
		write(fds[1], "hi there!", 9);
		
	}
	else
	{

		printf("parent readsss\n");
		read(fds[0], buf, 100);
		buf[9]  = '\0';

		printf("%s\n", buf);
		
	}*/


	if (pid == 0)
	{
		//read from pipe instead of from default stdin
//		close( fileno(stdin) );
//		dup(fds[0]); //make fds[0] same as stdin
dup2(fds[0], fileno(stdin));//replace 2 lines above with this

		close(fds[1]);
		
		execlp("wc", "wc", "-l", NULL);				
	}
	else
	{
		//write to pipe instead of to default stdout
//		close( fileno(stdout) );
//		dup(fds[1]); //make fds[1] same as stdout
dup2(fds[1], fileno(stdout));
		close(fds[0]);

		execlp("ls", "ls", "-1", NULL);		
	
	}



	return 0;
}

/* pass a dynamic array to the pipe
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char **argv){
    // child process will send an array of values to parent process

    // init file descriptors for pipe
    int fd[2]; // fd[0] - read, fd[1] - write

    // error check pipe
    if (pipe(fd) == -1){
        printf ("error with the pipe. \n");
        return 1;
    }
    
    // fork and error check the fork operation
    int id = fork();
    if (id == -1){
        printf("error with the fork");
    }

    int i = 0, size = 0; 
    int *data;
    

    if (id == 0){
        // this is a child process, we do not need to read from the pipe so we close fd[0]
        close(fd[0]);

        printf ("enter size: "); scanf ("%d", &size);
        data = (int*) malloc (size * sizeof(int)); // dynamically allocate array

        printf ("populate array: \n");
        for (i = 0; i < size; i++){
            scanf ("%d", &data[i]);
        }

        // printf ("entered array: \n");
        for (i = 0; i < size; i++){
            // printf ("%d ", data[i]);
        }
        
        // child process write() to pipe and error check
        printf ("\nchild process writing to pipe..\n");   

        if (write(fd[1], &size, sizeof(int)) == -1){ // note variable reference here
            printf("error with the pipe. \n");
            return 4;
        }

        if (write(fd[1], data, 4 * sizeof(int)) == -1){ // note array reference and size of array here
            printf("error with the pipe. \n");
            return 2;
        }

        // close write fd because we are done writing to the pipe at this point.
        close(fd[1]);
    } else { // parent process
        close(fd[1]); // now reading from pipe

        int mysize = 0;
        
        // parent process reads from pipe
        if (read(fd[0], &mysize, sizeof(int)) < 0) // note variable reference here
        {
            printf("error with the pipe. \n");
            return 5;
        }
        int receivedArray[mysize]; // = (int*) malloc (mysize * sizeof(int)); // dynamically allocate array

        if (read(fd[0], receivedArray, mysize * sizeof(int)) < 0) // note array reference and size here
        {
            printf("error with the pipe. \n");
            return 3;
        }
         
        close(fd[0]); // close pipe for read
        printf ("received array: [ ");
        for (i = 0; i < mysize; i++){
            printf ("%d ", receivedArray[i]);
        }
        printf ("]\n");
    }

    return 0;
}
*/

/* pass a struct to the pipe
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


struct Point
{
    int x, y;
};

int main (int argc, char **argv){
    printf ("\n welcome to pipes and ipc!\n");

    int fd[2]; // an array of two int values as file descriptors; fd[0] - read, fd[1] - write
    if (pipe(fd) == -1){
        printf ("error with the pipe. \n");
        return 1;
    }
    
    // fork and error check
    int id = fork();
    if (id == -1){
        printf("error with the fork");
    }

    int i = 0; // counter variable

    if (id == 0){
        // this is a child process, we do not need to read from the pipe so we close fd[0]
        close(fd[0]);

        int x; //we want to send this value from child to parent
        int y;
        printf("enter x: ");
        scanf("%d", &x);

        printf("enter y: ");
        scanf("%d", &y);

        struct Point p1 = {x, y}; // encapsulate to send
        
        // child process write() to pipe
        printf ("child process writing to pipe..\n");
         
        if (write(fd[1], &p1, sizeof(struct Point)) == -1){ //*
            printf("error with the pipe. \n");
            return 2;
        }

        // close write fd because we are done writing to the pipe at this point.
        close(fd[1]);
    } else { // parent process
        close(fd[1]); // now reading from pipe
        
        struct Point receivedPoint = {0, 0}; // may not be automatically done by the compiler
        // (struct Point*) malloc (sizeof (struct Point)); //  
        
        // parent process reads from pipe
        if (read(fd[0], &receivedPoint, sizeof(struct Point)) < 0) // pay attention to struct address reference here
        {
            printf("error with the pipe. \n");
            return 3;
        }
         
        close(fd[0]); // close pipe for read
        printf("\nreceived from child process: {x = %d, y = %d} \n", receivedPoint.x, receivedPoint.y); 
        
    } 

    return 0;
} // end main
*/

