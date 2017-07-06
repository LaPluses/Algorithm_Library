const int maxn = 300 ;
const int inf = 1e9;

int mat[maxn + 1][maxn + 1];

int lx[maxn + 1];
int ly[maxn + 1];
int slack[maxn + 1];
int S[maxn + 1];
int T[maxn + 1];
int lft[maxn + 1];

bool dfs( int x , int N ){
	S[x] = 1;
	for(int i = 1 ; i <= N ; ++ i)
		if( !T[i] ){
			int gap = lx[x] + ly[i] - mat[x][i];
			if( gap == 0 ){
				T[i] = 1;
				if( lft[i] == 0 || dfs( lft[i] , N ) ){
					lft[i] = x;
					return true;
				}
			}else slack[i] = min( slack[i] , gap );
		}
	return false;
}

int solve( int N ){

	for(int i = 1 ; i <= N ; ++ i){
		lx[i] = ly[i] = lft[i] = 0;
		for(int j = 1 ; j <= N ; ++ j) lx[i] = max( lx[i] , mat[i][j] );
	}

	for(int i = 1 ; i <= N ; ++ i){
		while( 1 ){
			for(int j = 1 ; j <= N ; ++ j) slack[j] = inf , S[j] = T[j] = 0;
			if( dfs( i , N ) ) break;
			int d = inf;
			for(int j = 1 ; j <= N ; ++ j) if( !T[j] ) d = min( d , slack[j] );
			for(int j = 1 ; j <= N ; ++ j){
				if( S[j] ) lx[j] -= d;
				if( T[j] ) ly[j] += d;
			}
		}
	}
	int res = 0;
	for(int i = 1 ; i <= N ; ++ i) res += lx[i] + ly[i];
	return res;
}