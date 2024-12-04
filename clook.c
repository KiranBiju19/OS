#include<stdio.h>
#include<math.h>

void sort(int a[], int n)
{
	int i,temp,j;
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
				if(a[j] > a[j+1])
					{
						temp=a[j];
						a[j]=a[j+1];
						a[j+1]=temp;
					}		
}

int main()
{
	int n, head, s=-1, l=-1, seek_time=0, count=2,dd;
	printf("Enter the number of elements: ");
	scanf("%d",&n);
	
	int arr[n],sml[n],lrg[n];
	printf("Enter the elements for the array:\n");
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	
	printf("\nEnter the head position: ");
	scanf("%d",&head);

	for(int i=0;i<n;i++)
		if(arr[i]>head)
			lrg[++l]=arr[i];
		else
			sml[++s]=arr[i];
	sort(lrg,l+1);
	sort(sml,s+1);
	
	// if(fabs(lrg[0]-head) < fabs(sml[s]-head))
	// 	dd=1;
	// else
	// 	dd=2;
	
	dd=1;

	while(count>0)
	{
		if(dd==1)
		{
			for(int i=0;i<=l;i++)
				{
					seek_time+=fabs(lrg[i]-head);
					head=lrg[i];
				}
			dd=2;
			count--;
		}
		else if(dd==2)
		{
			for(int i=0;i<=s;i++)
				{
					seek_time+=fabs(sml[i]-head);
					head=sml[i];
				}
			dd=1;
			count--;
		}
	}	
	
	printf("\nTotal seek time: %d",seek_time);
	return 0;
}


//176 79 34 60 92 11 41 114
