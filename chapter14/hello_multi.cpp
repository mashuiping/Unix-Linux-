/*************************************************************************
    > File Name: hello_multi.cpp
    > Author: mashuiping
    > Mail: 1647934940@qq.com 
    > Created Time: Sat Mar  4 15:50:06 2017
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#define NUM 5

using namespace std;

int main(){
	pthread_t p1, p2;
	timeval t1, t2;
	void * print_msg(void *);
	gettimeofday(&t1, NULL);

	pthread_create(&p1, NULL, print_msg, (void *)"hello");
	pthread_create(&p2, NULL, print_msg, (void *)"world\n");

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	gettimeofday(&t2, NULL);
	cout << 1000000 * (t2.tv_sec - t1.tv_sec) << endl;
}

void * print_msg(void *m){
	for (int i = 0; i < NUM; i++){
		printf("%s",(char *) m);
		fflush(stdout);
		sleep(1);
	}
	return NULL;
}
