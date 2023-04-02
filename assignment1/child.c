
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char filename[64] ;
    sprintf(filename, "file/input%d.txt", atoi(argv[1]));

    FILE *f = fopen(filename, "r");

    if (f == NULL)
        return 1;


    printf("%p \n", (void *)f);


    return 0;
}