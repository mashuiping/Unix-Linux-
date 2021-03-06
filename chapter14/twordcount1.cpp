/*************************************************************************
    > File Name: twordcount1.cpp
    > Author: mashuiping
    > Mail: 1647934940@qq.com 
    > Created Time: Sat Mar  4 16:36:38 2017
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int total_words;

int main(int ac, char *av[]){
	pthread_t t1, t2;
	void * count_words(void *);
	if (ac != 3){
		printf("usage: %s file1 file2\n", av[0]);
		exit(1);
	}
	total_words = 0;

	pthread_create(&t1, NULL, count_words, av[1]);
	pthread_create(&t2, NULL, count_words, av[2]);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("%5d: total words\n", total_words);
}

void * count_words(void *f){
	char * filename = (char * )f;
	FILE *fp;
	int c, prevc = '\0';
	if((fp = fopen(filename, "r")) != NULL){
		while((c = getc(fp)) != EOF){
			// non-char && non num behind signed a word
			if(! isalnum(c) && isalnum(prevc))
				total_words++;
			prevc = c;
		}
		fclose(fp);
	}
	else
		//print the result of error to the stdout
		perror(filename);
	return NULL;
}
