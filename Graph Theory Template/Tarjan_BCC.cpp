int tarjan_dfs(int u,int fa)
{
	dfn[u] = low[u] = ++T;
	for(int i = head[u] ; ~i ; i = e[i].nxt)
	{
		int v = e[i].v;
		if(v == fa) continue;
		if(!dfn[v])
		{
			s.push(make_pair(u,v));
			int lowv = tarjan_dfs(v,u);
			low[u] = min(low[u],lowv);
			if(lowv >= dfn[u])
			{
				bcc_cnt++;bcc[bcc_cnt].clear();
				while(1)
				{
					dl ss = s.top();s.pop();
					int x = ss.first , y = ss.second;
					if(belong[x] != bcc_cnt) 
					{
						bcc[bcc_cnt].push_back(x);
						belong[x] = bcc_cnt;
					}
					if(belong[y] != bcc_cnt) 
					{
						bcc[bcc_cnt].push_back(y);
						belong[y] = bcc_cnt;
					}
					if(x==u&&y==v) break;
				}
			}
		}
		else if(dfn[v] < dfn[u])
		{
			s.push(make_pair(u,v));
			low[u] = min(low[u] , dfn[v]);
		}
	}
	return low[u];
}