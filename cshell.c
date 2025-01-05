#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_CMD_LEN 1024

void countChar(char* name) {
    int count = 0;
    FILE* file = fopen(name, "r");
    printf("This is at %p \n", &file);
    if (file == NULL) {
        printf("Nothing open pal\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count = count + 1;
    }
    printf("Final count is %d \n", count);
    fclose(file);
}

void countSize(char* name) {
    FILE* file = fopen(name, "r");
    printf("This is at %p \n", &file);

    int size;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    printf("Size is %d \n", size);
    fclose(file);
}

void countWords(char* name) {
    FILE* file = fopen(name, "r");
    int words = 1;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ') {
            words = words + 1;
        }
    }
    printf("These many words  %d \n", words);
}

void countLines(char* name) {
    FILE* file = fopen(name, "r");
    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines = lines + 1;
        }
    }
    printf(" Lines in code %d \n", lines);
    fclose(file);
}

void executeCommand(char *command) {
    if (strcmp(command, "exit") == 0) {
        printf("Exiting the shell...\n");
        exit(0);
    }

    if (strncmp(command, "-c", 2) == 0) {
        printf("gonna run countChar function\n");
        countChar(command + 3);
        return;
    }

    if (strncmp(command, "-s", 2) == 0) {
        printf("gonna give you size\n");
        countSize(command + 3);
        return;
    }

    if (strncmp(command, "-w", 2) == 0) {
        printf("gonna give you # of words\n");
        countWords(command + 3);
        return;
    }

    if (strncmp(command, "-l", 2) == 0) {
        printf("gonna give you # of lines\n");
        countLines(command + 3);
        return;
    }

    if (strncmp(command, "cd ", 3) == 0) {
        char *path = command + 3;
        if (SetCurrentDirectory(path) == 0) {
            printf("cd: %s: No such file or directory\n", path);
        }
        return;
    }

    if (system(command) == -1) {
        perror("system");
    }
}

int main() {
    char command[MAX_CMD_LEN];

    printf("Welcome to your custom CMD shell! Type 'exit' to quit.\n");

    while (1) {
        printf("cmd> ");
        fflush(stdout);
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        command[strcspn(command, "\n")] = '\0';
        if (strlen(command) > 0) {
            executeCommand(command);
        }
    }

    return 0;
}
