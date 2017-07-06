struct SuffixArray{
	const static int maxn = 1e5 + 50;
	int sa[maxn],c[maxn],sq[maxn],sw[maxn],rank[maxn],height[maxn];
	void Build(int *s,int n,int m){
		++ n;
		int * x = sq , *y = sw , p = 1 ;
		for(int i = 0 ; i < m ; ++ i) c[i] = 0;
		for(int i = 0 ; i < n ; ++ i) c[x[i]=s[i]]++;
		for(int i = 1 ; i < m ; ++ i) c[i] += c[i - 1];
		for(int i = n - 1 ; i >= 0 ; -- i) sa[--c[x[i]]] = i;
		for(int k = 1 ; p < n ; k <<= 1){
			p = 0;
			for(int i = n - k ; i < n ; ++ i) y[p ++] = i;
			for(int i = 0 ; i < n ; ++ i) if( sa[i] >= k ) y[p ++] = sa[i] - k;
			for(int i = 0 ; i < m ; ++ i) c[i] = 0;
			for(int i = 0 ; i < n ; ++ i) c[x[y[i]]]++;
			for(int i = 1 ; i < m ; ++ i) c[i] += c[i-1];
			for(int i = n - 1 ; i >= 0 ; -- i) sa[--c[x[y[i]]]]=y[i];
			swap( x , y ) ; p = 1 , x[sa[0]] = 0;
	        for(int i = 1 ; i < n ; ++ i) x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
			m = p;
		}
		-- n;
		for(int i = 0 ; i < n ; ++ i) sa[i] = sa[i + 1] , rank[sa[i]] = i;
		for(int i = 0 , k = 0 ; i < n ; ++ i ){
			if( !rank[i] ) continue;
			int j = sa[rank[i] - 1];
			if( k ) -- k;
			while( s[i + k] == s[j + k] ) ++ k;
			height[rank[i]] = k;
		}
	}
}Sa;