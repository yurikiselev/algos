class Solution {
public:
    int GetLen(const char* s) {
		int len = 0;
		while (*s != '\0') {
			++s;
			++len;
		}
		return len;
	}
	void FillPref(const char* s, vector<int>& pref) {
		if (pref.empty())
			return;
		const char* ptr = s + 1;
		while (true) {
			int i = ptr - s;
			int j = pref[i - 1];
			while (j && s[j] != s[i])
				j = pref[j - 1];
			if (s[i] == s[j])
				++j;
			pref[i] = j;
			if (*ptr == '\0')
				break;
			++ptr;
		}
	}
    char *strStr(char* haystack, char* needle) {
        if (*needle == '\0')
            return haystack;

		int lenNeed = GetLen(needle);
		int lenHay = GetLen(haystack);
		vector<int> pref(lenNeed + 1, 0);
		FillPref(needle, pref);
		int p = 0;
		while (*haystack != '\0') {
			int newP = p;
			while (newP && *haystack != *(needle + newP))
				newP = pref[newP - 1];
			if (*haystack == *(needle + newP))
				++newP;
			p = newP;
			if (p == lenNeed)
				return haystack - p + 1;
            ++haystack;
		}
		return 0;
    }
};