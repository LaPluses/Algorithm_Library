#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <iomanip>
#include <string>
#include <ctime>
#include <list>
#include <bitset>
typedef unsigned char byte;
#define pb push_back
#define input_fast std::ios::sync_with_stdio(false);std::cin.tie(0)
#define local freopen("in.txt","r",stdin)
using namespace std;


void extend_gcd(long long a,long long &x,long long b,long long &y){
    if(b==0){
        x=1,y=0;
        return;
    }
    long long x1,y1;
    extend_gcd(b,x1,a%b,y1);
    x=y1;
    y=x1-(a/b)*y1;
}
long long inv(long long a,long long m){
    long long t1,t2;
    extend_gcd(a,t1,m,t2);
    return ( t1%m + m ) % m;
}
long long qpow(long long x,long long y,long long m){
    if(!y) return 1;
    long long ans=qpow(x,y>>1,m);
    ans= ans *ans %m;
    if(y&1) ans=ans *x %m;
    return ans;
}
long long nump(long long x,long long p){
    long long ans=0;
    while(x) ans += x/p, x /= p;
    return ans;
}
long long fac(long long n,long long p,long long pk){
    if(n==0) return 1;
    long long ans=1;
    for(long long i=1;i<=pk;i++){
        if(i%p==0) continue;
        ans= ans *i %pk;
    }
    ans = qpow(ans,n/pk,pk);
    long long to=n%pk;
    for(long long i=1;i<=to;i++){
        if(i%p==0) continue;
        ans = ans *i %pk;
    }
    return fac(n/p,p,pk) *ans %pk;
}
long long cal(long long n,long long m,long long p,long long pi,long long pk){
    long long a=fac(n,pi,pk),b=fac(m,pi,pk),c=fac(n-m,pi,pk);
    long long d=nump(n,pi)-nump(m,pi)-nump(n-m,pi);
    long long ans= a %pk * inv(b,pk) %pk * inv(c,pk) %pk * qpow(pi,d,pk) %pk;
    return ans * (p/pk) %p * inv(p/pk,pk) %p;
}
long long nCmmodp(long long n,long long m,long long p){
    if(n<m) return 0;
    long long ans=0;
    long long x=p;
    for(long long i=2;i*i<=x&&x>1;i++){
        long long k=0,pk=1;
        while(x%i==0){
            x /= i;
            k++;
            pk *= i;
        }
        if(k>0){
            ans =( ans + cal(n,m,p,i,pk) )%p;
        }
    }
    if(x>1) ans=( ans + cal(n,m,p,x,x) )%p;
    return ans;
}



int main(int argc,char *argv[])
{
    long long n , k , m;
    cin >> n >> k >> m;
    cout << nCmmodp(n,k,m) <<endl;
    return 0;
}