#include<iostream>
#include<stdlib.h>
//****important to add following library to allow a programmer to use parallel paradigms*****
#include<omp.h>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);

void bubble(int *a, int n)
{
  for(int i=0;i<n;i++) 
  {       
    int first = i % 2;      
    #pragma omp parallel for shared(a,first)
    for(int j=first;j<n-1;j+=2)
    {       
      if(a[j]>a[j+1])
      {       
  	swap(a[j],a[j+1]);
      }        
    }        
  }
}

void swap(int &a, int &b)
{
  int test;
  test=a;
  a=b;
  b=test;
}

int main()
{
  int *a,n;
  cout<<"\n enter total no of elements=>";
  cin>>n;
  a=new int[n];
  cout<<"\n enter elements=>";
  for(int i=0;i<n;i++)
  {
    cin>>a[i];
  }
  bubble(a,n);
  cout<<"\n sorted array is=>\n";
  for(int i=0;i<n;i++)
  {
    cout<<a[i]<<endl;
  }
  return 0;
}

/*
Output:

zoro2030@onepiece:~$ g++ bubble_sort.cpp -fopenmp
zoro2030@onepiece:~$ ./a.out

 enter total no of elements=>5

 enter elements=>23 11 44 33 9

 sorted array is=>
9
11
23
33
44

*/