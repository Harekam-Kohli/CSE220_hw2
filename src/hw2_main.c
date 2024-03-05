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
    // Check if the file exists and can be opened
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return -1; // Error opening file
    }
    fclose(file);
    return 0; // File exists and can be opened
}

int validateOutputFile(const char *fileName) {
    // Check if the file can be created for writing
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        return -1; // Error creating file
    }
    fclose(file);
    return 0; // File can be created for writing
}

int main(int argc, char* argv[]) {
    char *inputFileName = NULL, *outputFileName = NULL;
    int iFlag = 0, oFlag = 0,cFlag=0,rFlag=0,pFlag=0;
    int status[10] = {0};

    // Iterate through argument list
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (iFlag) {
                status[3]++;
            }
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                inputFileName = argv[i + 1];
                iFlag++;
                i++; // Skip the next argument since it's the parameter for -i
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
                i++; // Skip the next argument since it's the parameter for -o
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
                    // Parse and validate each parameter for -c
                    //int value = atoi(token);
                    // Perform additional validation if needed
                    index++;
                    token = strtok(NULL, ",");
                }
                printf("%d",index);
                if(index!=4)
                    status[7]++; 
                cFlag++;
                i++; // Skip the next argument since it's the parameter for -c
            } else {
                status[6]++;
            }

            // Extend with additional else if blocks for other options like -c, -p, -r
        }
        else if (strcmp(argv[i], "-p") == 0){
            if (pFlag) {
                status[3]++;
            }
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                char *token = strtok(argv[i + 1], ",");
                int index = 0;
                while (token != NULL) {
                    // Parse and validate each parameter for -p
                    //int value = atoi(token);
                    // Perform additional validation if needed
                    index++;
                    token = strtok(NULL, ",");
                }
                if(index!=2)
                    status[8]++;
                pFlag++;
                i++; // Skip the next argument since it's the parameter for -p
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
                // Validate and parse parameters for -r
                // Example: -r "stony brook university","fonts/font4.txt",1,80,10
                char *token = strtok(argv[i + 1], ",");
                int count = 0;
                while (token != NULL) {
                    if(count == 1)
                    {
                        if(validateInputFile(token) == -1)
                            status[9]++;
                    }
                    // Perform validation based on the parameter count
                    // Example: Check if the first parameter is a string, second is a file, etc.
                    count++;
                    token = strtok(NULL, ",");
                }
                if (count != 5) {
                    status[9]++;
                }
                rFlag++;
                i++; // Skip the next argument since it's the parameter for -r
            } else {
                status[1]++;
            }
        }
        else
        {
            status[2]++;
        }
    }

    // Validate mandatory arguments are provided
    if (!iFlag || !oFlag) {
        status[1]++;
    }

    if(pFlag>0 && cFlag == 0)
        status[6]++;

    // Validate input and output files
    if (validateInputFile(inputFileName) != 0) {
        status[4]++;
    }
    if (validateOutputFile(outputFileName) != 0) {
        status[5]++;
    }

    // Additional logic for processing images based on provided arguments
    for(int i = 0; i<10;i++)
    {
        if(status[i])
            return i;
    }
    return 0;
}