#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>

char **getInput(char *input);
int cd(char *path);

int main() {
    char **args;
    char *input;
    pid_t cpid;
    int status;

    while (1) {
        input = readline("esh> ");
        args = getInput(input);

        if (!args[0]) {
            free(input);
            free(args);
            continue;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (cd(args[1]) < 0) {
                perror(args[1]);
            }
            continue;
        }

        cpid = fork();
        if (cpid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (cpid == 0) {
            if (execvp(args[0], args) < 0) {
                perror(args[0]);
                exit(1);
            }
        } else {
            waitpid(cpid, &status, WUNTRACED);
        }
        free(input);
        free(args);
    }
    return 0;
}

char **getInput(char *input) {
    char **args = malloc(8 * sizeof(char *));
    if (args == NULL) {
        perror("Malloc failed");
        exit(1);
    }
    char *parsed;
    int index = 0;

    parsed = strtok(input, " ");
    while(parsed != NULL) {
        args[index] = parsed;
        index++;

        parsed = strtok(NULL, " ");
    }

    args[index] = NULL;
    return args;
}

int cd(char *path) {
    return chdir(path);
}
