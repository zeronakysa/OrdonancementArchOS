//
// Created by root on 28/12/17.
//

#ifndef DESKTOP_FUNCTIONS_H
#define DESKTOP_FUNCTIONS_H

#endif //DESKTOP_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>


int numBlocks(int nbLines,char* fileToRead);
char** readFileToBuffer(int nbBlocks, int nbLines, char* buffer[],char* fileToRead);
void createChilds(int *idChild, int nbBlocks);
void actionPere(int* idChild, FILE *scheduler);
void actionFils(int nbBlocks, int* idChild, char** buffer, FILE *output);
