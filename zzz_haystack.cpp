class Solution {
public:
    void Calc(const char* s, vector<int>& pref) {
        pref.push_back(0);
        for (int i = 1; s[i] != '\0'; ++i) {
            int j = pref[i - 1];
            while (j && s[j] != s[i])
                j = pref[j - 1];
            if (s[j] == s[i])
                ++j;
            pref.push_back(j);
        }
    }
    char *strStr(char* haystack, char* needle) {
        if (*needle == '\0')
            return haystack;
        vector<int> pref;
        Calc(needle, pref);
        int p = 0;
        for (int i = 0; haystack[i] != '\0'; ++i) {
            int j = p;
            while (j && haystack[i] != needle[j])
                j = pref[j - 1];
            if (haystack[i] == needle[j])
                ++j;
            p = j;
            if (p == pref.size())
                return haystack + i - p + 1;
        }
        return 0;
    }
};

