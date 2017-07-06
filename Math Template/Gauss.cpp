#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

//高斯_若尔当消元
//A为增广矩阵 , A[i][n] 存储的是系数
//求解完成后，A[i][n] 存储的是第i个未知数的值
const int MatrixSize = 50;
const double eps = 1e-8;
typedef double Matrix[MatrixSize][MatrixSize];

void Gauss(Matrix A, int n) 
{
  int i, j, k, r;
  for(i = 0; i < n; ++ i) 
  {
      r = i;
      for(j = i+1; j < n; ++ j)
        if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
      if(fabs(A[r][i]) < eps) continue;
      if(r != i) for(j = 0; j <= n; j++) swap(A[r][j], A[i][j]);
      for(k = 0; k < n; k++) if(k != i)
        for(j = n; j >= i; j--) A[k][j] -= A[k][i]/A[i][i] * A[i][j];
  }
  for(i = 0 ; i < n ; ++ i)
  {
    	 if(fabs(A[i][n]) < eps) A[i][n] = 0;
    	 else A[i][n] /= A[i][i];
  }
}



int main(int argc , char *argv[])
{
	
	return 0;
}