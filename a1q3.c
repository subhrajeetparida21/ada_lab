#include <stdio.h>
int iteration=1;

void merge(int arr[], int left, int mid, int right)
{
      int n1=mid-left+1;
      int n2=right-mid;
      int arr1[n1], arr2[n2], i=0, j=0, k;

      for(i=0;i<n1;i++)
            arr1[i]=arr[i+left];
      for(j=0;j<n2;j++)
            arr2[j]=arr[j+mid+1];
      
      printf("%d Iteration :\n",iteration);
      printf("First part : ");
      for(i=0;i<n1;i++)
            printf("%d->",arr1[i]);
      printf("\nSecond part : ");
      for(j=0;j<n2;j++)
            printf("%d->",arr2[j]);
      
      i=0;j=0, k=left;

      while(i<n1 && j<n2)
      {
            if(arr1[i]>arr2[j])
                  arr[k++]=arr2[j++];
            else
                  arr[k++]=arr1[i++];
            
      }

      while(i<n1)
            arr[k++]=arr1[i++];
      while(j<n2)
            arr[k++]=arr2[j++];
      
      printf("\n");
      iteration++;
      
}

void mergesort(int arr[], int left, int right)
{
      if (left < right) {
            int mid = left + (right - left) / 2;
            mergesort(arr, left, mid);
            mergesort(arr, mid + 1, right);
            merge(arr, left, mid, right);
    }

}

int main()
{
      int size;
      printf("Enter the size of the array : ");
      scanf("%d", &size);
      int arr[size];
      printf("Enter the array elements : \n");
      for(int i=0;i<size;i++)
            scanf("%d",&arr[i]);
      
      mergesort(arr, 0, size-1);
      printf("\nArray element after sorting : ");
      for(int i=0;i<size;i++)
            printf("%d->",arr[i]);
      

}