struct SplayTree{

	const static int maxn = 2e5 + 15;

	int ch[maxn][2] , s[maxn] , tot , root , fa[maxn];
	long long sum[maxn] , lzy[maxn] ;
	int index[maxn] , key[maxn];

	void init( int x , int id = 0 , int val = 0 , int par = 0 ){
		ch[x][0]=ch[x][1]=0 , fa[x]= par , key[x] = val , index[x] = id , s[x] = 1;
	}

	void init(){
		init( 0 , 0 , 0 , 0 ); s[0] = 0;
		tot = root = 0 ;
	}

	inline void up(int x){
		s[x] = s[ch[x][0]] + s[ch[x][1]] + 1;
		sum[x] = key[x];
		if( ch[x][0] ) sum[x] += sum[ch[x][0]];
		if( ch[x][1] ) sum[x] += sum[ch[x][1]];
    } 

    void update( int x , long long v ){
    	lzy[x] += v;
    	sum[x] += s[x] * v;
    	key[x] += v;
    }

    void ReleaseLabel( int x ){
    	if( lzy[x] ){
    		if( ch[x][0] ) update( ch[x][0] , lzy[x] );
    		if( ch[x][1] ) update( ch[x][1] , lzy[x] );
    		lzy[x] = 0;
    	}
    }

    void rotate( int x, int d ){
        int y = fa[x];
        //cout << "y is " << y << " lzy is " << lzy[y] << endl;
        ReleaseLabel( y );
        ReleaseLabel( x );
        ch[y][d ^ 1] = ch[x][d];
        if ( ch[x][d]) fa[ch[x][d]] = y;  
        fa[x] = fa[y];
        if (fa[y]){
            if (y == ch[fa[y]][d])  ch[fa[y]][d] = x;
            else  ch[fa[y]][d ^ 1] = x;
        }
        ch[x][d] = y , fa[y] = x;
        up( y );
        up( x );
    }

    // Splay x to target's son
    void Splay( int x , int target ){
    	ReleaseLabel( x ); // Very Improtant !!!!
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

    int insert( int & x , int id , int val , int par = 0 ){
    	int rs;
    	if( x == 0 ){
    		x = ++ tot;
    		rs = x;
    		init( tot , id , val , par );
    	}else{
    		int cur = x;
    		ReleaseLabel( cur );
    		if( id < index[x] ) rs = insert( ch[x][0] , id , val , x );
    		else rs = insert( ch[x][1] , id , val , x );
    	}
		up( x );
		return rs;
    }

    int pred( int t , int v ){
    	if( t == 0 ) return -1;
    	if( v <= index[t] ) return pred( ch[t][0] , v );
    	else{
    		int rs = pred( ch[t][1] , v );
    		if( rs == -1 ) return t;
    		return rs;
    	}
    }

    int succ( int t , int v ){
    	if( t == 0 ) return -1;
    	if( v >= index[t] ) return succ( ch[t][1] , v );
    	else{
    		int rs = succ( ch[t][0] , v );
    		if( rs == -1 ) return t;
    		return rs;
    	}
    }


    // After GotSegement( l , r ) must use Splay funtion to Modify son's information to the root
    int GetSegement( int l , int r ){
    	int s1 = pred( root , l ) , s2 = succ( root , r );
    	if( s1 == -1 && s2 == -1 ) return root;
    	else if( s1 == -1 ){
    		Splay( s2 , 0 );
    		return ch[s2][0];
    	}else if( s2 == -1 ){
    		Splay( s1 , 0 );
    		return ch[s1][1];
    	}else{
    		Splay( s1 , 0 );
    		Splay( s2 , s1 );
    		return ch[s2][0];
    	}
    }

    void Delete( int l , int r ){
    	int s1 = pred( root , l ) , s2 = succ( root , r );
    	if( s1 == -1 && s2 == -1 ){
    		fa[ch[root][0]] = 0;
    		fa[ch[root][1]] = 0;
    		root = 0;
    	}
    	else if( s1 == -1 ){
    		Splay( s2 , 0 );
    		fa[ch[s2][0]] = 0;
    		ch[s2][0] = 0;
    		up( s2 );
    	}else if( s2 == -1 ){
    		Splay( s1 , 0 );
    		fa[ch[s1][1]] = 0;
    		ch[s1][1] = 0 ;
    		up( s1 );
    	}else{
    		Splay( s1 , 0 );
    		Splay( s2 , s1 );
    		fa[ch[s2][0]] = 0;
    		ch[s2][0] = 0;
    		up( s2 );
    		up( s1 );
    	}
    }

}splay;