	e[0] = 1;
	for(int i = 1 ; i <= n ; ++ i){
		for(int j = 1 ; j <= i ; ++ j){
			int rs = mul( e[i - j] , p[j] );
			if( (j - 1) & 1 ) rs = mod - rs;
			up( e[i] , rs );
		}
		e[i] = mul( e[i] , qpow( i , mod - 2  ) );
	}