struct Suffix_Auto{
	const static int maxn = ( 1e5 + 50 ) * 2;
	const static int lettersz = 26;
	int tot , last , link[maxn] , nxt[maxn][lettersz] , len[maxn];
	int gethash( char c ){ return c -'a' ;}
	void init( int idx ){ link[idx] = len[idx] = 0 , memset( nxt[idx] , 0 , sizeof( nxt[idx] ) ); }
	void init(){ memset(nxt[0],0,sizeof(nxt[0])) ; last = tot = len[0] = 0 , link[0] = -1 ; }
	void extend( char c ){
		int cur = ++ tot , p , q , id = gethash( c ) ; 
		init( cur ) ;
		len[cur] = len[last] + 1;
		for( p = last ; ~p && !nxt[p][id] ; p = link[p] ) nxt[p][id] = cur;
		if( ~p ){
			q = nxt[p][id];
			if( len[p] + 1 == len[q] ) link[cur] = q;
			else{
				// Pay attention to init for clone , such as cnt array
				int clone = ++ tot ; 
				len[clone] = len[p] + 1 , memcpy( nxt[clone] , nxt[q] , sizeof(int)*lettersz ) , link[clone] = link[q];
				for( ; ~p && nxt[p][id] == q ; p = link[p] ) nxt[p][id] = clone;
				link[q] = link[cur] = clone;
			}
		}
		last = cur;
	}
}Sam;