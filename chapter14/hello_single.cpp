/*************************************************************************
    > File Name: hello_single.cpp
    > Author: mashuiping
    > Mail: 1647934940@qq.com 
    > Created Time: Sat Mar  4 15:25:59 2017
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM 5

using namespace std;

int main(){
	timeval t1, t2;
	void print_msg(char *);
	gettimeofday(&t1, NULL);
	print_msg("hello");
	gettimeofday(&t2, NULL);
	cout << 1000000*(t2.tv_usec - t1.tv_usec) << endl;
	print_msg("world\n");
}
void print_msg(char *m){
	int i;
	for(i = 0; i < NUM; i++){
		printf("%s", m);
		cout << " ";
		fflush(stdout);
		sleep(1);
	}
}
