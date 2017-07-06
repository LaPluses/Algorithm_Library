struct ds{

	const static int sz = 32;
	unsigned ele[sz];

	int get( int x ){
		int idx = x / 32;
		return ele[idx] >> (x %32) & 1;
	}

	void set( int x ){
		int idx = x / 32;
		ele[idx] |= (1 << (x % 32));
	}

	void clean( int x ){
		int idx = x / 32;
		ele[idx] &= ~(1 << (x % 32));
	}

	int count( ){
		int idx = M / 32 , rs = 0;
		for(int i = 0 ; i <= idx ; ++ i) rs += __builtin_popcount( ele[i] );
		return rs;
	}

	void reverse(){
		int idx = M / 32 , ed = M % 32;
		for(int i = 0 ; i < idx ; ++ i) ele[i] = ~ele[i];
		for(int i = 0 ; i < ed ; ++ i){
			if( ele[idx] >> i & 1 ){
				ele[idx] &= ~(1 << i);
			}else{
				ele[idx] |= (1 << i );
			}
		}
	}

	void copy( const ds & a ){
		memcpy( ele , a.ele , sizeof( unsigned ) * sz );
	}

};