struct CRT {
    int n;
    vector<int> num, rem, inv;

    PrimeFactorization pf;

    LL mod, pn;
    vector<LL> pp;

    void precomp() {
        pf.precomp();
    }
    
    void init(vector<int> _num) { 
        // num pairwise co-prime, if not, break into their prime factors first
        num = _num;
        n = SZ(num);

        computeNum();
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

    void computeNum() {
        mod = 1LL;
        for (int i = 0; i < n; ++i) 
            mod *= (LL) num[i];

        pp.resize(n);
        for (int i = 0; i < n; ++i)
            pp[i] = (mod / (LL) num[i]);

        inv.resize(n);
        for (int i = 0; i < n; ++i)
            inv[i] = fastPow(pp[i] % num[i], pf.phi(num[i]) - 1, num[i]);
    }

    LL compute(vector<int> rem) {
        LL ret = 0LL, hs;

        for (int i = 0; i < n; ++i) {
            hs = ((__int128) rem[i] * (__int128) pp[i]) % mod;
            hs = ((__int128) hs * (__int128) inv[i]) % mod;

            ret = (ret + hs) % mod;
        }
        
        return ret;
    }
}