
bool find_path(int u){
	vis[u] = 1;
	if(u==end){ //到达终点
		path.push_back(u);
		return true;
	}
	else{
		for(int i = head[u] ; ~i ; i = e[i].nxt){
			int v = e[i].v;
			if(!vis[v]){
				if(find_path(v))
				{
					path.push_back(u);
					return true;
				}
			}
		}
	}
	return false;
}