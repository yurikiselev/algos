#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <list>
#include <functional>
#include <queue>
#include <iterator>

using namespace std;

bool IsPalindrome(int x) {
    if (x < 0)
        return false;
    if (x == 0)
        return true;
    int div = 1;
    while (x / div >= 10)
        div *= 10;
    while (x) {
        int l = x / div;
        int r = x % 10;
        if (l != r)
            return false;
        x = (x % div) / 10;
        div /= 100; // !!! 100 !!!
    }
    return true;
}

bool IsPalindromeStr(int x) {
    if (x < 0)
        return false;
    string str;
    while (x) {
        str.push_back('0' + x % 10);
        x /= 10;
    }
    int len = str.size();
    for (int i = 0; i < len / 2; ++i)
        if (str[i] != str[len - 1 - i])
            return false;
    return true;
}

int main()
{
    for (long long i = numeric_limits<int>::min(); i <= numeric_limits<int>::max(); i += rand() % 1000) {
        bool isPal = IsPalindrome(i);
        if (isPal != IsPalindromeStr(i))
            cerr << "Error!";
        if (isPal)
            cerr << "1";
    }
    cerr << "\nDone!\n";
    return 0;
}      

