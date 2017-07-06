void tarjan_scc(int u)
{
	dfn[u] = low[u] = ++T;
	s.push(u);
	for(int i = head[u] ; ~i ; i = e[i].nxt)
	{
		int v = e[i].v;
		if(!dfn[v])
		{
			tarjan_scc(v);
			low[u] = min(low[u] , low[v]);
		}
		else if(scc_idx[v] == -1) low[u] = min(low[u] , dfn[v]);
	}
	if(low[u] == dfn[u])
	{
		while(1)
		{
			int x = s.top();s.pop();
			scc_idx[x] = scc_cnt;
			if(x == u) break;
		}
		scc_cnt++;
	}
}
