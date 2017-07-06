#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>


using namespace std;


void extend_gcd(long long a , long long b , long long& d , long long & x , long long &y ){
    if (!b) d = a , x = 1 , y = 0;
    else{
        extend_gcd(b,a%b,d,y,x);
        y -= x*(a/b);
    }
}

long long inv(long long a,long long n)
{
  long long d , x , y;
  extend_gcd(a,n,d,x,y);
  return d==1? (x+n) % n : -1;
}


int main(int argc,char *argv[])
{     
   
  return 0;
}
