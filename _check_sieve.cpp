#include <iostream>
#include <vector>

using namespace std;

vector<bool> prime;

const int MAXN = 40 * 1000;

void Generate(int n) {
    prime.resize(n, true);
    prime[0] = prime[1] = false;
    for (int i = 2; i < n; ++i) {
        if (!prime[i])
            continue;
        for (int j = i * i; j < n; j += i) {
            prime[j] = false;
        }
    }
}

bool IsPrime(int x) {
    if (x == 1)
        return false;
    if (x == 2)
        return true;
    if (x % 2 == 0)
        return 0;
    for (int i = 3; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    return true;
}

bool Test(int n) {
    for (int i = 1; i < n; ++i)
        if (prime[i] != IsPrime(i)) {
            cerr << "bad - " << i << endl;
            return false;
        }
    return true;
}

int main() {
    Generate(MAXN);
    if (Test(MAXN))
        cerr << "Ok!\n";
    else
        cerr << "Error!\n";
    cerr << "Done\n";
    return 0;
}
