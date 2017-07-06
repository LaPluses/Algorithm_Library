#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 500;
const int mod = 1e9 + 7;
const int p = 233;

vector < int > G1[maxn] , G2[maxn];
int N , tota , totb , pr1 , pr2 , match[maxn] , fa[maxn] , f1[maxn] , f2[maxn] , fb[maxn] , dp[maxn] , power[maxn] , f[maxn] , sz[maxn] , g[maxn] , prefix[maxn] , suffix[maxn];
pair < int , int > tf1[maxn] , tf2[maxn];
pair < int , int > seq[maxn];
char s1[maxn * 21] , s2[maxn * 21];
unordered_map < int , int > id1 , id2 ;
unordered_map < int , pair < char * , int > > pos1 , pos2;
pair < int , int > temp1[maxn] , temp2[maxn];

inline int mul( int x , int y ){
    return 1LL * x * y % mod;
}

inline void upd( int & x , int v ){
    x += v;
    if( x >= mod )
        x -= mod;
}

void PreDeal(){
    tota = totb = pr1 = pr2 = 0;
    pos1.clear() ; pos2.clear();
    for(int i = 1 ; i <= N ; ++ i)
        G1[i].clear(),
        G2[i].clear();
    id1.clear();
    id2.clear();
}

int extend( unordered_map < int , int > & id , int x , int & tot ){
    if( id.count( x ) )
        return id[x];
    id[x] = ++ tot;
    return tot;
}

int CalHash( char * s , int len ){
    int ans = 0;
    for(int i = 0 ; i < len ; ++ i){
        ans = mul( ans , p ) + s[i] ;
        if( ans >= mod )
            ans -= mod;
    }
    return ans;
}

void DFS( int u , int fa , vector < int > (& wr)[maxn] , int * temp){
    dp[u] = 0;
    sz[u] = 1;
    for(auto v : wr[u]){
        if( v == fa )
            continue;
        DFS( v , u , wr , temp );
        sz[u] += sz[v];
    }
    int len = 0;
    for(auto v : wr[u]){
        if( v == fa )
            continue;
        seq[ ++ len] = make_pair( dp[v] , sz[v] );
    }
    sort( seq + 1 , seq + len + 1 );
    dp[u] = sz[u];
    for(int i = 1 ; i <= len ; ++ i){
        dp[u] = mul( dp[u] , power[seq[i].second] );
        upd( dp[u] , seq[i].first );
    }
    temp[u] = dp[u];
}

void Cal( int u , int fa , vector < int > (& wr)[maxn] ){
    int len = 0;
    for(auto v : wr[u]){
        if( v == fa )
            seq[ ++ len ] = make_pair( f[u] , N - sz[u] );
        else
            seq[ ++ len ] = make_pair( dp[v] , sz[v] );
    }
    sort( seq + 1 , seq + len + 1 );
    prefix[0] = 0;
    suffix[len + 1] = 0;
    for(int i = 1 ; i <= len ; ++ i){
        prefix[i] = mul( prefix[i - 1] , power[seq[i].second] );
        upd( prefix[i] , seq[i].first );
    }
    for(int i = len ; i >= 1 ; -- i)
        suffix[i] = suffix[i + 1] + seq[i].second;
    int hashu = prefix[len];
    f[u] = hashu;
    for(auto v : wr[u]){
        if( v == fa )
            continue;
        else{
            int id = lower_bound( seq + 1 , seq + len + 1 , make_pair( dp[v] , sz[v] ) ) - seq;
            assert( seq[id] == make_pair( dp[v] , sz[v] ) );
            int ret = mul( power[suffix[id + 1]] , prefix[id] );
            ret = mod - ret;
            int newhash = hashu;
            upd( newhash , ret );
            upd( newhash , mul( prefix[id - 1] , power[suffix[id + 1]] ) );
            f[v] = newhash;
            upd( f[v] , mul( N - sz[v] , power[ N - 1 - sz[v] ] ) );
        }
    }
    upd( f[u] , mul( N , power[N - 1] ) );
    for(auto v : wr[u]){
        if( v == fa )
            continue;
        Cal( v , u , wr );
    }
}

