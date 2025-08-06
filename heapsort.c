#include <stdio.h>
#include <stdlib.h>
void swap(int arr[], int i, int j)
{
      int temp=arr[i];
      arr[i]=arr[j];
      arr[j]=temp;
}

void max_heapify(int arr[], int size, int i)
{
      int large=i;
      int left=2*i+1;
      int right=2*i+2;

      if(right<size && arr[right]>arr[large])
            large=right;
      if(left<size && arr[left]>arr[large])
            large=left;
      
      if(large != i)
      {
            swap(arr, large,i );
            max_heapify(arr, size, large);
      }
}

void build(int arr[], int size)
{
      for(int i = size/2-1;i>=0;i--)
            max_heapify( arr, size, i);
}

void print_array(int arr[], int size)
{
      for(int i=0;i<size;i++)
            printf("%d->",arr[i]);
}

void heap_sort(int arr[], int size)
{
      for(int j=size-1;j>1;j--)
      {
            swap(arr, 0, j);
            build( arr, j);
      }
      swap(arr,0,1);
}

int main()
{
      int size;
      printf("Enter the size of the array : \n");
      scanf("%d",&size);
      int arr[size];
      printf("Enter the elements of the array : \n");
      for(int i=0;i<size;i++)
            scanf("%d", &arr[i]);
      build(arr, size);
      printf("\nArray after heapify : ");
      print_array(arr, size);
      heap_sort(arr, size);
      printf("\nArray after heap sort : ");
      print_array(arr, size);
      return 0;

}

