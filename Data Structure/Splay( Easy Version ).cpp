struct SplayTree{

	const static int maxn = 1e5 + 15;

	int ch[maxn][2] , key[maxn] , s[maxn] , tot , root , fa[maxn];

	void init( int x , int val = 0 , int par = 0 ){
		ch[x][0]=ch[x][1]=0 , fa[x]= par , key[x] = val , s[x] = 1;
	}

	void init(){
		init( 0 , 0 , 0 ); s[0] = 0;
		tot = root = 0 ;
	}

	inline void up(int x){
		s[x] = s[ch[x][0]] + s[ch[x][1]] + 1;
    } 

    void rotate( int x, int d ){
        int y = fa[x];
        ch[y][d ^ 1] = ch[x][d];
        if ( ch[x][d]) fa[ch[x][d]] = y;  
        fa[x] = fa[y];
        if (fa[y]){
            if (y == ch[fa[y]][d])  ch[fa[y]][d] = x;
            else  ch[fa[y]][d ^ 1] = x;
        }
        ch[x][d] = y , fa[y] = x;
        up( y ) , up( x );
    }

    // Splay x to target's son
    void Splay( int x , int target ){
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

	void Preorder( int t ){
		if( !t ) return;
		Preorder( ch[t][0] );
		printf("%d " , key[t] );
		Preorder( ch[t][1] );
	}

}splay;