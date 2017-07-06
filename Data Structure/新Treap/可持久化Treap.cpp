namespace Treap{
	const int maxn = 3e6 + 50;
	int ch[maxn][2] , key[maxn] , weight[maxn] , tot , sz[maxn];

	void Init(){
		tot = 0;
	}

	int NewNode( int l , int r , int _key , int _weight ){
		int ret = ++ tot;
		ch[ret][0] = l , ch[ret][1] = r , key[ret] = _key , weight[ret] = _weight;
		sz[ret] = 1 + sz[l] + sz[r];
		return ret;
	}

	int Merge( int x , int y ){
		if( !x || !y ) return x ? x : y;
		return weight[x] < weight[y] ? NewNode( ch[x][0] , Merge( ch[x][1] , y ) , key[x] , weight[x] ) : NewNode( Merge( x , ch[y][0] ) , ch[y][1] , key[y] , weight[y] );
	}

	int Split_l( int x , int _key ){
		if( !x ) return 0;
		return key[x] <= _key ? NewNode( ch[x][0] , Split_l( ch[x][1] , _key ) , key[x] , weight[x] ) : Split_l( ch[x][0] , _key );
	}

	int Split_r( int x , int _key ){
		if( !x ) return 0;
		return key[x] > _key ? NewNode( Split_r( ch[x][0] , _key ) , ch[x][1] , key[x] , weight[x] ) : Split_r( ch[x][1] , _key );
	}

	int Insert( int root , int y ){
		return Merge( Split_l( root , y ) , Merge( NewNode( 0 , 0 , y , rand() ) , Split_r( root , y ) ) );
	}
}