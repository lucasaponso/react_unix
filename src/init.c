#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/reboot.h>
#include <stdlib.h>  
#include <sys/wait.h>
#include "utils.h"

#define MAX_TOKENS 6
#define MAX_TOKEN_LEN 20
#define MAX_CMD_LEN 255

char** token_stdin(char command[MAX_CMD_LEN]);

extern int real_waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options, void*);
extern void mkdir(const char *dirname, int mode);
extern ssize_t write(int fildes, const void *buf, size_t nbyte);
extern int open(const char *pathname, int flags, mode_t mode);
extern ssize_t read(int fd, void *buf, size_t count);
extern int execve(const char *pathname, char *const argv[], char *const envp[]);
extern pid_t fork(void);
extern void _exit(int status);

char** token_stdin(char command[MAX_CMD_LEN]) 
{
    static char* output_arr[MAX_TOKENS];
    char buffer[MAX_TOKEN_LEN];
    int token_count = 0;
    int i = 0, j = 0;

    while (command[i] != '\0') 
    {
        if (command[i] == ' ' || command[i] == '\0') 
        {
            if (j > 0) 
            {
                buffer[j] = '\0';

                output_arr[token_count] = (char*)malloc(j + 1);
                if (output_arr[token_count] != NULL) 
                {
                    memcpy(output_arr[token_count], buffer, j + 1);
                } 
                else 
                {
                    printf("Memory allocation failed\n");
                    _exit(1);
                }

                token_count++;
                j = 0;
            }
        } 
        else 
        {
            buffer[j++] = command[i];
        }

        i++;
    }

    if (j > 0)
    {
        buffer[j] = '\0';
        output_arr[token_count] = (char*)malloc(j + 1);
        if (output_arr[token_count] != NULL) {
            memcpy(output_arr[token_count], buffer, j + 1);
        } else {
            printf("Memory allocation failed\n");
            _exit(1);
        }
        token_count++;
    }

    output_arr[token_count] = NULL;
    return output_arr;
}

int main()
{
    sleep(1);
    print_motd();

    const char *dirname = "example_directory";
    int mode = 0755;

    mkdir(dirname, mode);

    char command[MAX_CMD_LEN];
    for (;;) 
    {
        write(1, "# ", 2);
        int count = read(0, command, 255);
        command[count - 1] = '\0';
        char **tokens = token_stdin(command);
        
        if (tokens[0] != NULL) 
        {
            printf("token[0]: %s\n", tokens[0]);
            if (tokens[1] != NULL) 
            {
                printf("token[1]: %s\n", tokens[1]);
            }
        }

        // Check if the command is "cd"
        if (tokens[0] != NULL && strcmp(tokens[0], "cd") == 0) 
        {
            if (tokens[1] != NULL) 
            {
                // Change the directory using chdir
                if (chdir(tokens[1]) == -1) 
                {
                    perror("cd failed");
                }
            } 
            else 
            {
                printf("cd: missing argument\n");
            }
        } 
        else 
        {
            // Handle other commands by forking and executing
            pid_t fork_result = fork();
            if (fork_result == 0) 
            {
                // Child process
                if (execve(tokens[0], tokens, NULL) == -1) 
                {
                    perror("execve failed");
                    _exit(1);  // Exit if execve fails
                }
            } 
            else 
            {
                // Parent waits for child process to finish
                siginfo_t info;
                real_waitid(P_ALL, 0, &info, WEXITED, 0);
            }
        }
    }

    _exit(0);
}
