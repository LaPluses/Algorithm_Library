const int maxn = 100 + 15;
const int mod = 1000000003;

void up( int & x , int v ){
	x += v;
	if( x >= mod ) x -= mod;
}

inline int mul( int x , int y ){ return 1LL * x * y % mod ;}

int n , p[maxn] , dp[maxn][2] , dp2[maxn][2]  , target ;

int solve( int target ){
	int rs = 0 , bit ;
	for(bit = 30 ; bit >= 0 ; -- bit){
		memset( dp , 0 , sizeof( dp ) );
		memset( dp2 , 0 , sizeof( dp2 ) );
		dp[0][0] = dp2[n + 1][0] = 1;
		for(int i = 0 ; i < n ; ++ i) for(int f = 0 ; f < 2 ; ++ f) if( dp[i][f] ){
			if( p[i + 1] >> bit & 1 ){
				up( dp[i + 1][f ^ 1] , mul( dp[i][f] , (p[i + 1]&((1<<bit)-1))+1 ));
				up( dp[i + 1][f] , mul( dp[i][f] , 1 << bit ) );
			}else up( dp[i + 1][f] , mul( dp[i][f] , (p[i + 1]&((1<<bit)-1))+1 ));
		}
		for(int i = n + 1 ; i > 1 ; -- i) for(int f = 0 ; f < 2 ; ++ f) if( dp2[i][f] ){
			if( p[i - 1] >> bit & 1 ) up( dp2[i - 1][f ^ 1] , mul( dp2[i][f] , (p[i - 1]&((1<<bit)-1))+1 ));
			else up( dp2[i - 1][f] , mul( dp2[i][f] , (p[i - 1]&((1<<bit)-1))+1 ));
		}
		int pre = 0 ;
		for(int i = n; i >= 1 ; -- i){
			if( p[i] >> bit & 1 ) for(int j = 0 ; j < 2 ; ++ j) up( rs , mul( dp[i - 1][j] , dp2[i + 1][ (target >> bit & 1) ^ j ] ) );
			pre ^= ( p[i] >> bit & 1 );
		}
		if( pre != ( target >> bit & 1 ) ) break;
	}
	return rs + (bit == -1);
}