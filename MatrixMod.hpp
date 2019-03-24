struct MatrixMod {
    int n, mod;
    vector<vector<int>> val;

    MatrixMod(int _n, int _mod) {
        n = _n; mod = _mod;
        val.assign(n, vector<int>(n, 0));
    }

    MatrixMod() {
        n = 0;
        mod = 1e9 + 7;
    }
    
    void set(int y, int x, int v) { val[y][x] = v; }

    int fastPow(int v, int k) {
        int ret = 1;
        while (k) {
            if (k & 1) ret = (1LL * ret * v) % mod;
            v = (1LL * v * v) % mod;
            k >>= 1;
        }
        return ret;
    }

    int getDeterminant() {
        int ret = 1;

        for (int i = 0; i < n; ++i) {
            int piv = i;
            while (piv < n && !val[piv][i]) piv++;
            if (piv == n) return 0;

            if (piv != i) {
                swap(val[i], val[piv]);
                if (ret) ret = (mod - ret);
            }

            for (int j = i + 1; j < n; j++)
                if (val[j][i]) {
                    int mtp = 1LL * val[j][i] * fastPow(val[i][i], mod - 2) % mod;
                    for (int k = i; k < n; k++)
                        val[j][k] = (val[j][k] - 1LL * val[i][k] * mtp % mod + mod) % mod;
                }

            ret = (1LL * ret * val[i][i]) % mod;
        }

        return ret;
    }
};