#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 500;

const long long Mod = 998244353;   // 模数
const long long SpMul = 3;  // 原根
long long qpow(long long a,long long k)  
{  
    long long res=1LL;  
    while(k>0)  
    {  
        if(k&1)res=res*a%Mod;  
        a=a*a%Mod;  
        k>>=1;
    }  
    return res;  
}  
void Change(long long y[],int len)  
{  
    for(int i=1,j=len/2;i<len-1;i++)  
    {  
        if(i<j)swap(y[i],y[j]);  
        int k=len/2;  
        while(j>=k)  
        {  
            j-=k;  
            k/=2;  
        }  
        if(j<k)j+=k;  
    }  
}  


void NTT(long long y[],int len,int on)  
{  
    Change(y,len);  
    for(int h=2;h<=len;h<<=1)  
    {  
        long long wn=qpow(SpMul,(Mod-1)/h);  
        if(on==-1)wn=qpow(wn,Mod-2);  
        for(int j=0;j<len;j+=h)  
        {  
            long long w=1LL;  
            for(int k=j;k<j+h/2;k++)  
            {  
                long long u=y[k];  
                long long t=w*y[k+h/2]%Mod;  
                y[k]=(u+t)%Mod;  
                y[k+h/2]=(u-t+Mod)%Mod;  
                w=w*wn%Mod;  
            }  
        }  
    }  
    if(on==-1)  
    {
        long long t=qpow(len,Mod-2);
        for(int i=0;i<len;i++)
            y[i]=y[i]*t%Mod;  
    }
}

int seq[60][maxn << 1] , ptr = 0;
long long B[maxn << 1] , C[maxn << 1];

int DFS( int l , int r ){
	if( l == r ){
		int id = ptr ++ ;
		seq[id][1] = l ;
		seq[id][0] = 1 ;
		return id;
	}else{
		int mid = l + r >> 1;
		int lid = DFS( l , mid );
		int rid = DFS( mid + 1 , r );
		ptr -= 2;
		int newid = ptr ++ ;
		int len = 1;
		while( len <= r - l + 1 ) len <<= 1;
		for(int i = 0 ; i < len ; ++ i) B[i] = seq[lid][i] , C[i] = seq[rid][i] , seq[lid][i] = seq[rid][i] = 0;
		NTT( B , len , 1 );
		NTT( C , len , 1 );
		for(int i = 0 ; i < len ; ++ i) B[i] = B[i] * C[i] % Mod;
		NTT( B , len , -1 );
		for(int i = 0 ; i < len ; ++ i) seq[newid][i] = B[i];
		return newid;
	}
}

int me[1005][1005];

int mul( int x , int y){
	return 1LL * x * y % Mod;
}

int S( int p , int k ){
	if( k == 0 ) return 0;
	if( p == k ) return 1;
	if( ~me[p][k] ) return me[p][k];
	int rs = S( p - 1 , k - 1 ) + mul( p - 1 , S( p - 1 , k ) );
	if( rs >= Mod ) rs -= Mod;
	me[p][k] = rs;
	return rs;
}

int main( int argc , char * argv[] ){
	memset( me , - 1, sizeof( me ) );
	int N , L , R ;
	cin >> N;
	//cin >> N >> L >> R;
	int id = DFS( 0 , N - 1 );
	for(int i = N ; i >= 0 ; -- i){
		printf( "f[%d] is %d \n" , N - i , seq[id][i] );
	}
	return 0;
}