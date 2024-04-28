#include<iostream>
#include<stdio.h>
#include<cstdlib>
//****important to add following library to allow a programmer to use parallel paradigms*****
#include<omp.h>	
using namespace std;
#define MAX 10

int main()
{
   int a[MAX],b[MAX],c[MAX],i;
   

   //Instruct a master thread to fork and generate more threads to process following loop structure
   #pragma omp parallel for
   for(i=0;i<MAX;i++)
   {
         cout << "Eneter First Vector " << i +1 <<" Element :";
         cin >> a[i];
      //a[i]=rand()%10;
   }
  //Discuss issue of this for loop below-if we make it parallel, possibly values that get printed will not be in sequence as we dont have any control on order of threads execution
   
   cout << "\n";
   #pragma omp parallel for
   for(i=0;i<MAX;i++)
   {
         cout << "Eneter Second Vector " << i + 1 <<" Element :";
         cin >> b[i];
         //b[i]=rand()%10;
   }
 cout << "\n";
   printf("\n First Vector:\t");
   for(i=0;i<MAX;i++)
   {
      printf("%d\t",a[i]);
   }
   printf("\n Second Vector:\t");
   for(i=0;i<MAX;i++)
   {
      printf("%d\t",b[i]);
   }
   printf("\n Parallel-Vector Addition : \t");
   #pragma omp parallel for
   for(i=0;i<MAX;i++) 
   {
      c[i]=a[i]+b[i];
   }
   for(i=0;i<MAX;i++)
   {
      printf("\n%d\t%d\t%d",a[i],b[i],c[i]);
   }
}
/*
output:
zoro2030@onepice:~$ g++ par_add_large_vectors.cpp -fopenmp
zoro2030@onepice:~$ ./a.out
Eneter First Vector 1 Element :1
Eneter First Vector 2 Element :2
Eneter First Vector 3 Element :3
Eneter First Vector 4 Element :4
Eneter First Vector 5 Element :5
Eneter First Vector 6 Element :6
Eneter First Vector 7 Element :7
Eneter First Vector 8 Element :8
Eneter First Vector 9 Element :9
Eneter First Vector 10 Element :10

Eneter Second Vector 1 Element :10
Eneter Second Vector 2 Element :9
Eneter Second Vector 3 Element :8
Eneter Second Vector 4 Element :7
Eneter Second Vector 5 Element :6
Eneter Second Vector 6 Element :5
Eneter Second Vector 7 Element :4
Eneter Second Vector 8 Element :3
Eneter Second Vector 9 Element :2
Eneter Second Vector 10 Element :1


 First Vector:  1       2       3       4       5       6       7       8       9       10
 Second Vector: 10      9       8       7       6       5       4       3       2       1
 Parallel-Vector Addition :
1       10      11
2       9       11
3       8       11
4       7       11
5       6       11
6       5       11
7       4       11
8       3       11
9       2       11
10      1       11
*/