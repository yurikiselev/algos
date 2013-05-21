#include <iostream>
#include <string>

using namespace std;

typedef unsigned int UI;

const int MAXN = 5000;
const UI P = 3137;

class THasher {
private:
	UI a[MAXN];
	UI p[MAXN];
public:
	THasher(const string &s) {
		UI h = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			h = h * P + (s[i] - 'a') + 1; // +1 is really important!
			a[i] = h;
		}
		p[0] = 1;
		for (size_t i = 1; i < s.size(); ++i) {
			p[i] = p[i - 1] * P;
		}
	}
	UI GetHash(int i, int j) {
		if (i == 0) {
			return a[j];
		}
		return a[j] - a[i - 1] * p[j - i + 1];
	}
};

short a[1 << 24];

void Add(int &cnt, UI hash, int len) {
	hash &= (1 << 24) - 1;
	if (a[hash] != len) {
		++cnt;
		a[hash] = len;
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	string s;
	cin >> s;
	THasher hasher(s);

	int ans = 0;
	for (size_t len = 1; len <= s.size(); ++len) {
		int cnt = 0;
		for (size_t pos = 0; pos + len <= s.size(); ++pos) {
			Add(cnt, hasher.GetHash(pos, pos + len - 1), len);
		}
		ans += cnt;
	}
	cout << ans << endl;
	return 0;
}