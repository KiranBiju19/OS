#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

int main()
{
    int fd[2];
    pid_t p;
    char name[100];
    pipe(fd);
    p=fork();
    
    if(p>0)
    {
        int l,num;
        FILE *fp;
        fp=fopen("test.txt","r");
    
        while(fscanf(fp,"%[^\n]",name)!=EOF)
            {
                l+=strlen(name);
                fgetc(fp);    
            }
        
        close(fd[1]);
        read(fd[0],&num,sizeof(num));
        close(fd[0]);
        
        fclose(fp);
        
        printf("Parent process result: %d\n",l);
        printf("Child process result: %d\n",num);
    }
    
    else
    {
        FILE *fp;
        fp=fopen("test.txt","r");
        
        int count=0;
        char ch;
        while((ch=fgetc(fp))!=EOF)
            if(ch=='\n')
                count++;
        count++;
        close(fd[0]);
        write(fd[1],&count,sizeof(count));
        close(fd[1]);
        
        fclose(fp);
    }
    
    
    return 0;
}








