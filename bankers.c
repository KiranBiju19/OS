#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

int alloc[100][100],max[100][100],need[100][100];
int avl[100],avl2[100],check[100],ans[100];
int rp[100];

bool flag=false,f1=false,f2=false;
int row,colm,n=0;

int testing()
{
 for(int i=0;i<row;i++)
  {
    flag=true;
    for(int j=0;j<colm;j++)
    {
       if(avl[j]<need[i][j])
        { 
         flag=false;
          break;
        }
       n++;
    }
    
    if(flag==true && check[i]==0)
    {
       check[i]=1;
       for(int k=0;k<colm;k++)
       {
          avl[k]+=alloc[i][k];
          printf("%d ",avl[k]);
       }
       printf("P%d ",i);
       printf("\n");
    }
  }
  return n;
}

int algo()
{
   int pnum;
   printf("Which process need new request?");
   scanf("%d",&pnum);
   printf("Enter the value for new process");
   for(int i=0;i<colm;i++)
      scanf("%d",&rp[i]);
      
   for(int i=0;i<colm;i++)
  	check[i]=0;
  
   for(int i=0;i<colm;i++)
   {
       if(rp[i]<=need[pnum][i])
         f1=true;
       else
         {
           f1=false;
           printf("It's not possible to create safe sequence");
           break;
         }
       
       if(rp[i]<=avl2[i])
         f2=true;
       else
         {
           f2=false;
           printf("It's not possible to create safe sequence");
           break;
         }
   }

   printf("%d %d\n",f1,f2);
   if(f1==true && f2==true)
   {
      for(int i=0;i<colm;i++)
      {
         avl2[i] = avl2[i]-rp[i];
         alloc[pnum][i] = alloc[pnum][i]+rp[i];
         need[pnum][i] = need[pnum][i]-rp[i]; 
         printf("%d %d %d",avl2[i],alloc[pnum][i],need[pnum][i]);
         printf("\n");
         avl[i] = avl2[i];
      }
      n=0;
      while(n<=row*row)
        n=testing();
        
      printf("\n\tDONE\n");
   }
}

int main()
{
 
  printf("Enter the number of process: ");
  scanf("%d",&row);
  printf("Enter the number of resources: ");
  scanf("%d",&colm);
  
  
  
  for(int i=0;i<colm;i++)
  	check[i]=0;
  
  printf("Enter the values for allocation matrix: \n ");
  for(int i=0;i<row;i++)
  {
     for(int j=0;j<colm;j++)
     {
         scanf("%d",&alloc[i][j]);
     }
  }
  
   printf("Enter the values for max matrix: \n ");
  for(int i=0;i<row;i++)
  {
     for(int j=0;j<colm;j++)
     {
         scanf("%d",&max[i][j]);
     }
  }
  
   printf("Enter the values for available matrix: \n ");
  for(int i=0;i<colm;i++)
  {
     scanf("%d",&avl[i]);
     avl2[i]=avl[i];
  }
  
  printf("\nCreating Need Matrix.....\n");
  for(int i=0;i<row;i++)
  {
     for(int j=0;j<colm;j++)
     {
         need[i][j]=max[i][j]-alloc[i][j];
         printf(" %d ",need[i][j]);
     }
     printf("\n");
  }
  int i,j;
  while(n<=row*row)
     n=testing();
   
   int ch;
   printf("Would you like to perform Resourse Request Algorithm?(Y=1/N=0)");
   scanf("%d",&ch);
   if(ch==1)
     algo();
     
    return 0;
} 



/*  
 0 1 0
 2 0 0
 3 0 2
 2 1 1
 0 0 2
 
 
 7 5 3
 3 2 2
 9 0 2
 2 2 2
 4 3 3
 
 3 3 2
 
 
 p1-1 0 2
 1 3 4 0 2 
 */