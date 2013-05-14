#include <iostream>
#include <string>
using namespace std;

int p[1000];

int main() {
    string s;
    getline(cin, s, '\n');
    p[0] = 0;
    for (int i = 1; i < s.size(); ++i) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = p[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        p[i] = j;
    }
    for (int i = 0; i < s.size(); ++i) {
        printf("%d ", p[i]);
    }
    printf("\n");
    return 0;
}
