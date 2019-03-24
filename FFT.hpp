//flow of the program
//fft.init(A, B); fft.multiply();
//complex : real, imag
//Implementation by: Yehezkiel R.T.
struct FFT{
    private:
    vector <complex<DB>> A, B;
    
    public:
    template <typename T1, typename T2>
    void init(vector <T1> _A, vector <T2> _B) {
        A.resize(_A.size());
        for (int i = 0; i < (int) _A.size(); ++i) {
            A[i] = _A[i];
        }
        B.resize(_B.size());
        for (int i = 0; i < (int) _B.size(); ++i) {
            B[i] = _B[i];
        }
        
        int newSize = max(A.size(), B.size());
        while((newSize & (newSize - 1)) != 0) {
            newSize += newSize & -newSize;      //add lsone continously
        }
        
        A.resize(newSize, complex<DB>(0));
        B.resize(newSize, complex<DB>(0));
    }
    
    private:
    vector<complex<DB>> fft(const vector<complex<DB>> &coef, bool inverse) {
        int n = coef.size();
        
        //base case
        if (n == 1) {
            return vector<complex<DB>>(1, coef[0]);
        }
        
        //recursive part
        vector <complex<DB>> even(n >> 1), odd(n >> 1);
        for (int i = 0; i < (int) n; i += 2) {
            even[i >> 1] = coef[i];
            odd[(i + 1) >> 1] = coef[i + 1];
        }
        even = fft(even, inverse);
        odd = fft(odd, inverse);
        
        //merging
        DB rad = (DB) 2.0 * (DB) acos(-1.0) / (DB) n;
        if (inverse) rad = -rad;
        complex<DB> base(cos(rad), sin(rad));
        complex<DB> unity(1.0);
        
        vector <complex<DB>> ret(n);
        for(int i = 0; i < (n >> 1); ++i) {
            ret[i] = even[i] + unity * odd[i];
            ret[i + (n >> 1)] = even[i] - unity * odd[i];
            unity *= base;
        }
        
        return ret;
    }
    
    public:
    vector <complex<DB>> multiply() {
        A.resize(A.size() << 1, complex<DB>(0));
        B.resize(B.size() << 1, complex<DB>(0));        //2*n point value
        
        vector <complex<DB>> pointA = fft(A, false);
        vector <complex<DB>> pointB = fft(B, false);
        
        //convolution
        vector <complex<DB>> pointC(pointA.size());
        for (int i = 0; i < (int) pointC.size(); ++i) {
            pointC[i] = pointA[i] * pointB[i];
        }
        
        //inverse
        vector <complex<DB>> C = fft(pointC, true);
        for (int i = 0; i < (int) C.size(); ++i) {
            C[i] = C[i] / (DB) C.size();
        }
        return C;
    }
};
FFT fft;