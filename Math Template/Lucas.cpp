#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
typedef long long ll;
using namespace std;
const int maxn = 2e5 + 500;

ll q_pow_mod(ll x,ll y,ll p)
{
   long long res = 1;
   res %= p;
   while(y)
    {
       if (y & 1)
        res = (res*x) % p;
       y >>= 1;
       x = (x*x) % p;
	}
   return res;
}



ll fac[maxn];
void init_fac(ll p)
{
   fac[0] = 1;
   for(int i = 1 ; i <= p ; ++ i)
    fac[i] = fac[i-1]*i % p;
}


ll Lucas(ll x,ll y,ll p)
{
   ll ans = 1;
   while(x && y)
    {
    	ll newx = x % p, newy = y % p;
    	if (newx < newy) return 0;
    	ans = ans*fac[newx]*q_pow_mod(fac[newy]*fac[newx-newy]%p,p-2,p)%p;
    	x /= p;
    	y /= p;
	}
   return ans;
}



int main(int argc,char *argv[])
{
  int Case;
  scanf("%d",&Case);
  while(Case--)
   {
   	 ll n,p;
   	 scanf("%lld%lld",&n,&p);
   	 init_fac(p);
   	 printf("%lld\n",(Lucas(n*2,n,p) % p - Lucas(n*2,n-1,p) % p + p ) % p);
   }
  return 0;
}