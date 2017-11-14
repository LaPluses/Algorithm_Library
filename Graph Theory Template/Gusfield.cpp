namespace Gusfield{
	const int MAXN=2050,MAXM=400000,inf=1e9;
    struct Edge{
        int v,c,f,nx;
        Edge() {}
        Edge(int v,int c,int f,int nx):v(v),c(c),f(f),nx(nx) {}
    } E[MAXM];
    int G[MAXN],cur[MAXN],pre[MAXN],dis[MAXN],gap[MAXN],N,sz,fa[MAXN],w[MAXN],vis[MAXN];
    void init(int _n){
        N=_n,sz=0; memset(G,-1,sizeof(G[0])*N);
    }
    void link(int u,int v,int c){
        E[sz]=Edge(v,c,0,G[u]); G[u]=sz++;
        E[sz]=Edge(u,0,0,G[v]); G[v]=sz++;
    }
    int ISAP(int S,int T){
        int maxflow=0,aug=inf,flag=false,u,v;
        for (int i=0;i<N;++i)cur[i]=G[i],gap[i]=dis[i]=0;
        for (gap[S]=N,u=pre[S]=S;dis[S]<N;flag=false)
        {
            for (int &it=cur[u];~it;it=E[it].nx)
            {
                if (E[it].c>E[it].f&&dis[u]==dis[v=E[it].v]+1)
                {
                    if (aug>E[it].c-E[it].f) aug=E[it].c-E[it].f;
                    pre[v]=u,u=v; flag=true;
                    if (u==T)
                    {
                        for (maxflow+=aug;u!=S;)
                        {
                            E[cur[u=pre[u]]].f+=aug;
                            E[cur[u]^1].f-=aug;
                        }
                        aug=inf;
                    }
                    break;
                }
            }
            if (flag) continue;
            int mx=N;
            for (int it=G[u];~it;it=E[it].nx)
            {
                if (E[it].c>E[it].f&&dis[E[it].v]<mx)
                {
                    mx=dis[E[it].v]; cur[u]=it;
                }
            }
            if ((--gap[dis[u]])==0) break;
            ++gap[dis[u]=mx+1]; u=pre[u];
        }
        return maxflow;
    }

    void Dfs( int u ){
    	for(int i = G[u] ; ~i ; i = E[i].nx){
    		int v = E[i].v;
    		if( !vis[v] && E[i].f < E[i].c ){
    			vis[v] = 1;
    			Dfs( v );
    		}
    	}
    }

    vector < tuple < int , int , int > > Build( int n , vector < tuple < int , int , int > > Edge ){
    	fa[0] = -1;
    	for(int i = 1 ; i < n ; ++ i) fa[i] = 0;
		init( n );
		for(auto && it : Edge) link( get < 0 >( it ) , get < 1 >( it ) , get < 2 >( it ) );
        for(int u = 1 ; u < n ; ++ u){
            int v = fa[u];
            for(int i = 0 ; i < sz ; ++ i) E[i].f = 0;
    		w[u] = ISAP( u , v );
    		memset( vis , 0 , n << 2 );
    		Dfs( u );
    		for(int x = u + 1 ; x < n ; ++ x)
    			if( fa[x] == v && vis[x] )
    				fa[x] = u;
 	  	}
 	  	vector < tuple < int , int , int > > res;
 	  	for(int u = 1 ; u < n ; ++ u){
 	  		int v = fa[u] , cost = w[u];
 	  		res.emplace_back( make_tuple( u , v , cost ) );
 	  	}
 	  	return res;
    }
};