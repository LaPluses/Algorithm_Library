#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6;
long long n,dp[1005][1005],prime[maxn + 1];
int vis[maxn + 1],tot,prime2[maxn + 1];

void init(){
	for(int i = 2 ; i <= maxn ; ++ i)
	{
		if(!vis[i]) prime2[tot] = i , prime[tot++] = 1LL*i *i;
		for(int j = 0 ; j < tot && i * prime2[j] <= maxn ; ++ j){
			vis[i * prime2[j]] = 1;
			if(i % prime2[j] == 0) break;
		}
	}
}

long long dfs(long long x , int y){
	if(prime[y] > x) return dfs( x , upper_bound( prime , prime + tot , x ) - prime - 1);
	if(x == 0 || y == -1) return x;
	if(x <= 1000 && y <= 1000 && ~dp[x][y]) return dp[x][y];
	long long res = - dfs( x / prime[y] , y - 1 ) + dfs( x , y - 1 );
	if(x <= 1000 && y <= 1000) dp[x][y] = res;
	return res;
}

int main(int argc,char *argv[]){
	init();
	memset(dp,-1,sizeof(dp));
	int Case;
	scanf("%d",&Case);
	while(Case--){
		scanf("%lld",&n);
		assert( n > 1e11);
		printf("%lld\n",dfs(n,tot-1));
	}
	return 0;
}