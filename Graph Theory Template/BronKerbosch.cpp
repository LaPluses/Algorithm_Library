#define lowbit( x ) ((x)&(-x))
namespace BronKerbosch{
	const int maxn = 40;
	typedef unsigned long long ull;
	int N[maxn] , n;
	void DFS( ull r , ull p , ull x ){
		if( !p && !x )
			cout << r << endl;
		else{
			ull tr = ( 1ull << n ) - 1 , tsk = p | x;
			for(int i = 0 ; i < n ; ++ i)
				if( tsk >> i & 1 ){
					ull newtr = p & ( (1ull << i) | N[i] );
					if( __builtin_popcountll( newtr ) < __builtin_popcountll( tr ) )
						tr = newtr;
				}
			while( tr ){
				ull y = lowbit( tr );
				int v = __builtin_ctzll( y );
				DFS( r | (1ull << v) , p &~( ( 1ull << v ) | N[v] ) , x &~( ( 1ull << v ) | N[v] ) );
				p &=~ (1ull << v);
				x |= (1ull << v);
				tr -= y;
			}
		}
	}
};