#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 500;
int dp[40500][205] , vis[maxn] , prime[maxn] , tot ;

void init(){
    for(int i = 2 ; i <= 1e6 ; ++ i)
    if(!vis[i]){
        prime[tot++] = i;
        for(int j = i * 2 ; j <= 1e6 ; j += i) vis[j] = 1;
    }
}

int cal(int x){
    int l = 0 , r = tot - 1;
    while(l<=r){
        int mid = l + ((r-l)>>1);
        if(1LL * prime[mid] * prime[mid] <= x) l = mid + 1;
        else r = mid - 1;
    }
    return prime[l-1];
}

int dfs(int x , int y){
    if( y <= 1 ) return max( 0 , x - 1);
    int flag = (x <= 4e4 && y <= 200);
    if(1LL * y * y > x) return dfs( x , cal(x) );
    if(vis[y]) return dfs( x , prime[upper_bound( prime , prime + tot , y ) - prime - 1 ] );
    if(flag && ~dp[x][y]) return dp[x][y];
    long long ans = dfs( x , y - 1 ) - ( dfs( x / y , y - 1) - dfs( y - 1 , sqrt(y - 1) ) );
    if(flag) dp[x][y] = ans;
    return ans;
}

int main(int argc,char *argv[]){
    init();
    memset(dp,-1,sizeof(dp));
    int l , r ;
    while(scanf("%d%d",&l,&r)){
        if(l == 0 && r == 0) break; l--;
        printf("%d\n",dfs(r,sqrt(r)) - dfs(l,sqrt(l)));
    }
    return 0;
}
