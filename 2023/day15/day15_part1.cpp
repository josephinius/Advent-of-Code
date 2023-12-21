#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <sstream>
#include <utility>

using namespace std;


int main() {
    ifstream f("input.txt");
    string s;
    int hash = 0;
    int res = 0;
    while (getline(f, s)) {
        for (auto c : s) {
            if (c == ',') {
                res += hash;
                hash = 0;
            }
            else {
                hash += c - ' ' + 32;
                hash *= 17;
                hash %= 256;
            }
            
        }
    }
    res += hash;

    cout << "Result: " << res << endl;
    
    f.close();
}
