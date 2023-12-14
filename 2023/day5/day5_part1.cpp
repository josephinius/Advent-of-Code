#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_set>
#include <limits>
#include <algorithm>

using namespace std;

struct Map {
    vector<vector<long long>> ranges;  // {destination, source, range}
    long long map(long long source) {
        for (auto& vec : ranges) {
            if (vec[1] <= source && source <= vec[1] + vec[2] - 1) {
                return vec[0] + (source - vec[1]);
            }
        }
        return source;
    }
};


long long get_long_long(const string &s, int& i) {
    long long res = 0;
    while (i < s.size() && isdigit(s[i])) {
        res = res * 10 + (s[i] - '0');
        i++;
    }
    return res;
}


int main() {
    // cout << numeric_limits<int>::max() << endl;
    ifstream f("input.txt");
    string s;
    getline(f, s);
    cout << s << endl;
    int i = 7;
    vector<long long> seeds;
    while (i < s.size()) {
        long long n = get_long_long(s, i);
        seeds.emplace_back(n);
        i++;
    }
    for (auto x: seeds)
        cout << x << endl;
    cout << endl;
    
    getline(f, s);  // empty line
    getline(f, s);  // seed-to-soil map:

    getline(f, s);  // first line with ranges
    
    vector<Map> maps;
    
    for (int q = 0; q < 7; q++) {
        Map m;
        while (s.size() != 0) {
            vector<long long> range;
            int j = 0;
            for (int i = 0; i < 3; i++) {
                long long n = get_long_long(s, j);
                range.push_back(n);
                j++;
            }
            m.ranges.push_back(range);
            getline(f, s);
        }
        for (auto range : m.ranges) {
            for (auto x : range) {
                cout << x << ", ";
            }
            cout << endl;
        }
        maps.emplace_back(m);
        cout << endl;
        getline(f, s);
        getline(f, s);
    }
    
    // int seed = seeds[3];
    // cout << "m0.map(seed): " << m0.map(seed) << endl;
    
    for (auto& x : seeds) {
        for (auto m : maps) {
            x = m.map(x);
            cout << x << ", ";
        }
        cout << endl;
    }
    
    long long result = seeds[0];
    for (auto x : seeds) {
        result = min(result, x);
    }
    
    cout << "Result: " << result << endl;
    
    f.close();
}
