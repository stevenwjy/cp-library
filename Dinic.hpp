const int MAXN_D = 2005;
const int MAXE_D = 300005;

struct Dinic {
	int n, s, t;
	int cntEdge, aft[MAXE_D], fl[MAXE_D];
	vector<int> adj[MAXN_D];
	void init(int _n, int _s, int _t) {
		n = _n; s = _s; t = _t;
		cntEdge = 0;
		for (int i = 1; i <= n; i++) 
			adj[i].clear();
	}
	void addEdge(int u, int v, int f) {
		aft[cntEdge] = v; fl[cntEdge] = f; adj[u].psb(cntEdge); cntEdge++;
		aft[cntEdge] = u; fl[cntEdge] = 0; adj[v].psb(cntEdge); cntEdge++;
	}
	int dst[MAXN_D], que[MAXN_D];
	bool bfs() {
		for (int i = 1; i <= n; i++)
			dst[i] = -1;
		dst[s] = 0; que[0] = s;
		for (int ql = 0, qr = 1; ql < qr; ql++) {
			int now = que[ql];
			for (auto edge : adj[now]) {
				int &nex = aft[edge];
				int &flow = fl[edge];
				if (dst[nex] != -1 || flow == 0) continue;
				dst[nex] = dst[now] + 1;
				que[qr++] = nex;
			}
		}
		return dst[t] != -1;
	}
	int itr[MAXN_D];
	int dfs(int now, int f) {
		if (now == t) return f;
		while (itr[now] < SZ(adj[now])) {
			int edge = adj[now][itr[now]];
			int &nex = aft[edge];
			int &flow = fl[edge];
			if (dst[nex] != dst[now] + 1 || flow == 0) {
				itr[now]++;
				continue;
			}
			int dpt = dfs(nex, min(f, flow));
			if (dpt == 0) {
				itr[now]++;
				continue;
			}
			fl[edge] -= dpt;
			fl[edge ^ 1] += dpt;
			return dpt;
		}
		return 0;
	}
	int computeMaxFlow() {
		int ret = 0;
		while (bfs()) {
			for (int i = 1; i <= n; i++)
				itr[i] = 0;
			while (1) {
				int dpt = dfs(s, INF);
				if (dpt == 0) break;
				ret += dpt;
			}
		}
		return ret;
	}
};
