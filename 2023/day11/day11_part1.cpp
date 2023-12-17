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
    
    vector<vector<char>> col_expanded(map.size(), vector<char>(map[0].size() + empty_cols.size(), '.'));
    
    for (int row = 0; row < map.size(); row++) {
        int i = empty_cols.size() - 1;
        int read = map[row].size() - 1;
        int write = col_expanded[row].size() - 1;
        while (read >= 0) {
            if (i >=0 && read == empty_cols[i]) {
                write -= 2;
                i--;
            }
            else {
                col_expanded[row][write] = map[row][read];
                write--;
            }
            read--;
        }
    }
    
    /*
    for (auto row : col_expanded) {
        for (auto x : row) cout << x;
        cout << endl;
    }
     */
    
    vector<vector<char>> full_expanded(map.size() + empty_rows.size(), vector<char>(col_expanded[0].size(), '.'));
    
    for (int col = 0; col < col_expanded[0].size(); col++) {
        int i = empty_rows.size() - 1;
        int read = map.size() - 1;
        int write = full_expanded.size() - 1;
        while (read >= 0) {
            if (i >=0 && read == empty_rows[i]) {
                write -= 2;
                i--;
            }
            else {
                full_expanded[write][col] = col_expanded[read][col];
                write--;
            }
            read--;
        }
    }
    
    /*
    cout << endl;
    for (auto row : full_expanded) {
        for (auto x : row) cout << x;
        cout << endl;
    }
     */
    
    vector<pair<int, int>> galaxies;
    
    for (int r = 0; r < full_expanded.size(); r++) {
        for (int c = 0; c < full_expanded[r].size(); c++) {
            if (full_expanded[r][c] == '#') {
                galaxies.push_back({r, c});
            }
        }
    }
    
    int res = 0;
    
    for (int i = 0; i < galaxies.size() - 1; i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            res += abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second);
        }
    }
    
    cout << "Result: " << res << endl;
    
}
