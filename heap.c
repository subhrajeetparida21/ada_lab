#include <stdio.h>
#include <stdlib.h>

void max_heapify(int arr[], int n, int i)
{
      int largest = i, left = (2*i)+1, right =(2*i)+2;
      if(left<n && arr[left]>arr[largest])
            largest = left;
      if(right<n && arr[right]>arr[largest])
            largest = right;
      
      if(largest !=i)
      {
            int temp=arr[largest];
            arr[largest]=arr[i];
            arr[i]=temp;

            max_heapify(arr, n, largest);
      }
      
}

void build(int arr[],int n)
{
      for(int i=n/2-1;i>=0;i--)
            max_heapify(arr, n, i);
}
void print_heap(int arr[],int n)
{
      for(int i=0;i<n;i++)
            printf("%d->",arr[i]);
}

int main()
{
      int arr[]={1,3,4,2,7,812,56,98};
      build(arr,8);
      print_heap(arr, 8);
      
      return 0;
}
