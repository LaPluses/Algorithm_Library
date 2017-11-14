namespace PlanarGraph{
	const int N = 6666;
	const int M = 6666;
	pair < int , int > p[N];
	long long operator ^( const pair < int , int > & a , const pair < int , int > & b){
		return 1ll * a.first * b.second - 1ll * a.second * b.first;
	}
	struct edge{
		int u,v,cost;
		double r;
		edge(int u = 0,int v = 0,int cost = 0):u(u),v(v),cost(cost){r=atan2(p[v].second-p[u].second,p[v].first-p[u].first);};
	}e[M];
	int ecnt,belong[M],cnt,idsz;//0~cnt面数,0~idsz-1端点个数
	struct cmp{bool operator()(int a,int b){return e[a].r<e[b].r;}};
	set<int,cmp>g[N];
	vector<int>q;
	map<pair<int,int>,int>id;
	bool del[M];
	void init(){
		for(int x=0;x<idsz;x++)g[x].clear();
		for(int x=0;x<ecnt;x++)g[e[x].u].insert(x);
		memset(del,0,sizeof(del));
		memset(belong,0,sizeof(belong));
		cnt=1;
	}

	void work(){
		init();
		for(int x=0;x<ecnt;x++)
		if(!del[x]){
			q.clear();
			int t=x;
			do{
				q.emplace_back(t);
				auto k=g[e[t].v].find(t^1);
				++k;
				if(k==g[e[t].v].end())k=g[e[t].v].begin();
				t=*k;
			}while(t!=x);
			long long s=0;
			for(auto&& y:q)
				s+=p[e[y].u]^p[e[y].v],del[y]=1;
			if(s>=0)continue;		//表示最外环和无面积环,belong=0
			for(auto&& y:q)
				belong[y]=cnt;
			cnt++;
		}
	}

	int Ins( pair < int , int > t ){
		if( !id.count( t ) ) p[idsz] = t , id[t] = idsz++;
		return id[t];
	}

	vector < tuple < int , int , int > > Build( vector < tuple < pair < int , int > , pair < int , int > , int > > in){
		id.clear(); idsz = ecnt = 0;
		for(auto && x : in){
			int u = Ins( get < 0 > ( x ) );
			int v = Ins( get < 1 > ( x ) );
			int w = get < 2 > ( x );
			e[ecnt++] = edge( u , v , w );
			e[ecnt++] = edge( v , u , w );
		}
		work();
		vector < tuple < int , int , int > > ans;
		// 单向边
		for(int i = 0 ; i < ecnt ; i += 2) ans.emplace_back( make_tuple( belong[i] , belong[i ^ 1] , e[i].cost ) );
		return ans;
	}
};