#include "hw2.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> 

int validateInputFile(const char* filename);
int validateOutputFile(const char* filename);


int validateInputFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return -1; 
    }
    fclose(file);
    return 0;
}

int validateOutputFile(const char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        return -1;
    }
    fclose(file);
    return 0; 
}

int main(int argc, char* argv[]) {
    char *inputFileName = NULL, *outputFileName = NULL;
    int iFlag = 0, oFlag = 0,cFlag=0,rFlag=0,pFlag=0;
    int status[10] = {0};

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (iFlag) {
                status[3]++;
            }
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                inputFileName = argv[i + 1];
                iFlag++;
                i++; 
            } else {
                status[1]++;
            }
        } else if (strcmp(argv[i], "-o") == 0) {
            if (oFlag) {
                status[3]++;
            }
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                outputFileName = argv[i + 1];
                oFlag++;
                i++; 
            } else {
                status[1]++;
            }
        } 
        else if (strcmp(argv[i], "-c") == 0) {
            if (cFlag) {
                status[3]++;
            }
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                char *token = strtok(argv[i + 1], ",");
                int index = 0;
                while (token != NULL) {
                    index++;
                    token = strtok(NULL, ",");
                }
                printf("%d",index);
                if(index!=4)
                    status[7]++; 
                cFlag++;
                i++; 
            } else {
                status[6]++;
            }
        }
        else if (strcmp(argv[i], "-p") == 0){
            if (pFlag) {
                status[3]++;
            }
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                char *token = strtok(argv[i + 1], ",");
                int index = 0;
                while (token != NULL) {
                    index++;
                    token = strtok(NULL, ",");
                }
                if(index!=2)
                    status[8]++;
                pFlag++;
                i++; 
            } else {
                status[1]++;
            }

        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            if(rFlag) {
                status[3]++;
            }
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                char *token = strtok(argv[i + 1], ",");
                int count = 0;
                while (token != NULL) {
                    if(count == 1)
                    {
                        if(validateInputFile(token) == -1)
                            status[9]++;
                    }
                    count++;
                    token = strtok(NULL, ",");
                }
                if (count != 5) {
                    status[9]++;
                }
                rFlag++;
                i++;
            } else {
                status[1]++;
            }
        }
        else
        {
            status[2]++;
        }
    }

    if (!iFlag || !oFlag) {
        status[1]++;
    }

    if(pFlag>0 && cFlag == 0)
        status[6]++;

    if (validateInputFile(inputFileName) != 0) {
        status[4]++;
    }
    if (validateOutputFile(outputFileName) != 0) {
        status[5]++;
    }
        
    for(int i = 0; i<10;i++)
    {
        if(status[i])
            return i;
    }
    return 0;
}