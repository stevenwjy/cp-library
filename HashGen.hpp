const int MAXN_HG = 1e6 + 5;
const int MAXH_HG = 10;

struct HashGen {
	int BASE[MAXH_HG] = {29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
	int N_BASE = 2;

	int n, val[MAXN_HG];

	int frontHash[MAXH_HG][MAXN_HG], backHash[MAXH_HG][MAXN_HG];
	int mtpHash[MAXH_HG][MAXN_HG];

	void init(int _N_BASE, int _n) {
		N_BASE = _N_BASE;
		n = _n;
	}

	void setVal(vector<int> v) {
		n = SZ(v);
		for (int i = 0; i < SZ(v); ++i)
			val[i + 1] = v[i];
	}

	void setVal(int x, int v) {
		assert(x >= 0);
		val[x] = v;
	}

	void createHash() {
		for (int k = 0; k < N_BASE; ++k) {
			frontHash[k][0] = 0; mtpHash[k][0] = 1;
			for (int i = 1; i <= n; i++) {
				frontHash[k][i] = ((1LL * frontHash[k][i - 1] * BASE[k]) + val[i]) % MOD;
				mtpHash[k][i]   = (1LL * mtpHash[k][i - 1] * BASE[k]) % MOD;
			}
			backHash[k][n + 1] = 0;
			for (int i = n; i >= 1; i--) 
				backHash[k][i]  = ((1LL * backHash[k][i + 1]  * BASE[k]) + val[i]) % MOD;
		}
	}

	vector<int> getHash(int kd, int l, int r) {
		assert(l <= r); vector<int> ret;
		for (int k = 0; k < N_BASE; ++k) {
			int hv;
			if (kd == 0) { // from front
				hv = frontHash[k][r] - (1LL * frontHash[k][l - 1] * mtpHash[k][r - l + 1]) % MOD;
			} else { // from back
				hv = backHash[k][l]  - (1LL * backHash[k][r + 1]  * mtpHash[k][r - l + 1]) % MOD;
			}
			if (hv < 0) hv += MOD;
			ret.psb(hv);
		}
		return ret;
	}
};