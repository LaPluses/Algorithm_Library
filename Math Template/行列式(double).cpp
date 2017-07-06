double Det(){
	//-- N;
	double ans = 1;
	int cur = 0 , sgn = 1;
	for(int i = 0 ; i < N ; ++ i){
		int nxt = -1;
		for( int j = cur ; j < N ; ++ j) if( fabs(mat[j][i]) > eps ){
			nxt = j ; 
			break ;
		}
		if( nxt == -1 ) continue;
		for( int j = 0 ; j < N ; ++ j) swap( mat[cur][j] , mat[nxt][j] );
		if( nxt != cur ) sgn = - sgn;
		for( int j = 0 ; j < N ; ++ j ) if( j != cur ){
			double s = mat[j][i] / mat[cur][i];
			for( int k = i ; k < N ; ++ k) mat[j][k] -= s * mat[cur][k];
		}
		++ cur ;
	}
	for( int i = 0 ; i < N ; ++ i) ans = ans * mat[i][i];
	return ans * sgn;
}