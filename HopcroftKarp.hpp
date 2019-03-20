struct HopcroftKarp {
    int n, m;
    vector<int> aft, bef, dst;
    vector<vector<int>> adj;

    void init(int _n, int _m) {
        n = _n;
        m = _m;
        adj.assign(n + 1, vector<int>());
    }

    void init(int _n) {
        init(_n, _n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> que;

        dst[0] = -1;
        for (int i = 1; i <= n; ++i)
            if (aft[i] == 0) {
                dst[i] = 0;
                que.push(i);
            } else dst[i] = -1;

        while (!que.empty()) {
            int now = que.front(); que.pop();
            for (auto nex : adj[now]) 
                if (dst[bef[nex]] == -1) {
                    dst[bef[nex]] = dst[now] + 1;
                    que.push(bef[nex]);

                    if (bef[nex] == 0) return true;
                }
        }

        return false;
    }

    int dfs(int now) {
        if (now == 0) return 1;

        for (auto nex : adj[now])
            if (dst[bef[nex]] == dst[now] + 1 && dfs(bef[nex])) {
                bef[nex] = now;
                aft[now] = nex;
                return 1;
            }

        dst[now] = -1;
        return 0;
    }

    int getMaxMatching() {
        aft.assign(n + 1, 0);
        bef.assign(m + 1, 0);
        dst.assign(n + 1, -1);

        int ret = 0;
        while (bfs()) 
            for (int i = 1; i <= n; ++i)
                if (aft[i] == 0) ret += dfs(i);
        
        return ret;
    }
};