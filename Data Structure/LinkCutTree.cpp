namespace LinkCutTree{
	const int maxn = 3e4 + 500;

	int ch[maxn][2] , parent[maxn] , nodetype[maxn];
	int cost[maxn] , sum[maxn] , rev[maxn] , stk[maxn];

	void Update( int Node ){
		sum[Node] = cost[Node] + sum[ch[Node][0]] + sum[ch[Node][1]];
	}

	inline void Reverse( int Node ){
		nodetype[ch[Node][0]] = 1 , nodetype[ch[Node][1]] = 0;
		swap( ch[Node][0] , ch[Node][1] );
		rev[Node] ^= 1;
	}

	void ReleaseLabel( int Node ){
		if( rev[Node] ){
			Reverse( ch[Node][0] );
			Reverse( ch[Node][1] );
			rev[Node] = 0;
		}
	}

	void Rotate( int Node , int x ){
		int p = parent[Node] , y = nodetype[p] , tmp = parent[p];
		parent[Node] = tmp , nodetype[Node] = y;
		if( y != 2 ) ch[tmp][y] = Node;
		y = x ^ 1 , tmp = ch[Node][y] , ch[p][x] = tmp , parent[tmp] = p , nodetype[tmp] = x ;
		parent[p] = Node , nodetype[p] = y , ch[Node][y] = p;
		Update( p );
	}

	void Splay( int Node ){
		int tmp = Node , len = 0;
		while( nodetype[tmp] != 2 )
			stk[len ++ ] = tmp , tmp = parent[tmp];
		stk[len ++ ] = tmp;
		for(int i = len - 1 ; i >= 0 ; -- i)
			ReleaseLabel( stk[i] );
		int a = nodetype[Node];
		while( a != 2 && Node ){
			int p = parent[Node] , b = nodetype[p];
			if( a == b ) Rotate( p , a );
			else Rotate( Node , a );
			if( b == 2 )
				break;
			Rotate( Node , b );
			a = nodetype[Node];
		}
		Update( Node );
	}

	pair < int , int > Access( int Node ){
		int u = Node , v = 0;
		pair < int , int > ret;
		while( u ){
			Splay( u );
			if( !parent[u] )
				ret = make_pair( ch[u][1] , u );
			if( ch[u][1] )
				nodetype[ch[u][1]] = 2,
				parent[ch[u][1]] = u;
			nodetype[v] = 1 , parent[v] = u , ch[u][1] = v;
			Update( u );
			v = u ;
			u = parent[u] ;
		}
		return ret;
	}

	int FindRoot( int x ){
		Access( x );
		Splay( x );
		while( ch[x][0] )
			x = ch[x][0];
		Splay( x );
		return x;
	}

	void Link( int u , int v ){
		Access( u );
		Splay( u );
		Reverse( u );
		parent[u] = v;
	}

};