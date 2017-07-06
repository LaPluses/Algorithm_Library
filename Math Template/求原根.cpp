#include <iostream>  
#include <cstdlib>  
#include <cstring>  
#include <cstdio>  
using namespace std;  
int P;  
const int NUM = 32170;  
int prime[NUM/4];  
bool f[NUM];  
int pNum = 0;  
void getPrime()//线性筛选素数  
{  
    for (int i = 2; i < NUM; ++ i)  
    {  
        if (!f[i])  
        {  
            f[i] = 1;  
            prime[pNum++] = i;  
        }  
        for (int j = 0; j < pNum && i*prime[j] < NUM; ++ j)  
        {  
            f[i*prime[j]] = 1;  
            if (i%prime[j] == 0)  
            {  
                break;  
            }  
        }  
    }  
}  
__int64 getProduct(int a,int b,int P)//快速求次幂mod  
{  
    __int64 ans = 1;  
    __int64 tmp = a;  
    while (b)  
    {  
        if (b&1)  
        {  
            ans = ans*tmp%P;  
        }  
        tmp = tmp*tmp%P;  
        b>>=1;  
    }  
    return ans;  
}  
  
bool judge(int num)//求num的所有的质因子  
{  
    int elem[1000];  
    int elemNum = 0;  
    int k = P - 1;  
    for (int i = 0; i < pNum; ++ i)  
    {  
        bool flag = false;  
        while (!(k%prime[i]))  
        {  
            flag = true;  
            k /= prime[i];  
        }  
        if (flag)  
        {  
            elem[elemNum ++] = prime[i];  
        }  
        if (k==1)  
        {  
            break;  
        }  
        if (k/prime[i]<prime[i])  
        {  
            elem[elemNum ++] = prime[i];  
            break;  
        }  
    }  
    bool flag = true;  
    for (int i = 0; i < elemNum; ++ i)  
    {  
        if (getProduct(num,(P-1)/elem[i],P) == 1)  
        {  
            flag = false;  
            break;  
        }  
    }  
    return flag;  
}  
int main()  
{  
      
    getPrime();  
    while (cin >> P)  
    {  
        for (int i = 2; i <= P ;++i)  
        {  
            if (judge(i))  
            {  
                cout << i<< endl;  
                break;
            }  
        }  
    }  
    return 0;  
}  