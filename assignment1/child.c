
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

void SelectionSort(int * nums, int n);
void InsertionSort(int * nums, int n);

int main(int argc, char **argv)
{
    // Definitions
    char InputFileName[64], OutputFileName[64];
    int nums[100];
    int n, i;

    // Get start time
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

    // Create file names
    sprintf(InputFileName,  "file/input%d.txt",  atoi(argv[1]));
    sprintf(OutputFileName, "file/output%d.txt", atoi(argv[1]));

    // Open files
    FILE *InputFile = fopen(InputFileName, "r");
    if (InputFile == NULL)
        return 1;

    FILE *OutputFile = fopen(OutputFileName, "w");
    if (OutputFile == NULL)
        return 1;


    // Read input file
    fscanf(InputFile,"%d\n",&n);

    for(i=0; i<n; i++)
        fscanf(InputFile,"%d ", &nums[i]);

    // Sort numbers with appropriate sorting function
    if((atoi(argv[1])%2) == 1)
        SelectionSort(nums, n);
    else
        InsertionSort(nums, n);

#if 0    
    for(i=0; i<n; i++)
        printf("%d ", nums[i]);
    printf("\n");
#endif
    
    // Random sleep between 1-7 seconds
    srand(time(NULL));
    int stime = (rand() % 7) + 1 ;
    sleep(stime);

    // Get end time & calculate execution time
    gettimeofday(&tv2, NULL);
    double time_spent = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec) ;
#if 0
    printf ("Total time = %f seconds\n", time_spent);
#endif

    //  Writes the results to the intermediate output file
    fprintf(OutputFile, "%d\n", n);
    for(i=0; i<n; i++)
        fprintf(OutputFile, "%d ", nums[i]);
    fprintf(OutputFile, "\n");
    fprintf(OutputFile, "%f \n", time_spent);
    fprintf(OutputFile, "**** coming soon ****\n");


    // Close files
    fclose(InputFile);
    fclose(OutputFile);
    
    return 0;
}


void SelectionSort(int * nums, int n)
{
    int i,k, tmp;

    k=0;
    for(k=0; k<(n-1); k++)
    {
        for(i=k+1; i<n; i++){
            if(nums[i]<nums[k])
            {
                tmp = nums[k] ;
                nums[k] = nums[i];
                nums[i] = tmp ;
            } 
        }
    }
    return;
}

void InsertionSort(int * nums, int n)
{
    int i ;
    for (int i = 1; i < n; i++) 
    {
        int key = nums[i];
        int j = i - 1;

        while (key < nums[j] && j >= 0) {
            nums[j + 1] = nums[j];
            --j;
        }
        nums[j + 1] = key;
  }

}