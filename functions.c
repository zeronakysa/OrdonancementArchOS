//
// Created by root on 28/12/17.
//

#include "functions.h"

int numBlocks(int nbLines,char* fileToRead){
    FILE *file;
    int numLines = 0;
    int numBlocks = 0;
    int ch = 0;

    file = fopen(fileToRead, "r");
    if (file == NULL)
        exit (EXIT_FAILURE);
    while ( ch != EOF ){
        ch = fgetc( file );
        if( ch == '\n' )
            numLines++;
    }
    while (numLines > 0){
        numBlocks++;
        numLines = numLines - nbLines;
    }
    fclose(file);
    return numBlocks;
}

char** readFileToBuffer(int nbBlocks, int nbLines, char* buffer[],char* fileToRead){
    FILE *file;
    int ch = 0;
    int numLines = 0;
    int i, j = 0;

    buffer = malloc(sizeof(double long)*nbBlocks);
    if (buffer == NULL)
        exit(EXIT_FAILURE);
    for( i = 0; i < nbBlocks; i++){
        buffer[i] = malloc(8192 * sizeof(char));
        if (buffer[i] == NULL)
            exit(EXIT_FAILURE);
    }

    file = fopen(fileToRead, "r");
    if (file == NULL)
        exit (EXIT_FAILURE);
    i = 0;
    while ( ch != EOF ){
        ch = fgetc( file );
        if( ch == '\n' ){
            numLines++;
            buffer[i][j] = (char) ch;
            j++;
            if(numLines == nbLines){
                buffer[i][j] = '\0';
                i++;
                numLines = 0;
                j=0;
            }
        }else if (ch > 0){
            buffer[i][j] = (char) ch;
            j++;
        }
    }
    fclose (file);
    return buffer;
}

void createChilds(int* idChild,int nbBlocks){

    pid_t pere = getpid();

    for(int i = 0; i < nbBlocks ; i++){
        if (getpid() != pere){
            return;
        }else{
            idChild[i] = fork();
            if (getpid() != pere){
                return;
            }else{
                continue;
            }
        }
    }
}

void actionPere(int* idChild, FILE * scheduler){
    int i = 0;
    int status;
    time_t t;
    pid_t pid;

    while (idChild[i]) {
        fprintf(scheduler, "%d", idChild[i]);
        rewind(scheduler);
        pid = idChild[i];

        do {
            if ((pid = waitpid(pid, &status, WNOHANG)) == -1)
                perror("wait() error");
            else if (pid == 0) {
                time(&t);
                //printf("child%d is still running at %s",i, ctime(&t));
            }
            else {
                if (WIFEXITED(status))
                    printf("child%d exited with status of %d\n", i, WEXITSTATUS(status));
                else puts("child did not exit successfully");
            }
        } while (pid == 0);
        i++;
    }
}


void actionFils(int nbBlocks, int* idChild, char** buffer, FILE *output){
    int i = nbBlocks;
    char tmp[6] = {'\0'};
    FILE *scheduler2;

    while(idChild[i-1] == 0){
        i--;
    }
    if (i < 0)
        i = 0;

    while (1){
        scheduler2 = fopen("scheduler.tmp", "r");
        fread(tmp, sizeof(char), 5, scheduler2);
        fclose(scheduler2);
        if( atoi(tmp) == getpid()){
            printf("child%d,execute.\n", i);
            fprintf(output ,"%s", buffer[i]);
            exit(EXIT_SUCCESS);
        }
    }
}