void DisplayA( int id ){
    int ha = fa[id];
    pair < char * , int > p = pos1[ha];
    for( int i = 1 ; i <= p.second ; ++ i , p.first ++ )
        putchar( *p.first );
}

void DisplayB( int id ){
    int ha = fb[id];
    pair < char * , int > p = pos2[ha];
    for( int i = 1 ; i <= p.second ; ++ i , p.first ++ )
        putchar( *p.first );
}

void DFS2( int root1 , int root2 , int fa1 , int fa2 ){
	int len1 = 0 , len2 = 0;
	for(auto v : G1[root1])
		if( v != fa1 )
			temp1[++len1] = make_pair( f1[v] , v );
	for(auto v : G2[root2])
		if( v != fa2 )
			temp2[++len2] = make_pair( f2[v] , v );
	sort( temp1 + 1 , temp1 + len1 + 1 );
	sort( temp2 + 1 , temp2 + len2 + 1 );
	for(int i = 1 ; i <= len1 ; ++ i)
		match[temp1[i].second]=temp2[i].second;
	for(auto v : G1[root1])
		if( v != fa1 )
			DFS2( v , match[v] , root1 , root2 );
}

int main( int argc , char * argv[] ){
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
    power[0] = 1;
    for(int i = 1 ; i < maxn ; ++ i)
        power[i] = mul( power[i - 1] , p );
    while(~scanf( "%d" , & N ) ){
        PreDeal();
        for(int i = 2 ; i <= N ; ++ i){
            scanf( "%s" , s1 + pr1 );
            int len = strlen( s1 + pr1 );
            int r1 = CalHash( s1 + pr1 , len );
            int ia = extend( id1 , r1 , tota );
            fa[ia] = r1;
            pos1[r1] = make_pair( s1 + pr1 , len );
            pr1 += len;
            scanf( "%s" , s1 + pr1 );
            len = strlen( s1 + pr1 );
            int r2 = CalHash( s1 + pr1 , len );
            int ib = extend( id1 , r2 , tota );
            pos1[r2] = make_pair( s1 + pr1 , len );
            fa[ib] = r2;
            pr1 += len;
            G1[ia].push_back( ib );
            G1[ib].push_back( ia );
        }
        for(int i = 2 ; i <= N ; ++ i){
            scanf( "%s" , s2 + pr2 );
            int len = strlen( s2 + pr2 );
            int r1 = CalHash( s2 + pr2 , len );
            int ia = extend( id2 , r1 , totb );
            pos2[r1] = make_pair( s2 + pr2 , len );
            fb[ia] = r1;
            pr2 += len;
            scanf( "%s" , s2 + pr2 );
            len = strlen( s2 + pr2 );
            int r2 = CalHash( s2 + pr2 , len );
            int ib = extend( id2 , r2 , totb );
            pos2[r2] = make_pair( s2 + pr2 , len );
            fb[ib] = r2;
            pr2 += len;
            G2[ia].push_back( ib );
            G2[ib].push_back( ia );
        }
        DFS( 1 , 0 , G1 , f1 );
        Cal( 1 , 0 , G1 );
        for(int i = 1 ; i <= N ; ++ i) tf1[i] = make_pair( f[i] , i );
        sort( tf1 + 1 , tf1 + N + 1 );
        DFS( 1 , 0 , G2 , f2 );
        Cal( 1 , 0 , G2 );
        for(int i = 1 ; i <= N ; ++ i) tf2[i] = make_pair( f[i] , i );
        sort( tf2 + 1 , tf2 + N + 1 );
    	int root1 = tf1[1].second , root2 = tf2[1].second;
    	DFS( root1 , 0 , G1 , f1 );
    	DFS( root2 , 0 , G2 , f2 );
    	match[root1] = root2;
    	DFS2( root1 , root2 , 0 , 0 );
    	for(int i = 1 ; i <= N ; ++ i){
    		DisplayA( i );
    		putchar( 32 );
    		DisplayB( match[i] );
    		puts("");
    	}
    }
    return 0;
}