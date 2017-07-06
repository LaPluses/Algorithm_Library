
struct Edge{
	int u ,v ,nxt ; long long w ;
};

Edge e[maxn * 2];
int n ,tot,head[maxn],fa[maxn],son[maxn],top[maxn],idx[maxn],dfs_clock,deep[maxn];
long long co[maxn];
void addedge(int u ,int v,long long w){
	e[tot].v=v,e[tot].nxt=head[u],e[tot].w=w,head[u]=tot++;
}

int dfs1(int u){
	int sz = 0 , res = 1;
	for(int i = head[u] ; ~i ; i = e[i].nxt){
		int v = e[i].v;
		if(v==fa[u]) continue;
		fa[v] = u,deep[v]=deep[u]+1;
		int t = dfs1(v);
		co[v] = e[i].w;
		if(t > sz){
			sz = t;
			son[u] = v;
		}
		res += t;
	}
	return res;
}

void dfs2(int u ,int tp){
	top[u] = tp , idx[u] = ++dfs_clock;
	if(u!=1) Sgtree.updata(idx[u],co[u],1);
	if(son[u]) dfs2(son[u],tp);
	for(int i = head[u] ; ~i ; i = e[i].nxt){
		int v = e[i].v;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}

void solve(int u ,int v , long long x){
	int f1 = top[u] , f2 = top[v];
	while(f1 != f2){
		if(deep[f1] < deep[f2]) swap(f1,f2),swap(u,v);
		x /= Sgtree.query(idx[f1],idx[u],1);
		u = fa[top[u]],f1=top[u];
	}
	if(deep[u] > deep[v]) swap(u,v);
	if(u!=v) x/= Sgtree.query(idx[u]+1,idx[v],1);
	printf("%I64d\n",x);
}