#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) 
{
    // // If no arguments are passed, use current directory.
    const char *dir_path = (argc == 1) ? "." : argv[1];

    // Define a pointer to DIR
    DIR *dir_stream;
    
    // Define a pointer to the dirent struct
    struct dirent *dir_read;

    // Open the specified directory
    dir_stream = opendir(dir_path);

    // opendir returns NULL on error, so we handle the error...
    if (dir_stream == NULL) {
        perror("Error while trying to open directory");
        return 1;
    }

    // Now let's read the contents:
    while ((dir_read = readdir(dir_stream)) != NULL) {
        printf("%s\t%d bytes\n", dir_read->d_name, dir_read->d_reclen);
    }

    // We also need to close the directory when we are done
    if (closedir(dir_stream) == -1) {
        perror("Can't close the directory");
        return -1;
    }

    return 0;
}
