#include "functions.h"

int main(int argc, char* argv[]){

    /* Static mode
    int nbLines = 1;
    char* fileToRead = "test";
    char* fileToBuild = "endFile";
    */

    if( argc < 4){
        return (EXIT_FAILURE);
    }

    int nbLines = atoi(argv[1]);
    char* fileToRead = argv[2];
    char* fileToBuild = argv[3];

    pid_t pere = getpid();
    FILE *scheduler;
    FILE *output;

    scheduler = fopen("scheduler.tmp", "w+");
    output = fopen(fileToBuild, "w+");
    if(scheduler == NULL || output == NULL){
        puts("Erreur while creating files (run as root pls).");
        exit(EXIT_FAILURE);
    }

    int nbBlocks;
    char** buffer = {'\0'};
    int* idChild;

    nbBlocks = numBlocks(nbLines, fileToRead);

    idChild = malloc(nbBlocks * sizeof(int));

    buffer = readFileToBuffer(nbBlocks, nbLines, buffer, fileToRead);
    createChilds(idChild, nbBlocks);

    if(getpid() == pere){
        actionPere(idChild, scheduler);
    }else {
        actionFils(nbBlocks, idChild, buffer, output);
    }
    fclose(output);
    fclose(scheduler);

    if(remove("scheduler.tmp") == 0) {
        printf("scheduler.tmp file deleted successfully\n");
    } else {
        printf("Error: unable to delete the file\n");
    }
    return 0;
}