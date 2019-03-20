#include <bits/stdc++.h>
using namespace std;

#define LL 					long long
#define DB					double
#define ULL 				unsigned long long
#define PII 				pair<int,int>

#define mp					make_pair
#define fi 					first
#define se 					second
#define psb 				push_back
#define ppb 				pop_back
#define endln 				printf("\n")

#define ALL(x)			 	(x).begin(),(x).end()
#define SZ(x)				(int)(x).size()

#define SETMIN(x)			memset((x), -1, sizeof (x))
#define SETNUL(x)			memset((x),  0, sizeof (x))
#define gc					getchar_unlocked

#ifndef getchar_unlocked
#define getchar_unlocked 	getchar
#endif

const int INF = 1e9 + 5;
const LL INFLL = 1e18+5;
const int MOD = 1e9 + 7;

template <typename T>
void gi(T &ret) {
	ret = 0; char inp = gc(); bool isNeg = 0;
	while (inp < '0' || inp > '9') { 
		if (inp == '-') isNeg = 1; 
		inp = gc();
	}
	while ('0' <= inp && inp <= '9') {
		ret = (ret << 3) + (ret << 1) + (inp - '0');
		inp = gc();
	}
	if (isNeg) ret = -ret;
}

void readInput() {
	
}

void solve() {
	
}

int main() {
	int tc; gi(tc);
	for (int cs = 1; cs <= tc; cs++) {
		readInput();
		solve();
	}
	return 0;
}
