const int maxn = 1e6;
const int Sqrt_N = 1e3;
int pre[maxn + 1] , decomp[maxn + 1][3] , dp[Sqrt_N + 1][Sqrt_N + 1];

int Ask( int a , int y ){
	int x[3] , g = 1 ;
	for(int i = 0 ; i < 3;  ++ i) x[i]=decomp[a][i];
	for(int i = 0 ; i < 3 ; ++ i){
		int d = 1;
		if( x[i] <= Sqrt_N ) d = dp[x[i]][y % x[i]];
		else if( y % x[i] == 0 ) d = x[i];
		g *= d;
		y /= d;
	}
	return g;
}

int Ask2( int a , int b ){
	int x[3] , y[3] , g = 1 ;
	for(int i = 0 ; i < 3;  ++ i) x[i]=decomp[a][i] , y[i] = decomp[b][i];
	for(int i = 0 ; i < 3 ; ++ i)
		for(int j = 0 ; j < 3 ; ++ j){
			int d = 1;
			if( max( x[i] , y[j] ) <= Sqrt_N ) d = dp[x[i]][y[j]];
			else if( x[i] == y[j] ) d = x[i];
			g *= d;
			x[i] /= d;
			y[j] /= d;
		}
	return g;
}

void Construction(){
	for(int i = 2 ; i <= maxn ; ++ i)
		if(!pre[i])
			for(int j = i ; j <= maxn ; j += i) if( !pre[j] ) pre[j] = i;
	decomp[1][0]=decomp[1][1]=decomp[1][2]=1;
    for(int i = 2 ; i <= maxn ; ++ i){
    	int p = pre[i] , pos = 0;
    	for(int j = 0 ; j < 3 ; ++ j){
    		decomp[i][j]=decomp[i/p][j];
    		if(decomp[i][j]<decomp[i][pos]) pos = j;
    	}
    	decomp[i][pos]*=p;
    }
    for(int i = 1 ; i <= Sqrt_N ; ++ i) dp[i][i] = dp[i][0] = dp[0][i] = i;
    for(int i = 1 ; i <= Sqrt_N ; ++ i)
    	for(int j = 1 ; j <= i - 1 ; ++ j)
    		dp[i][j] = dp[j][i] = dp[i - j][j];
}