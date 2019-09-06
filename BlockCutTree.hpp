int n, m, low[MAXN], num[MAXN], id[MAXN], cnt = 0, no = 0;
LL sum[MAXN], tot[MAXN];
vector<int> adj[MAXN], rev[MAXN];
stack<int> stk;

void add_edge (int a, int b) {
	rev[a].psb(b);
	rev[b].psb(a);
}

void dfs (int now, int par) {
	num[now] = low[now] = ++cnt;
	stk.push(now);

	for (auto nex : adj[now]) {
		if (nex == par) continue;
		if (num[nex] == -1) {
			dfs(nex,now);
			low[now] = min(low[now], low[nex]);

			if (low[nex] >= num[now] && id[now] == -1) {
				++no;
				id[now] = no;
				sum[no] = 1;
				tot[no] = 1; 
			}

			if (low[nex] == num[now]) {
				++no;
				tot[no] = 0LL;
				sum[no] = 0LL;

				while (1) {
					int v = stk.top(); stk.pop();
					tot[no]++;
					
					if (id[v] == -1) {
						sum[no]++;
						id[v] = no;
					} else add_edge(no, id[v]);

					if (v == nex) break;
				}

				tot[no]++;
				add_edge(no, id[now]);

			} else if (low[nex] > num[now]) {
				add_edge (id[now], id[nex]);
			}

		} else low[now] = min(low[now], num[nex]);
	}
	
	if (low[now] == num[now] && id[now] == -1) {
		++no;
		id[now] = no;
		sum[no] = 1;
		tot[no] = 1;
	}

	if (low[now] == num[now]) stk.pop();
}
