struct Palindromic_Auto{
	const static int maxn = 2e5 + 15;
	const static int lettersz = 26;
	int link[maxn] , len[maxn] , last , tot , nxt[maxn][lettersz] , s[maxn] , n ;
	void init( int id , int l ){ memset( nxt[id] , 0 , sizeof( nxt[id] ) ); len[id] = l; }
	void init(){ n = last = 0 , s[0] = -1 , link[0] = tot = 1; init( 0 , 0  ) , init( 1 , -1 ); }
	int gethash( char c ){ return c -'a' ;}
	int extend( char c ){
		s[ ++ n ] = gethash( c );
		int cur = last ;
		while( s[n - len[cur] - 1] != s[n] ) cur = link[cur];
		if( !nxt[cur][s[n]] ){
			int id = ++ tot , t = link[cur] ; init( id , len[cur] + 2 );
			while( s[n - len[t] - 1] != s[n] ) t = link[t];
			link[id] = nxt[t][s[n]] , nxt[cur][s[n]] = id;
		}
		last = nxt[cur][s[n]];
		return len[last];
	}
}pa_auto;