const int MAXN_SA = 5e5 + 5;
const int MAXLOGN_SA = 21;

struct SuffixArray {
    int n, val[MAXN_SA], LOGN;
    int rank[MAXLOGN_SA][MAXN_SA], ord[MAXN_SA], tmpOrd[MAXN_SA], cntNum[MAXN_SA];
    int inv[MAXN_SA];

    void setVal(vector<int> vec) {
        n = SZ(vec);
        for (int i = 0; i < n; ++i)
            val[i] = vec[i];
    }

    void countSort(int k, int off) {
        int lim = 0;

        for (int i = 0; i < n; ++i) {
            int rk = i + off < n ? rank[k][i + off] : 0;
            lim = max(lim, rk);
        }
        
        for (int i = 0; i <= lim; ++i)
            cntNum[i] = 0;

        for (int i = 0; i < n; ++i) {
            int rk = i + off < n ? rank[k][i + off] : 0;
            cntNum[rk]++;
        }

        for (int i = 1; i <= lim; ++i)
            cntNum[i] += cntNum[i - 1];

        for (int i = n - 1; i >= 0; --i) {
            int rk = ord[i] + off < n ? rank[k][ord[i] + off] : 0;
            tmpOrd[--cntNum[rk]] = ord[i];
        }

        for (int i = 0; i < n; ++i)
            ord[i] = tmpOrd[i];
    }

    bool cmp(int a, int b) {
        return val[a] < val[b];
    }

    void initRank() {
        vector<PII> sr;
        for (int i = 0; i < n; ++i)
            sr.psb({val[i], i});
        sort(ALL(sr));

        rank[0][sr[0].se] = 0;
        ord[0] = sr[0].se;

        for (int i = 1; i < n; ++i) {
            if (sr[i].fi == sr[i - 1].fi)
                rank[0][sr[i].se] = rank[0][sr[i - 1].se];
            else
                rank[0][sr[i].se] = rank[0][sr[i - 1].se] + 1;

            ord[i] = sr[i].se;
        }
    }

    void printOrd() {
        for (int i = 0; i < n; ++i)
            printf("%d ", ord[i]);
        endln;
    }

    void printRank(int k) {
        for (int i = 0; i < n; ++i)
            printf("%d ", rank[k][i]);
        endln;
    }

    void computeSA() {
        initRank();
        
        for (int k = 1; (1 << k) <= n; ++k) {
            int off = 1 << (k - 1);

            countSort(k - 1, off);
            countSort(k - 1, 0);
        
            rank[k][ord[0]] = 0;
            for (int i = 1; i < n; ++i) {

                int ra = ord[i - 1] + off < n ? rank[k - 1][ord[i - 1] + off] : 0;
                int rb = ord[i]     + off < n ? rank[k - 1][ord[i]     + off] : 0;

                if (rank[k - 1][ord[i]] == rank[k - 1][ord[i - 1]] && ra == rb)
                    rank[k][ord[i]] = rank[k][ord[i - 1]];
                else
                    rank[k][ord[i]] = rank[k][ord[i - 1]] + 1;
            }

            LOGN = k;

            if (rank[k][ord[n - 1]] == (n - 1))
                break;
        }
    }

    void computeInv() {
        for (int i = 0; i < n; ++i)
            inv[ord[i]] = i;
    }
};