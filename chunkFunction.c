//
// Created by het on 3/10/21.
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "chunkFunction.h"

int valueChecker(int value) {
    if (value <= 0) {
	fprintf(stderr,"Invalid Arguement\n");
	exit(0);
	return -1;
    }
    return 1;
}
int errorHandle(char* opt) {
    if (strcmp(" ",opt) == 0) {
	return -1;
    } //if
    return 0;
} // errorHandle

int inputFile(char* fileName) {
   int value = open(fileName,O_RDONLY);
   if (value == -1) {
       fprintf(stderr,"File does not exist\n");
       exit(0);
   }
   return value;
}

int checker(char* optarg) {
    if (optarg[0] >= 'a' && optarg[0] <= 'z') {
	if (optarg[1] >= 'a' && optarg[1] <= 'z') {
	    return 1;
	} else {
	    fprintf(stderr,"Invalid Arguement\n");
	    exit(0);
	    return -1;
	}
    } else if (optarg[0] >= '0' && optarg[0] <= '9' && optarg[1] >= '0' && optarg[1] <= '9') {
	return 1;
    } else {
	fprintf(stderr,"Invalid Arguement\n");
	exit(0);
	return -1;
    }
}
