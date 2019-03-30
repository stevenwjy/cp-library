struct Combin {
    int mod, lim;
    vector<int> fact, inv;
    
    void init(int _mod, int _lim) {
        mod = _mod;
        lim = _lim;

        fact.resize(lim);
        fact[0] = fact[1] = 1 % mod;
        for (int i = 2; i < lim; ++i)
            fact[i] = (1LL * fact[i - 1] * i) % mod;

        inv.assign(lim, -1);
    }

    int fastPow(int v, int k, int m) {
        int mul = v, ret = 1 % m;
        while (k) {
            if (k & 1) ret = (1LL * ret * mul) % m;
            k >>= 1;
            mul = (1LL * mul * mul) % m;
        }
        return ret;
    }

    int compute(int v, int k) {
        if (k > v || k < 0 || v <= 0) return 0;
        if (inv[k] == -1) inv[k] = fastPow(fact[k], mod - 2, mod);
        if (inv[v - k] == -1) inv[v - k] = fastPow(fact[v - k], mod - 2, mod);

        int ret = (1LL * fact[v] * inv[v - k]) % mod;
        ret = (1LL * ret * inv[k]) % mod;

        return ret;
    }

    // mod must be a prime number
    int combinLucas(int a, int b) {
        int res = 1;
        while (a > 0 && b > 0){
            res = (1LL * res * compute(a % mod, b % mod)) % mod;
            a /= mod; b /= mod;
        }
        return res;
    }
};
