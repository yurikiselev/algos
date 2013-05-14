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

string IntToRom(int x) {
    const string rom = "IVXLCDM";
    string res;
    for (int i = 0; x > 0; x /= 10, i += 2) {
        int val = x % 10;
        if (val <= 3) {
            res = string(val, rom[i]) + res;
        } else {
            if (val == 4) {
                res = string(1, rom[i + 1]) + res;
                res = string(1, rom[i]) + res;
            } else {
                if (val == 5) {
                    res = string(1, rom[i + 1]) + res;
                } else {
                    if (val < 9) {
                        res = string(val - 5, rom[i]) + res;
                        res = string(1, rom[i + 1]) + res;
                    } else {
                        res = string(1, rom[i + 2]) + res;
                        res = string(1, rom[i]) + res;
                    }
                }
            }
        }
    }
    return res;
}

int RomToInt(const string& str) {
    const char rom[] = {'I', 'V', 'X', 'L', 'C', 'D',  'M'};
    const int  val[] = { 1,   5,   10,  50,  100, 500, 1000};
    int res = 0;
    for (int i = 0; i < str.size(); ++i) {
        int x = 0, sign = 1;
        for (int j = 0; j < 7; ++j)
            if (rom[j] == str[i]) {
                x = val[j];
                for (int k = j + 1; k < 7; ++k)
                    if (i + 1 < str.size() && str[i + 1] == rom[k]) {
                        sign = -1;
                        break;
                    }
                break;
            }
        res += x * sign;
    }
    return res;
}

void Solve() {
    for (int i = 1; i < 4000; ++i) {
        string str = IntToRom(i);
        int x = RomToInt(str);
        if (i != x) 
            cerr << "Error: " << i << ' ' << str << ' ' << x << endl;
    }
    cerr << "Done!\n";
}

int main() {
    Solve();
    return 0;
}

