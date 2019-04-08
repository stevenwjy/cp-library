void buildKMP(const string& P, int* fail) {
	fail[0] = -1;
	int j = -1, i = 0;
	while (i < SIZE(P)) {
		while (j > 0 && P[i] != P[j]) j = fail[j];
		++i; ++j;
		fail[i] = j;
	}
}
void find(const string& P, const string& T, int* fail) {
	int i = 0, j = 0;
	while (i < SIZE(T)) {
		while (j >= 0 && P[j] != T[i]) j = fail[j];
		++i; ++j;
		if (j == SIZE(P)) {
			// found at T[i - j + 1 .. i]
			j = fail[j];
		}
	}
}