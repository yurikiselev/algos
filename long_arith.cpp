#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int BASE = 1000;

typedef vector<int> TLong;

void Normalize(TLong& v) {
    if (v.empty()) {
        v.push_back(0);
    }
    while (!v.empty() && v.back() == 0) {
        v.pop_back();
    }
}

bool Eq(TLong a, TLong b) {
    Normalize(a);
    Normalize(b);
    return a == b;
}

void Print(const TLong& v) {
    printf("%d", v.empty() ? 0 : v.back());
    for (int i = (int)v.size() - 2; i >= 0; --i) {
        printf("%03d", v[i]);
    }
    printf("\n");
}

TLong Read(const string& s) {
    TLong res;
    for (int i = s.size(); i > 0; i -= 3) {
        if (i < 3) {
            res.push_back(atoi(s.substr(0, i).c_str()));
        } else {
            res.push_back(atoi(s.substr(i - 3, 3).c_str()));
        }
    }
    return res;
}

TLong Read(int x) {
    TLong res;
    while (x) {
        res.push_back(x % BASE);
        x /= BASE;
    }
    return res;
}

TLong Sum(const TLong& a, const TLong& b) {
    TLong res;
    int carry = 0;
    for (int i = 0; i < max(a.size(), b.size()); ++i) {
        int x = i < a.size() ? a[i] : 0;
        int y = i < b.size() ? b[i] : 0;
        res.push_back((x + y + carry) % BASE);
        carry = (x + y + carry) / BASE;
    }
    if (carry) {
        res.push_back(carry);
    }
    return res;
}

TLong Ext(const TLong& a, const TLong& b) {
    TLong res;
    int carry = 0;
    for (int i = 0; i < a.size(); ++i) {
        res.push_back(a[i] - (carry + (i < b.size() ? b[i] : 0)));
        carry = res[i] < 0;
        if (carry) {
            res[i] += BASE;
        }
    }
    Normalize(res);
    return res;
}

TLong Mul(const TLong& a, const TLong& b) {
    TLong res(a.size() + b.size());
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0, carry = 0; j < b.size() || carry; ++j) {
            long long cur = res[i + j] + carry + 1LL * a[i] * (j < b.size() ? b[j] : 0);
            res[i + j] = cur % BASE;
            carry = cur / BASE;
        }
    }
    return res;
}

int main() {
    for (int i = 0; i < 20; ++i) {
        int a = rand() % (BASE * BASE * BASE);
        int b = rand() % (BASE * BASE * BASE);
        if (!Eq(Sum(Read(a), Read(b)), Read(a + b))) {
            cerr << "Error in Sum operator!\n";
            return 0;
        }
        if (a < b) {
            swap(a, b);
        }
        if (!Eq(Ext(Read(a), Read(b)), Read(a - b))) {
            cerr << "Error in Ext operator!\n";
            return 0;
        }
        a %= 10000;
        b %= 10000;
        if (!Eq(Mul(Read(a), Read(b)), Read(a * b))) {
            cerr << "Error in Mul operation\n";
            return 0;
        }
    }
    printf("Everyrhing is OK!\n");
    return 0;
}
