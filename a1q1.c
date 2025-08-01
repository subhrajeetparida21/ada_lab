#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Student
{
      int roll;
      char name[25];
      float cgpa;
      char dept[25];
}s1;


int main()
{
      int n;
      printf("Enter the no of inputs : ");
      scanf("%d",&n);
      s1* det=(s1*)malloc(n*sizeof(s1));
      for(int i=0;i<n;i++)
      {
            printf("Enter the roll no of the student\n");
            scanf("%d",&det[i].roll);
            printf("Enter the name of the student\n");
            scanf("%s",det[i].name);
            printf("Enter the cgpa of the student\n");
            scanf("%f",&det[i].cgpa);
            printf("Enter the department of the student\n");
            scanf("%s",det[i].dept);
      }
      
      for(int i=1;i<n;i++)
      {
            s1 key = det[i];
            int j=i-1;
            while(j>=0 && det[j].cgpa>key.cgpa)
            {
                  det[j+1]=det[j];
                  j--;
            }
            det[j+1] = key;
      }

      for(int i=0;i<n;i++)
      {
            int k=1;
            while(det[i].cgpa==det[i+k].cgpa)
            {
                  k++;
            }
            if(k>1)
            {
                  for(int a=i+1;a<i+k;a++)
                  {
                        s1 key = det[a];
                        int j = a-1;
                        while(j>=i && key.roll<det[j].roll)
                        {
                              det[j+1]=det[j];
                              j--;
                        }
                        det[++j]=key;
                  }
            }
            i+=k;
      }
      for(int i=0;i<n;i++)
      {
            printf("%d %s %.2f %s\n",det[i].roll, det[i].name, det[i].cgpa, det[i].dept);
      }

      free(det);
      return 0;
}