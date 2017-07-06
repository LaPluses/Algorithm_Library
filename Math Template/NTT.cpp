const int mod = 998244353;   // 模数
const int Root = 3;  // 原根

inline int mul( int x , int y ){
	return 1LL * x * y % mod;
}

inline void upd( int & x , int v ){
	x += v;
	if( x >= mod )
		x -= mod;
}

int power_mod( int x , int y ){
	int ret = 1;
	while( y ){
		if( y & 1 )
			ret = mul( ret , x );
		y >>= 1;
		x = mul( x , x );
	}
	return ret;
}

void Change( int y[] , int len ){  
	for(int i = 1 , j = ( len >> 1 ) ; i < len - 1 ; ++ i ){
		if( i < j )
			swap( y[i] , y[j] );
		int k = len >> 1;
		while( j >= k ){
			j -= k;
			k >>= 1;
		}
		if( j < k )
			j += k;
	}
}

void NTT( int y[] , int len , int on ){
	Change( y , len );
	for( int h = 2 ; h <= len ; h <<= 1 ){
		int wn = power_mod( Root , (mod - 1) / h );
		if( on == -1 ) wn = power_mod( wn , mod - 2 );
		for( int j = 0 ; j < len ; j += h){
			int w = 1;
			for(int k = j ; k < j + (h >> 1) ; ++ k){
				int u = y[k] , t = mul( w , y[k + (h >> 1)] );
				upd( y[k] , t );
				y[k + (h >> 1)] = (u - t + mod);
				if( y[k + (h >> 1)] >= mod )
					y[k + (h >> 1)] -= mod;
				w = mul( w , wn );
			}
		}
	}

    if( on == -1 ){
    	int t = power_mod( len , mod - 2 );
    	for( int i = 0 ; i < len ; ++ i )
    		y[i] = mul( y[i] , t );
    }
}