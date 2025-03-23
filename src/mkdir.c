#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern void _mkdir(const char *dirname, int mode);

int main(int argc, char **argv) 
{
    if (argc < 2)
    {
        printf("Not providing name in mkdir\n");
        return 1;
    }

    const char * dir_name = argv[1];
    int mode = 0755;

    
    _mkdir(dir_name, mode);

    return 0;
}
