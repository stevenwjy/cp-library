struct ExtendedEuclid { // ax + by = c
    LL a, x, b, y, c;

    ExtendedEuclid(LL _a, LL _b) {
        a = _a;
        b = _b;
    }

    void process(LL a, LL b, LL &x, LL &y) {
        if (b == 0) {
            x = 1LL;
            y = 0LL;
            c = a;
            return;
        }

        LL x1, y1;
        process(b, a % b, x1, y1);
        x = y1;
        y = x1 - (a / b) * y1;
    }

    pair<LL,LL> compute() {
        process(a, b, x, y);
        
        LL lcm = a * b / c;
        
        if (y >= 0) {
            LL mtp = ((y + (lcm / b)) / (lcm / b));
            
            x += mtp * (lcm / a);
            y -= mtp * (lcm / b);
        }

        return {x, y};
    }
};
