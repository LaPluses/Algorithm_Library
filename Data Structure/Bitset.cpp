namespace Bitset{
	using ull = unsigned long long;
	const int Maxsz = 100;

	void lftmove( ull * x , ull * y , int z ){
		memset( y , 0 , Maxsz << 3 );
		if( z >= Maxsz * 60 ) return;
		for(int i = Maxsz - 1 - z / 64 , j = Maxsz - 1 ; i >= 0 ; -- i , -- j)
			y[j] = x[i];
		int s = z % 64;
		y[Maxsz - 1]<<=(ull)s;
		for(int i = Maxsz - 2 ; i >= 0 ; -- i){
			if( s ) y[i + 1] |= (y[i] >> (64ULL - s));
			y[i] <<= (ull)s;
		}
	}

	void rightmove( ull * x , ull * y , int z ){
		memset( y , 0 , Maxsz << 3 );
		if( z >= Maxsz * 60 ) return;
		for(int i = z / 64 , j = 0 ; i < Maxsz ; ++ i , ++ j)
			y[j] = x[i];
		int s = z % 64;
		y[0] >>= (ull)s;
		for(int i = 1 ; i < Maxsz ; ++ i){
			if( s ) y[i - 1] |= (y[i] << (64ULL - s));
			y[i] >>= (ull)s;
		}
	}
}