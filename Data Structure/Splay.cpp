namespace Splay{
	int ch[maxn][2] , s[maxn] , root , fa[maxn];
	int lzy[maxn];
	stack < int > allocate , stk;
	pair < int , int > key[maxn];

	void Add( int x , int y ){
		key[x].first += y;
		lzy[x] += y;
	}

	inline void up(int x){
		s[x] = s[ch[x][0]] + s[ch[x][1]] + 1;
    }

    void ReleaseLabel( int x ){
        if( !lzy[x] )
            return;
    	if( ch[x][0] )
    		Add( ch[x][0] , lzy[x] );
    	if( ch[x][1] )
    		Add( ch[x][1] , lzy[x] );
    	lzy[x] = 0;
    }

    void Debug( int u , int par = 0 ){
    	ReleaseLabel( u );
        assert( fa[u] == par );
    	printf( "id is %d , key is (%d,%d) , size is %d , fa is %d , lson is %d , rson is %d\n" , u , key[u].first , key[u].second , s[u] , fa[u] , ch[u][0] , ch[u][1] );
    	if( ch[u][0] )
    		Debug( ch[u][0] , u );
    	if( ch[u][1] )
    		Debug( ch[u][1] , u );
    }

    void rotate( int x, int d ){
        int y = fa[x];
        ch[y][d ^ 1] = ch[x][d];
        if ( ch[x][d] ) fa[ch[x][d]] = y;  
        fa[x] = fa[y];
        if (fa[y]){
            if (y == ch[fa[y]][d])  ch[fa[y]][d] = x;
            else  ch[fa[y]][d ^ 1] = x;
        }
        ch[x][d] = y , fa[y] = x;
        up( y ) , up( x );
    }

    void Splay( int x , int target ){
        int y = x;
        while( y ^ target )
            stk.push( y ),
            y = fa[y];
        while( !stk.empty() )
            ReleaseLabel( stk.top() ),
            stk.pop();
    	while( fa[x] != target ){
    		int y = fa[x];
    		if( x == ch[y][0] ){
    			if( fa[y] != target && y == ch[fa[y]][0])
    				rotate( y , 1 );
    			rotate( x , 1 );
    		}else{
    			if( fa[y] != target && y == ch[fa[y]][1])
    				rotate( y , 0 );
    			rotate( x , 0 );
    		}
    	}
    	if( !target ) root = x;
    }

    void Insert( int & x , pair < int , int > val , int par = 0 ){
    	if( x == 0 ){
    		x = allocate.top(); allocate.pop();
    		ch[x][0] = ch[x][1] = 0 , s[x] = 1 , key[x] = val , lzy[x] = 0 , fa[x] = par;
    		Splay( x , 0 );
    	}else{
    		int cur = x;
    		ReleaseLabel( cur );
    		if( val < key[x] ) Insert( ch[x][0] , val , x );
    		else Insert( ch[x][1] , val , x );
    	}
    }

    void Delete(){
    	ReleaseLabel( root );
    	allocate.push( root );
    	if( !ch[root][0] && !ch[root][1] ){
    		root = 0;
    		return ;
    	}
    	if( !ch[root][0] )
    		root = ch[root][1] , fa[root] = 0;
    	else if( !ch[root][1] )
    		root = ch[root][0] , fa[root] = 0;
    	else{
    		int x = ch[root][0];
    		while( ch[x][1] )
    			x = ch[x][1];
    		Splay( x , root );
    		fa[ch[root][1]] = x;
    		ch[x][1] = ch[root][1];
    		root = x;
    		fa[root] = 0;
    		up( root );
    	}
    }

    int Kth( int x , int k ){
    	ReleaseLabel( x );
    	if( k == s[ch[x][0]] + 1 ){
    		Splay( x , 0 );
    		return key[x].first;
    	}
    	else if( k <= s[ch[x][0]] ) return Kth( ch[x][0] , k );
    	else return Kth( ch[x][1] , k - s[ch[x][0]] - 1 );
    }

    int pred( int t , pair < int , int > v ){
    	if( t == 0 ) return -1;
    	ReleaseLabel( t );
    	if( v <= key[t] ) return pred( ch[t][0] , v );
    	else{
    		int rs = pred( ch[t][1] , v );
    		if( rs == -1 ) return t;
    		return rs;
    	}
    }

    int succ( int t , pair < int , int > v ){
    	if( t == 0 ) return -1;
    	ReleaseLabel( t );
    	if( v >= key[t] ) return succ( ch[t][1] , v );
    	else{
    		int rs = succ( ch[t][0] , v );
    		if( rs == -1 ) return t;
    		return rs;
    	}
    }

};