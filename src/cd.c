#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) 
{
    if (argc < 2)
    {
        printf("not supporting no args\n");
        return 1;
    }

    const char * path = argv[1];

    // Change the directory
    if (chdir(path) == -1) 
    {
        printf("error\n");
        return 1;
    }

    return 0;
}
