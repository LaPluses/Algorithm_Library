int Det(){
	int cur = 0 , sgn = 1;
	for( int i = 0 ; i < N ; ++ i){
		int nxt = -1;
		for( int j = cur ; j < N ; ++ j) if( mat[j][i]){
			nxt = j ;
			break ;
		}
		if( nxt == -1 ) return 0;
		if( nxt != cur ) sgn = - sgn;
		for( int j = 0 ; j < N ; ++ j) swap( mat[cur][j] , mat[nxt][j] );
		for( int j = cur + 1 ; j < N ; ++ j){
			while( mat[j][i] ){
				int x = mat[j][i] / mat[cur][i];
				if( x ){
					for( int k = i ; k < N ; ++ k){
						mat[j][k] -= mul( mat[cur][k] , x ) ;
						Maintain(mat[j][k]);
					}
				}else{
					for( int k = i ; k < N ; ++ k) swap( mat[j][k] , mat[cur][k] );
					sgn = - sgn;
				}
			}
		}
		++ cur;
	}
	int ans = 1;
	for( int i = 0 ; i < N ; ++ i ) ans = mul( ans , mat[i][i] );
	if( sgn == -1 ) ans = P - ans;
    return ans;
}