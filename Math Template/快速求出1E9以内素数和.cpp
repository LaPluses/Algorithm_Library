#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 50;
long long dp[maxn][105];
int vis[maxn * 100] , tot , prime[maxn * 100] ;

int cal(long long x){
    int l = 0 , r = tot - 1;
    while(l <= r){
        int mid = l + ( (r-l) >> 1);
        if( 1LL * (long long)prime[mid] * prime[mid] <= x) l = mid + 1;
        else r = mid - 1;
    }
    return prime[l-1];
}

long long dfs(int x , int y){
    if(y <= 1) return ( 1LL * (x + 2) * (x - 1) ) >> 1LL; //±ß½çÌõ¼þ
    int flag = ( x <= 1e4 && y <= 1e2);
    if( 1LL * y * y > x) return dfs( x , cal(x)); //find
    if( vis[y] ) return dfs( x , prime[upper_bound(prime , prime + tot , y ) - prime - 1] );
    if(flag && ~dp[x][y]) return dp[x][y];
    long long ans = 0;
    ans = dfs( x , y - 1 ) - 1LL * y * ( dfs(x / y , y - 1 ) - dfs( y - 1 , cal( y - 1 )) );
    if(flag) dp[x][y] = ans;
    return ans;
}

void init(){
    for(int i = 2 ; i <= 1e6 ; ++ i)
    if(!vis[i]){
        prime[tot++] = i;
        for(int j = i * 2 ; j <= 1e6 ; j += i) vis[j] = 1;
    }
}

int main(int argc,char *argv[]){
    init();
    memset( dp , -1 , sizeof(dp) );
    int yy = 1e8;
    cout << dfs(yy , sqrt(yy)) << endl;
    return 0;
}
