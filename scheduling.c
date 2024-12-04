#include<stdio.h>
int npid;
int arr[10][6],rq[10],flag[10],sum=0;
int display()
{    
    printf("\nPid\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<npid;i++)
    {    for(int j=0;j<6;j++)
            printf("%d\t",arr[i][j]);
        printf("\n");
    }
    
    for(int j=0;j<npid;j++)
        printf("%d\t",rq[j]);

    
}
/*
        1 0 11
        2 5 28
        3 12 2
        4 2 10
        5 9 16
*/

int fcfs()
{
    //  for(int i=0;i<npid;i++)
    //     {
    //         for(int j=0;j<6;j++)
    //         {
    //             if(arr[i][j] <= arr[i][j])
    //             {
    //                 int temp = arr[i][j];
    //                 arr[i][j] = arr[i][j];
    //                 arr[i][j] = temp;
    //             }
    //         }
    //     }
    sum=0;
    for(int i=0;i<npid;i++)
    {
            arr[i][3]=sum+arr[i][2];
            sum=arr[i][3];
            arr[i][4]=arr[i][3]-arr[i][1];
            arr[i][5]=arr[i][4]-arr[i][2];
            printf("%d ",i);
    }
}
/*
        1 0 11
        2 5 28
        3 12 2
        4 2 10
        5 9 16
*/
int sjf()
{
    int hat=arr[npid-1][1];
    int f=0,r=0;
    arr[0][3]=arr[0][2];
    int ct=arr[0][3];
    printf("%d ",ct);
    arr[0][4]=arr[0][3]-arr[0][1];
    arr[0][5]=arr[0][4]-arr[0][2];

    for(int i=1;i< npid;i++)
    {
        for(int j=1;j<npid;j++)
        {
            if(arr[j][1]<ct && flag[j]==0)
            {
                rq[f++]=j;
                printf("%d ",j);
            }
        }
        printf("\n");
        for(int k=r;k<f;k++)
        {
            for(int h=0;h<k;h++)
            {
                if(arr[rq[k]][2] <= arr[rq[k+1]][2] && rq[k]!=0 && rq[k+1]!=0)
                {
                    int temp = rq[k];
                    rq[k] = rq[k+1];
                    rq[k+1] = temp;
                    printf("%d ",rq[k]);
                }
            }
            printf("\n");
        }
//create a srtf using producer consumer problem
        for(int k=r;k<f;k++)
        {
            if(rq[k]==0)
             break;
            arr[rq[k]][3]=ct+arr[rq[k]][2];
            ct+=arr[rq[k]][3];
            arr[rq[k]][4]=arr[rq[k]][3]-arr[rq[k]][1];
            arr[rq[k]][5]=arr[rq[k]][4]-arr[rq[k]][2];
            flag[rq[k]]=1;
         }
        printf("r= %d ",r);
        r=f;
        //ct=sum;//ct+arr[rq[f-1]][3];
    }
}

int nps()
{
    int ch1;
  do{
      printf("MENU\n1.FCFS\n2.SJF\n3.Priority\n4.Exit\nEnter your choice: ");
      scanf("%d",&ch1);
      switch(ch1)
      {
        case 1: fcfs(); break;
        case 2: sjf(); break;
        //case 3: pnps(); break;
        case 4: break;
      }
      display();
  }while(ch1!=4);
}
/////Non Premptive Scheduling


int main()
{
  int ch;
  printf("Enter the number of process: ");
  scanf("%d",&npid);
  printf("Enter the value for process id, arrival time, burst time:");

  for(int i=0;i<npid;i++)
   { 
    flag[i]=0;
    rq[i]=0;
    for(int j=0;j<6;j++)
        arr[i][j]=0;
   }

  for(int i=0;i<npid;i++)
    for(int j=0;j<3;j++)
     scanf("%d",&arr[i][j]);

  do{
      printf("MENU\n1.Non-Premptive\n2.Premptive\n3.Exit\nEnter your choice: ");
      scanf("%d",&ch);
      switch(ch)
      {
        case 1: nps(); break;
        //case 2: ps(); break;
        case 3: break;
      }
  }while(ch!=3);
}

// for(int j=0;j<npid;j++)
        // {
        //  if(arr[i][1]<time)
        //  {
        //     //insert();
        //     rq[k]=i;
            
        //     if(k==0)
        //      {
        //         arr[i][3]+=arr[i][2];
        //         arr[i][4]=arr[i][3]-arr[i][1];
        //         arr[i][5]=arr[i][4]-arr[i][2];
        //         k++;
        //      }

        //      else
        //      {

        //      }
        //  }
        /*
        1 0 11
        2 5 28
        3 12 2
        4 2 10
        5 9 16
        */