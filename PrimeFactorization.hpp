const int MAXP = 32000;
struct PrimeFactorization { // for N up to 1e9
    bool notPrime[MAXP];
    vector<int> primes;

    void precomp() {
        notPrime[0] = notPrime[1] = 1;
        for (int i = 2; i < MAXP; ++i) {
            if (notPrime[i]) continue;
            primes.psb(i);
            for (int j = i * i; j < MAXP; j += i)
                notPrime[j] = 1;
        }
    }

    vector<PII> factorize(int n) { // be careful when n = 1
        vector<PII> ret;

        for (auto p : primes) {
            if (n % p) continue;
            int c = 0;
            while ((n % p) == 0) {
                ++c;
                n /= p;
            }
            ret.psb({p, c});
        }
        if (n != 1) ret.psb({n, 1});

        return ret;
    }


    int phi(int n) {
        int ret = n;
        vector<PII> pf = factorize(n);
        for (auto p : pf) {
            ret /= p.fi;
            ret *= p.fi - 1;
        }
        return ret;
    }
};