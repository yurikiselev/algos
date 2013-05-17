#include <iostream>
#include <vector>

std::vector<bool> prime;

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

int main() {
    int n = 10000;
    Generate(n);
    for (int i = 0; i < n; ++i) {
        if (prime[i]) {
            printf("%d ", i);
        }
    }
    return 0;
}
