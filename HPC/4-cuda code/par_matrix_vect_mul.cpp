#include<iostream>
#include<stdio.h>
//****important to add following library to allow a programmer to use parallel paradigms*****
#include<omp.h>
#include<math.h>
using namespace std;
int main()
{
    cout<<"Number of rows in first matrix: ";
    int row1;
    cin>>row1;

    cout<<"Number of columns in first matrix: ";
    int col1;
    cin>>col1;

    int row2 = col1;

    cout<<"Number of columns in second matrix: ";
    int col2;
    cin>>col2;

    cout<<endl;
    cout<<"Enter elements for Matrix 1:"<<endl;
    int mat1[row1][col1];
    for(int i=0; i<row1; i++)
    {
        for(int j=0; j<col1; j++)
        {
            //mat1[i][j] = rand()%10; // randomly taking input values
            cin>>mat1[i][j] ; 
        }
    }
    cout<<endl;

    cout<<"Enter elements for Matrix 2:"<<endl;
    int mat2[row2][col2];
    for(int i=0; i<row2; i++)
    {
        for(int j=0; j<col2; j++)
        {
          //mat2[i][j] = rand()%10; // randomly taking input values
            cin>>mat2[i][j]; 
        }
    }
    cout<<endl;

    cout<<"Matrix 1:"<<endl;
    for(int i=0; i<row1; i++)
    {
        for(int j=0; j<col1; j++)
        {
            cout << mat1[i][j] << " " ; 
        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"Matrix 2:"<<endl;
    for(int i=0; i<row2; i++)
    {
        for(int j=0; j<col2; j++)
        {
            cout << mat2[i][j] << " " ; 
        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"Multiplication: "<<endl;
    int mat3[row1][col2];
    #pragma omp parallel for
	for(int i=0;i<row1;i++)
	{
		#pragma omp parallel for
		for(int j=0;j<col2;j++)
		{
			mat3[i][j]=0;
      int arr[col1];
      #pragma omp parallel for
			for(int k=0;k<col1;k++) {
        arr[k] = mat1[i][k]*mat2[k][j];
      }

      int sum = 0;
      #pragma omp parallel for reduction(+: sum)
      for (int l = 0; l < col1; l++){
        sum += arr[l];
      } 

      mat3[i][j] = sum;
		}
	}

    for(int i=0; i<row1; i++)
    {
        for(int j=0; j<col2; j++) {
          cout<<mat3[i][j]<<" ";
        }
        
        cout<<endl;
    }

    return 0;
}

/*
o/p:
zoro2030@onepiece:~$ g++ par_matrix_vect_mul.cpp -fopenmp
zoro2030@onepiece:~$ ./a.out
Number of rows in first matrix: 2
Number of columns in first matrix: 2
Number of columns in second matrix: 2

Enter elements for Matrix 1:
1
2
3
4

Enter elements for Matrix 2:
4
3
2
1

Matrix 1:
1 2
3 4

Matrix 2:
4 3
2 1

Multiplication:
8 5
20 13
*/
