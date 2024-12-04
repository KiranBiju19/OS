#include<stdlib.h>
//#include<semaphore.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
//#include<sys/mman.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdbool.h>

#define max 10

struct data{
	sem_t mutex,full, empty;
	int buffer[max];
	int index;
}*data;

int main()
{
   bool new=true;
  int fd=shm_open("/evideyo",  O_RDWR | O_EXCL,0777);
   if(fd== -1 && errno == EEXIST)
   {
      new=false;
      fd=shm_open("/evideyo",O_CREAT | O_RDWR,0777);
      if(fd==-1)
      {
       perror("Memory not open...");
       exit(EXIT_FAILURE);
      }
   }
   ftruncate(fd,sizeof(struct data));
  data=mmap(NULL,sizeof(struct data), PROT_READ | PROT_WRITE, MAP_SHARED, fd ,0);
   if(new)
  {
    data->index=0;
    sem_init(&(data->mutex), 10, 1);
    sem_init(&(data->full), 10, max);
    sem_init(&(data->empty), 10, 0);
  }
  while(true)
  {
    sem_wait(&(data->full));
    sem_wait(&(data->mutex));
    int item=data->buffer[(max+data->index-1)%max];
    printf("Consumed value =%d\n",item);
    data->index=(data->index -1+max)%max;
    sem_post(&(data->mutex));
    sem_post(&(data->empty));
    sleep(1);
  }
}
