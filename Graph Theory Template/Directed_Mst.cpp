#include <iostream>

/*
最小树形图图模版-朱刘算法
模版说明：点标号必须0-(N-1)
		必须去除到自身的点（到自身的边的边权赋无限大）
		（link已自动判断，到自身的点不会建边)
*/

struct Directed_Mst{
	typedef int Directed_MST_Type;
	const static Directed_MST_Type inf=(1)<<30;
	const static int M = 105;
	struct Node{
		int u , v;
		Directed_MST_Type cost;
	}E[M*M+5];

	int pre[M],ID[M],vis[M],n,m;
	Directed_MST_Type In[M];

	void init(int n){
		this-> n = n;
		m = 0;
	}

	void link(int u,int v,Directed_MST_Type c){
		if(u != v){
			E[m].u = u , E[m].v = v , E[m++].cost = c;
		}
	}

	// -1 说明不存在
	Directed_MST_Type Directed_MST(int root) {
		int NV = n , NE = m;
		Directed_MST_Type ret = 0;
		while(true) {
			//1.找最小入边
			for(int i=0;i<NV;i++) In[i] = inf;
			for(int i=0;i<NE;i++){
				int u = E[i].u;
				int v = E[i].v;
				if(E[i].cost < In[v] && u != v) {
					pre[v] = u;
					In[v] = E[i].cost;
				}
			}
			for(int i=0;i<NV;i++) {
				if(i == root) continue;
				if(In[i] == inf)	return -1;//除了跟以外有点没有入边,则根无法到达它
			}
			//2.找环
			int cntnode = 0;
			memset(ID,-1,sizeof(ID));
			memset(vis,-1,sizeof(vis));
			In[root] = 0;
			for(int i=0;i<NV;i++) {//标记每个环
				ret += In[i];
				int v = i;
				while(vis[v] != i && ID[v] == -1 && v != root) {
					vis[v] = i;
					v = pre[v];
				}
				if(v != root && ID[v] == -1) {
					for(int u = pre[v] ; u != v ; u = pre[u]) {
						ID[u] = cntnode;
					}
					ID[v] = cntnode ++;
				}
			}
			if(cntnode == 0)	break;//无环
			for(int i=0;i<NV;i++) if(ID[i] == -1) {
				ID[i] = cntnode ++;
			}
			//3.缩点,重新标记
			for(int i=0;i<NE;i++) {
				int v = E[i].v;
				E[i].u = ID[E[i].u];
				E[i].v = ID[E[i].v];
				if(E[i].u != E[i].v) {
					E[i].cost -= In[v];
				}
			}
			NV = cntnode;
			root = ID[root];
		}
		return ret;
	}
}solver;

int main(){

}