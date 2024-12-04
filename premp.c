#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int rr(int at[],int bt[],int size)
{
  int rm_time[size],ct,tat[size],wt[size],rq[100],k=0,done=1,time=0;
  for(int i=0;i<size;i++)
	rm_time[i]=bt[i];
  int qnt;
  printf("Enter the quntum time: ");
  scanf("%d",&qnt);
  while(!done)
  {
	for(int i=0;i<size;i++)
	{
		if(rm_time[i]>0)
		{
           done=0;
		   if(rm_time[i]>0)
		   {
			time=time+qnt;
			rm_time[i]=rm_time[i]-qnt;
			printf("%d",i+1);
		   }
		   else
		   {
			time=time+rm_time[i];
			ct=time;
			tat[i]=ct-at[i];
			wt[i]=tat[i]-bt[i];
			rm_time[i]=0;
		   }
		}
	}
  }
  for(int i=0;i<size;i++)
      printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct,tat[i],wt[i]);
}

int srjf(int at[],int bt[],int size)
{
  int rm_time[size],ct,tat[size],wt[size],rq[100],k=0;
  bool complt[size];
  for(int i=0;i<size;i++)
	{
		rm_time[i]=bt[i];
		complt[i]=false;
	}
   int count=0,counter=0;
   while(count!=size)
	{
		int sht_job=-1;
		int sht_time=9999;
		for(int i=0;i<size;i++)
			{
				if(at[i]<=counter && !complt[i] && rm_time[i]<sht_time)
					{
						sht_job=i;
						sht_time=rm_time[i];
					}
			}
		if(sht_job==-1)
			counter++;
		else
		{
			rm_time[sht_job]--;
			rq[k++]=sht_job+1;
			if(rm_time[sht_job] == 0)
				{
					count++;
					ct=counter+1;
					tat[sht_job]=ct - at[sht_job];
					wt[sht_job]= tat[sht_job]-bt[sht_job];
					complt[sht_job]=true;
					printf("%d\t%d\t%d\t%d\t%d\t%d\n",sht_job+1,at[sht_job],bt[sht_job],ct,tat[sht_job],wt[sht_job]);	
					
				}
		}
		counter++;
	}
	for(int i=0;i<k;i++)
	 printf("%d ",rq[i]);
}


int main()
{
  int n;
  printf("Enter the number of process");
  scanf("%d",&n);
  int at[n],bt[n],tat[n],wt[n];
  printf("Enter the arrival time");
  for(int i=0;i<n;i++)
  	scanf("%d",&at[i]);
  printf("Enter the burst time:");
  for(int i=0;i<n;i++)
	scanf("%d",&bt[i]);
  //srjf(at,bt,n);
  printf("_______\nRound Robin\n");
  rr(at,bt,n);
}