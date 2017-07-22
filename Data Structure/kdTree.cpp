namespace Kdtree{

	const static int Maxn = 1e5 + 50;
	static int Dim = 5;
	struct Point{
		int x[5];
	}p[Maxn << 2];
	int isok[Maxn << 2];
	priority_queue < pair < long long , int > > pq;

	long long Cal( const Point & x , const Point & y ){
		long long ret = 0;
		for(int i = 0 ; i < Dim ; ++ i)
			ret += 1LL * ( x.x[i] - y.x[i] ) * ( x.x[i] - y.x[i] );
		return ret;
	}

	void Build( int l , int r , Point s[] , int o = 1 , int k = 0 ){
		if( l > r )
			return;
		int mid = l + r >> 1;
		isok[o] = 1 , isok[o << 1] = isok[o << 1 | 1] = 0;
		nth_element( s + l , s + mid , s + r + 1 , [ & ]( const Point & x , const Point & y ){
			return x.x[k] < y.x[k];
		} );
		p[o] = s[mid];
		int nexv = ( k + 1 == Dim ) ? 0 : k + 1;
		Build( l , mid - 1 , s , o << 1 , nexv );
		Build( mid + 1 , r , s , o << 1 | 1 , nexv );
	}

	void query( Point x , int m , int o = 1 , int k = 0 ){
		if( !isok[o] )
			return;
		int lft = o << 1 , rht = o << 1 | 1 , nexv = ( k + 1 == Dim ) ? 0 : k + 1;
		if( x.x[k] > p[o].x[k] )
			swap( lft , rht );
		query( x , m , lft , nexv );
		while( pq.size() >= m && Cal( p[o] , x ) < pq.top().first )
			pq.pop();
		if( pq.size() < m )
			pq.push( make_pair( Cal( p[o] , x ) , o ) );
		if( 1LL * ( x.x[k] - p[o].x[k] ) * ( x.x[k] - p[o].x[k] ) < pq.top().first )
			query( x , m , rht , nexv );
	}

};