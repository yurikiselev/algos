class Solution {
public:
    string ToString(int x) {
    	string res;
		while (x) {
			res.push_back('0' + x % 10);
			x /= 10;
		}
		reverse(res.begin(), res.end());
		return res;
	}
	void Add(int amount, char value, string& s) {
		s += ToString(amount);
        s.push_back(value);
	}
	string Generate(const string& s) {
		int n = s.size();
		int st = 0;
		string res;
		for (int i = 1; i < n; ++i) {
			if (s[i] != s[st]) {
				Add(i - st, s[st], res);
				st = i;
			}
		}
		Add(n - st, s[st], res);
        return res;
	}
    string countAndSay(int n) {
        string res = "1";
		for (int i = 2; i <= n; ++i) {
			res = Generate(res);
		}
		return res;
    }
};