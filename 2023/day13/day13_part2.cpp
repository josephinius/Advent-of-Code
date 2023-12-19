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


int find_vertical_reflection(const vector<vector<char>>& pattern) {
    const int rows = pattern.size();
    const int cols = pattern[0].size();
    for (int i = 1; i < cols; i++) {
        int count = 0;
        for (int r = 0; r < rows && count <= 1; r++) {
            for (int j = 0; j < min(i, cols - i) && count <= 1; j++) {
                if (pattern[r][i - j - 1] != pattern[r][i + j]) {
                    count++;
                }
            }
        }
        if (count == 1) {
            return i;
        }
    }
    return - 1;
}


int find_horizontal_reflection(const vector<vector<char>>& pattern) {
    const int rows = pattern.size();
    const int cols = pattern[0].size();
    for (int i = 1; i < rows; i++) {
        int count = 0;
        for (int c = 0; c < cols && count <= 1; c++) {
            for (int j = 0; j < min(i, rows - i) && count <= 1; j++) {
                if (pattern[i - j - 1][c] != pattern[i + j][c]) {
                    count++;
                }
            }
        }
        if (count == 1) {
            return i;
        }
    }
    return - 1;
}


int main() {
    ifstream f("input.txt");
    string s;
    
    int res = 0;
    
    while (getline(f, s)) {
        
        vector<vector<char>> pattern;

        while (s != "") {
            pattern.push_back({});
            for (auto c : s) {
                pattern.back().push_back(c);
            }
            getline(f, s);
        }
        
        int ver = find_vertical_reflection(pattern);
        // cout << "ver: " << ver << endl;
        
        if (ver != -1) {
            res += ver;
        }
        
        int hor = find_horizontal_reflection(pattern);
        // cout << "hor: " << hor << endl;
        if (hor != -1) {
            res += 100 * hor;
        }
        
    }
    f.close();
    
    cout << "Result: " << res << endl;
}
