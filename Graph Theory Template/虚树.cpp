

bool check(int x,int y) {return in[x] <= in[y] && out[x] >= out[y];}  
bool cmp( int x , int y ){ return in[x] < in[y] ;} 

void DFS( int u , int fa = 0 ){
	in[u] = ++ dfs_clock;
	for(auto v : G[u]){
		if( v == fa )
			continue;
		deep[v] = deep[u] + 1;
		f[v][0] = u;
		DFS( v , u );
	}
	out[u] = ++ dfs_clock;
}
void Build(){
	sort( seq + 1 , seq + len + 1 , cmp );
	int m = len;
	for(int i = 1 ; i < m ; ++ i)
        seq[++ len] = getlca( seq[i] , seq[i + 1] );

    len = unique(seq + 1,seq + len + 1) - seq - 1; 
    for(int i = 1 ; i <= len ; ++ i) E[seq[i]].clear();
    sort( seq + 1 , seq + len + 1 , cmp );
    int top = 0 , root ;
    for(int i = 1;i <= len;i ++) {  
        while(top > 0 && !check(STK[top],seq[i])) 
            top --;  
        if(STK[top] == 0) root = seq[i];
        else {  
            int s = STK[top],t = seq[i];  
            if( s != t )
              Link(s,t,deep[t] - deep[s]);  
        }  
        STK[ ++ top] = seq[i];  
    }
   cal( root , 0 );
    for(int i = 1 ; i <= len ; ++ i)
    	sz[seq[i]] = 0;
}