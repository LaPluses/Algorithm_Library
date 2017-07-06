#include <bits/stdc++.h>


using namespace std;
const int maxn = 1e5 + 500;
struct Edge{
	int u , v , w;
	friend bool operator < (const Edge & a,const Edge & b){
		return a.w < b.w;
	}
};
Edge e[maxn << 1];
int n , m , fa[maxn] , ans1 , ans2;

int find_set(int u){
	return u != fa[u] ? fa[u] = find_set( fa[u] ) : u;
}

void union_set(int u,int v){
	int p1 = find_set( u ) , p2 = find_set( v );
	if(p1 != p2) fa[p1] = p2;
}

int main(int argc,char *argv[]){
	scanf("%d%d",&n,&m);
	for(int i = 1 ; i <= n ; ++ i) fa[i] = i;
	for(int i = 0 ; i < m ; ++ i) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort( e , e + m );
	for(int i = 0 ; i < m ; ++ i){
		int u = e[i].u , v = e[i].v , w = e[i].w;
		if(find_set(u) == find_set(v)) continue;
		int j;
		for(j = i ; j < m ; ++ j) if(e[j].w != w) break; else if(find_set(e[j].u) != find_set(e[j].v)) ans2++;
		for(int k = i ; k < j ; ++ k){
			if(find_set(e[k].u) != find_set(e[k].v)) ans1+=w;
			union_set(e[k].u,e[k].v);
		}
		i = j - 1;
	}
	printf("%d %d\n",ans1,ans2);
	// ans1 MST的权值 ， ans2 可能在MST上的数量
	return 0;
}