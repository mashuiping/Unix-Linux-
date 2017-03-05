/*************************************************************************
    > File Name: timeClientSHM.cpp
    > Author: mashuiping
    > Mail: 1647934940@qq.com 
    > Created Time: Sun Mar  5 14:15:39 2017
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/shm.h>

#define TIME_MEM_KEY  99
#define SEG_SIZE ((size_t) 100)
#define oops(m, x){perror(m); exit(x);}

using namespace std;

int main(int ac, char * av[]){
	int seg_id;
	char * mem_ptr;
	long now;
	// create a shared memory segment
	seg_id = shmget(TIME_MEM_KEY, SEG_SIZE, 0777);
	if(seg_id == -1)
		oops("shmget", 1);
	//attach to it and get a pointer to whete it attaches
	mem_ptr = (char *) shmat(seg_id, NULL, 0);
	if(mem_ptr == (void *) -1)
		oops("shmat", 2);
	printf("The time, direct from memory:..%s", mem_ptr);
	shmdt(mem_ptr);
}
