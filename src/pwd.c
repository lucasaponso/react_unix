#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    // Get the current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        printf("%s\n", cwd);
    } 
    else 
    {
        perror("getcwd");
        return 1;
    }

    return 0;
}
