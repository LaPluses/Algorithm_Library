
vector<int> G[maxn]; // 邻接表
int dfn[maxn];    // dfs时间戳
int low[maxn];    // u以及u的后代所能追溯到的最早的祖先
int sccno[maxn];  // sccno[u] 为u所属SCC的编号，从1开始
int dfs_clock;    // dfs时间戳变量
int scc_cnt;      // SCC数量
stack<int> S;     // DFS储存访问的结点

void dfs(int u) {
    dfn[u] = low[u] = ++dfs_clock;
    S.puhs(u);
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!dfn[v]) { // 这条边是树边
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!sccno[v]) { // 这条边是反向边
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {   // 判断是否是SCC中的最早访问结点
        scc_cnt++;
        for (;;) {
            int x = S.top(); S.pop();
            sccno[x] = scc_cnt;
            if (x == u) break;
        }
    }
}


void find_scc(int n) {
    dfs_clock = scc_cnt = 0;
    memset(sccno, 0, sizeof(sccno));
    memset(dfn, 0, sizeof(dfn));
    for (int i = 0; i < n; i++) {
        if (!dfn[i]) dfs(i);
    }
}
