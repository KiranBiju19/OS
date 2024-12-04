#include<stdio.h>
#include<stdlib.h>
//#include<semaphore.h>
#include<unistd.h>
#include<fcntl.h>
//#include<sys/mman.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdbool.h>


#define max 5

struct data{
	int buffer[max];
	sem_t empty,full,mutex;
	int index;
}*d;

//sem_t mutex,empty,full;

int main(){
	bool new=true;
	int fd=shm_open("/ramanan",O_CREAT|O_RDWR|O_EXCL,0777);
	if(fd==-1 && errno==EEXIST)
	{      
		new=false;
		fd=shm_open("/ramanan",O_CREAT|O_RDWR,0777);
		if(fd==-1){
		perror("shm_open failed to open existing memory");
		exit(EXIT_FAILURE);
		}
	}
	ftruncate(fd,sizeof(struct data));
	d=mmap(NULL,sizeof(struct data),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		if(new){
			d->index=0;
			sem_init(&(d->mutex),10,1);
			sem_init(&(d->full),10,0);
			sem_init(&(d->empty),10,max);
			}
		while(true){
			int x;
			sem_getvalue(&(d->full),&x);
			if(x==max){
				printf("Buffer full\n");
				exit(0);
				}
			int y=rand()%100;
			sem_wait(&(d->empty));
			sem_wait(&(d->mutex));
			d->buffer[d->index]=y;
			d->index++;
			sem_post(&(d->mutex));
			sem_post(&(d->full));
			printf("Producer produced %d\n",y);
			sleep(1);
			}
		return 0;
}