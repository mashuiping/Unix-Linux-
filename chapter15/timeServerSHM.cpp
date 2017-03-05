/*************************************************************************
    > File Name: timeServerSHM.cpp
    > Author: mashuiping
    > Mail: 1647934940@qq.com 
    > Created Time: Sun Mar  5 13:48:10 2017
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <sys/shm.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

using namespace std;

#define TIME_MEM_KEY 99
#define SEG_SIZE ((size_t)100)
#define oops(m, x){	perror(m); exit(x);}

int main(int ac, char * av[]){
	int seg_id;
	char * mem_ptr;
	time_t now;
	int n;
	// create a shared memory segment
	seg_id = shmget(TIME_MEM_KEY, SEG_SIZE, IPC_CREAT | 0777);
	if(seg_id == -1){
		oops("shmget", 1);
	}
	// attach to it and get a pointer to whete it attaches
	// explict convert void * to char *
	mem_ptr = (char *)shmat(seg_id, NULL, 0);
	if(mem_ptr == (void * )-1)
		oops("shmat",2);
	for(n = 0; n < 60; n++){
		time(&now);
		// write to mem
		strcpy(mem_ptr, ctime(&now));
		sleep(1);
	}
	// remove it
	shmctl(seg_id, IPC_RMID, NULL);
}
