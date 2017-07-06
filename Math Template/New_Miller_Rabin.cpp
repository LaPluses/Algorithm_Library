/*
10^9 : 336781006125, 9639812373923155
10^15 : 2, 4130806001517, 149795463772692060, 186635894390467037, 3967304179347715805
>= 2^64 : 2, 325, 9375, 28178, 450775, 9780504, 1795265022

*/

namespace Miller_Rabin{

	// srand( time( NULL ) ) !! if find_fac
	const int CheckTime = 5;
	long long Magic[] = {2LL, 4130806001517LL, 149795463772692060LL, 186635894390467037LL, 3967304179347715805LL};

	long long mul( long long u , long long v , long long p ){
		return (u*v-(long long)((long double)u*v/p)*p+p)%p;
	}

	long long power_mod( long long a , long long b , long long mod ){
		long long ret = 1;
		if( a >= mod )
			a %= mod;
		while( b ){
			if( b & 1 )
				ret = mul( ret , a , mod );
			b >>= 1;
			a = mul( a , a , mod );
		}
		return ret;
	}

	bool check(long long a , long long n , long long x , long long t){
	    long long ret = power_mod( a , x , n );
	    long long last = ret;
	    for(int i = 1 ; i <= t ; ++ i){
	    	ret = mul( ret , ret , n );
	    	if( ret == 1 && last != 1 && last != n - 1 )
	    		return true;
	    	last = ret;
	    }
	    if( ret != 1 )
	    	return true;
	    return false;
	}

	bool IsPrime(long long n){
	    if( n < 2 )return false;
	    if( n == 2 )return true;
	    if( (n&1)==0 ) return false;//偶数
	    long long x = n - 1 , t = 0;
	    while( !(x & 1) )
	    	x >>= 1,
	    	++ t;
	    for(int i = 0 ; i < CheckTime ; ++ i)
	    	if( check( Magic[i] % (n - 1) + 1 , n , x , t ) )
	    		return false;
	    return true;
	}

	vector < long long > Factor;
	void Divide( long long number ){
		if( number == 1 )
			return ;
		if( IsPrime( number ) ){
			Factor.emplace_back( number );
			return;
		}
		long long cycle_size = 2, x = rand() % number , x_fixed = x , factor = 1;
		while (factor == 1) {
			for(int count = 1 ; count <= cycle_size && factor <= 1 ; ++ count){
				x = mul( x , x , number ) + 1;
				if( x >= number ) x -= number;
				factor = __gcd( x - x_fixed + number , number);
			}
			cycle_size <<= 1LL;
			x_fixed = x;
			if( factor == number )
				cycle_size = 2, x = rand() % number , x_fixed = x , factor = 1;
		}
		Divide( factor );
		Divide( number / factor );
	}

};