struct Mcmf{
	const static int MAXN = 10000;
	const static int MAXM = 100000;
	int INF = 0x3f3f3f3f;

    struct Edge
    {
        int to, next, cap, flow, cost;
        int x, y;
    } edge[MAXM],HH[MAXN],MM[MAXN];
    int head[MAXN],tol;
    int pre[MAXN],dis[MAXN];
    bool vis[MAXN];
    int N, M;
    void init()
    {
        N = MAXN;
        tol = 0;
        memset(head, -1, sizeof(head));
    }
    //¼Ó±ß²Ù×÷
    //×ó¶Ëµã£¬ÓÒ¶Ëµã£¬ÈÝÁ¿£¬»¨·Ñ
    void addedge(int u, int v, int cap, int cost)
    {
        edge[tol]. to = v;
        edge[tol]. cap = cap;
        edge[tol]. cost = cost;
        edge[tol]. flow = 0;
        edge[tol]. next = head[u];
        head[u] = tol++;
        edge[tol]. to = u;
        edge[tol]. cap = 0;
        edge[tol]. cost = -cost;
        edge[tol]. flow = 0;
        edge[tol]. next = head[v];
        head[v] = tol++;
    }
    //Èç¹ûÖ»ÏëÓÃÕâ¸öËã·¨£¬SPFA²¿·Ö¿ÉÒÔ²»¶¯
    bool spfa(int s, int t)
    {
        queue<int>q;
        for(int i = 0; i < N; i++)
        {
            dis[i] = INF;
            vis[i] = false;
            pre[i] = -1;
        }
        dis[s] = 0;
        vis[s] = true;
        q.push(s);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for(int i = head[u]; i != -1; i = edge[i]. next)
            {
                int v = edge[i]. to;
                if(edge[i]. cap > edge[i]. flow &&
                        dis[v] > dis[u] + edge[i]. cost )
                {
                    dis[v] = dis[u] + edge[i]. cost;
                    pre[v] = i;
                    if(!vis[v])
                    {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        if(pre[t] == -1) return false;
        else return true;
    }
    //·µ»ØµÄÊÇ×î´óÁ÷£¬ cost´æµÄÊÇ×îÐ¡·ÑÓÃ
    int minCostMaxflow(int s, int t, int &cost)
    {
        int flow = 0;
        cost = 0;
        while(spfa(s,t))
        {
            int Min = INF;
            for(int i = pre[t]; i != -1; i = pre[edge[i^1]. to])
            {
                if(Min > edge[i]. cap - edge[i]. flow)
                    Min = edge[i]. cap - edge[i]. flow;
            }
            for(int i = pre[t]; i != -1; i = pre[edge[i^1]. to])
            {
                edge[i]. flow += Min;
                edge[i^1]. flow -= Min;
                cost += edge[i]. cost * Min;
            }
            flow += Min;
        }
        /*debug²¿·Ö
        //¿ÉÊä³öÃ¿Ìõ±ß¾ßÌåÁ÷Á¿
        for(int i=1;i<=n;i++)
        {
            for(int j = head[i]; j != -1; j = edge[j]. next)
            {
                if(edge[j].to==0)
                    continue;
                MMm[i][edge[j].to-n] += edge[j].flow;
            }
        }
        */
        return flow;
    }
};
