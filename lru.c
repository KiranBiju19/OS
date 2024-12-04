//SSTF Disk Scheduling algorithm
#include <stdio.h>
#include <math.h>

int main()
{
	int head,n;
	printf("Enter the array size: ");
	scanf("%d",&n);
	
	int arr[n],chk[n],seek_count=0;
	
	for(int i=0;i<n;i++)
	    chk[i]=0;
	
	printf("\nStart entering the number: ");
	for(int i=0;i<n;i++)
	    scanf("%d",&arr[i]);
	 printf("\nEnter the current head position: ");
	 scanf("%d",&head);
	
	for(int j=0;j<n;j++)
	{
	    int hg=99999;
	    int loc=99999;
	    for(int i=0;i<n;i++)
	    {
	        if(fabs(head-arr[i])<hg && chk[i]==0)
	        {
	            hg=fabs(head-arr[i]);
	            loc=i;
	        }
	    }
	    printf("Accesing order: %d\n",arr[loc]);
	    seek_count+=hg;
	    head=arr[loc];
	    chk[loc]=1;
	}
	
	printf("\nTotal over-head movement: %d\n",seek_count);
	

	return 0;
}
/*

sample input: size=8
            176,79,34,60,92,11,41,114

output:

Enter the array size: 7

Start entering the number: 82
170
43
140
24
16
190

Enter the current head position: 50

Accesing order: 43
Accesing order: 24
Accesing order: 16
Accesing order: 82
Accesing order: 140
Accesing order: 170
Accesing order: 190

Total over-head movement: 208

*/