struct ZKW_MinCostMaxFlow{  

    const static int maxn = 1e5 + 50;
    const static int maxE = 1e5 + 50;
    const static int INF = 0x3f3f3f3f;

    struct Edge{  
        int to,next,cap,flow,cost;  
        Edge(int _to=0,int _next=0,int _cap=0,int _flow=0,int _cost=0):  
            to(_to),next(_next),cap(_cap),flow(_flow),cost(_cost){}  
    }edge[maxE * 2];  

    int head[maxn],tot;  
    int cur[maxn];  
    int dis[maxn];  
    bool vis[maxn];  
    int ss,tt,N;  
    int min_cost,max_flow;  
    void init(int N){  
        tot=0;
        for( int i = 0 ; i < N ; ++ i ) head[i] = -1;
    }  
    void addedge(int u,int v,int cap,int cost){  
        edge[tot]=Edge(v,head[u],cap,0,cost);  
        head[u]=tot++;  
        edge[tot]=Edge(u,head[v],0,0,-cost);  
        head[v]=tot++;  
    }  
    int aug(int u,int flow){  
        if(u==tt) return flow;  
        vis[u]=true;  
        for(int i=cur[u];i!=-1;i=edge[i].next){  
            int v=edge[i].to;  
            if( edge[i].cap>edge[i].flow && !vis[v] && dis[u]==dis[v]+edge[i].cost ){  
                int tmp=aug(v,min(flow,edge[i].cap-edge[i].flow));  
                edge[i].flow+=tmp;  
                edge[i^1].flow-=tmp;  
                cur[u]=i;  
                if(tmp) return tmp;  
            }  
        }  
        return 0;  
    }  
    bool modify_label(){  
        int d=INF;  
        for(int u=0;u<N;u++){  
            if(vis[u])  
            for(int i=head[u];i!=-1;i=edge[i].next){  
                int v=edge[i].to;  
                if(edge[i].cap>edge[i].flow && !vis[v])  
                    d=min(d,dis[v]+edge[i].cost-dis[u]);  
            }  
        }  
        if(d==INF) return false;  
            for(int i=0;i<N;i++)  
            if(vis[i]){  
                vis[i]=false;  
                dis[i]+=d;  
            }  
        return true;  
    }  
    int mincostmaxflow(int start,int ed,int n ){  
        ss=start,tt=ed,N=n;  
        min_cost=max_flow=0;  
        for(int i=0;i<n;i++) dis[i]=0;  
        while(1){  
            for(int i=0;i<n;i++) cur[i]=head[i];  
            while(1){  
                for(int i=0;i<n;i++) vis[i]=false;  
                int tmp=aug(ss,INF);  
                if(tmp==0) break;
                max_flow+=tmp;  
                min_cost+=tmp*dis[ss];  
            }  
            if(!modify_label()) break;  
        }  
        return min_cost; // reutnr max_flow
    }
}solver;