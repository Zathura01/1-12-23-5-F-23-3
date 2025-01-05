#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#define MAX_SIZE 100

void countChar(char* name) {

    int count = 0;
    FILE* file = fopen(name, "r");
    printf("This is at %p \n",&file);
    if (file == NULL) {
        printf("Nothing open pal\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count = count + 1;
    }
    printf("Final count is %d\n", count);
    fclose(file);
}

void countSize(char* name){
    FILE* file = fopen(name, "r");
    printf("This is at %p \n",&file);

    int size;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    printf("Size is %d",size);
    fclose(file);
}

void countWords(char* name){
    FILE* file = fopen(name, "r");
    int words = 1;
    char ch;
    while ((ch = fgetc(file)) !=EOF )
    {
        if(ch == ' '){
            words = words + 1;
        }
    }
    printf("These many words %d",words);
    
}

void countLines(char* name){
    FILE* file = fopen(name, "r");
    int lines = 0;
    char ch;
    while((ch = fgetc(file))!= EOF){
        if(ch == '\n'){
            lines = lines + 1;
        }
    }
    printf(" Lines in code %d",lines);
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Something's wrong with the arguments.\n");
        return 1;
    }

    printf("First: %s, Second: %s\n", argv[0], argv[1]);
    
    if (strcmp(argv[1], "-c") == 0) {
        printf("gonna run countChar function\n");
        countChar(argv[2]);
    } 
    if(strcmp(argv[1], "-s") == 0){
        printf("gonna give you size\n");
        countSize(argv[2]);
    }
    if(strcmp(argv[1], "-w") == 0){
        printf("gonna give you # of words\n");
        countWords(argv[2]);
    }  
    if(strcmp(argv[1], "-l") == 0){
        printf("gonna give you # of lines\n");
        countLines(argv[2]);
    }
     else {
        printf(" \nSomething wrong in code: %s\n", argv[1]);
    }

    return 0;
}
