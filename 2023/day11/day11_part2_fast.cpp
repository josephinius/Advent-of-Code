#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include <sstream>
#include <utility>

using namespace std;


struct PairHasher {
    long long operator() (const pair<int, int>& p) const {
        return 97 * p.first + p.second;
    }
};


int main() {
    ifstream f("input.txt");
    string s;
    vector<vector<char>> map;
    while (getline(f, s)) {
        map.push_back({});
        for (auto c : s) {
            map.back().push_back(c);
        }
    }
    f.close();
    
    for (auto row : map) {
        for (auto x : row) cout << x;
        cout << endl;
    }
    
    vector<int> empty_rows;
    
    int r = 0;
    for (auto row : map) {
        bool flag = true;
        for (auto x : row) {
            if (x == '#') {
                flag = false;
                break;
            }
        }
        if (flag) {
            empty_rows.emplace_back(r);
        }
        r++;
    }
    
    for (auto x : empty_rows) {
        cout << x << ", ";
    }
    cout << endl;
    
    vector<int> empty_cols;
    
    for (int c = 0; c < map[0].size(); c++) {
        bool flag = true;
        for (int r = 0; r < map.size(); r++) {
            if (map[r][c] == '#') {
                flag = false;
                break;
            }
        }
        if (flag) {
            empty_cols.emplace_back(c);
        }
    }
    
    for (auto x : empty_cols) {
        cout << x << ", ";
    }
    cout << endl;
    
    int expansion_factor = 1000000;
    
    vector<pair<int, int>> expanded;
    
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[r].size(); c++) {
            if (map[r][c] == '#') {
                int i = 0;
                while (i < empty_rows.size() && r > empty_rows[i]) {
                    i++;
                }
                int r_new = r + (expansion_factor - 1) * i;
                int j = 0;
                while (j < empty_cols.size() && c > empty_cols[j]) {
                    j++;
                }
                int c_new = c + (expansion_factor - 1) * j;
                expanded.push_back({r_new, c_new});
            }
        }
    }
    
    long long res = 0;
    
    cout << "expanded.size(): " << expanded.size() << endl;
    
    for (int i = 0; i < expanded.size() - 1; i++) {
        for (int j = i + 1; j < expanded.size(); j++) {
            res += abs(expanded[i].first - expanded[j].first) + abs(expanded[i].second - expanded[j].second);
        }
    }
    
    cout << "Result: " << res << endl;
    
}
