/*************************************************************************
    > File Name: twordcount4.cpp
    > Author: mashuiping
    > Mail: 1647934940@qq.com 
    > Created Time: Sun Mar  5 08:31:51 2017
 ************************************************************************/
// the mutex lock ensure only one thread can do "condition wait"
// the same lock indicate both two thread should wait each other
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

using namespace std;

struct arg_set{
	char * fname;
	int count;
};
struct arg_set * mailbox;
pthread_mutex_t lock =	PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t flag =	PTHREAD_COND_INITIALIZER;

int main(int ac, char *av[]){
	pthread_t t1, t2;
	struct arg_set args1, args2;
	void *count_words(void *);
	int reports_in = 0;
	int total_words = 0;
	if(ac != 3){
		cout << "usage: " << av[0] << " file1 file2" << endl;
		exit(1);
	}
	pthread_mutex_lock(&lock);

	args1.fname = av[1];
	args1.count = 0;
	pthread_create(&t1, NULL, count_words, (void *) &args1);

	args2.fname = av[2];
	args2.count = 0;
	pthread_create(&t2, NULL, count_words, (void *) &args2);

	while(reports_in < 2){
	   //	sleep(1);
	   //	without sleep func,  the thread2 may no exec until the thread1 exit 
	   //	i think the cause of the result may be the priority queue (main > thread1 > thread2)   
		printf("MAIN: waiting for flag to go up\n");
		pthread_cond_wait(&flag, &lock);
		printf("MAIN: Wow! flag was raised, I have the lock\n");
		printf("%7d: %s\n", mailbox->count, mailbox->fname);
		total_words += mailbox->count;
		if(mailbox == &args1)
			pthread_join(t1, NULL);
		if(mailbox == &args2)
			pthread_join(t2, NULL);
		mailbox = NULL;
		pthread_cond_signal(&flag);
		reports_in++;
	}
	printf("%7d: total words\n", total_words);
}
void * count_words(void * a){
	struct arg_set * args = (arg_set * )a;
	FILE * fp;
	int c, prevc = '\0';
	if((fp = fopen(args->fname, "r")) != NULL){
		while((c = getc(fp)) != EOF){
			if(! isalnum(c) && isalnum(prevc))
				args->count++;
			prevc = c;
		}
		fclose(fp);
	}
	else
		perror(args->fname);
	printf("COUNT: waiting to get lock \n");
	pthread_mutex_lock(&lock);
	printf("COUNT: have lock, storing data\n");
	if(mailbox != NULL)
		pthread_cond_wait(&flag, &lock);
	mailbox = args;
	printf("COUNT: raising flag\n");
	pthread_cond_signal(&flag);
	printf("COUNT: unlocking box\n");
	pthread_mutex_unlock(&lock);
	return NULL;
}
