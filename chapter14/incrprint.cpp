/*************************************************************************
    > File Name: incrprint.cpp
    > Author: mashuiping
    > Mail: 1647934940@qq.com 
    > Created Time: Sat Mar  4 16:26:44 2017
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 5

using namespace std;

int counter = 0;

int main(){
	pthread_t t1;
	void * print_count(void *);
	int i;
	pthread_create(&t1, NULL, print_count, NULL);
	for(i = 0; i < NUM; i++){
		counter++;
		sleep(1);
	}
	pthread_join(t1, NULL);
}

void *print_count(void *m){
	int i;
	for(i = 0; i < NUM; i++){
		printf("count = %d\n", counter);
		sleep(1);
	}
	return NULL;
}
