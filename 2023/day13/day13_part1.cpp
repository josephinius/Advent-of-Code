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
        bool flag = true;
        for (int r = 0; r < rows && flag; r++) {
            for (int j = 0; j < min(i, cols - i); j++) {
                if (pattern[r][i - j - 1] != pattern[r][i + j]) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            return i;
        }
        
    }
    return - 1;
}


int find_horizontal_reflection(const vector<vector<char>>& pattern) {
    const int rows = pattern.size();
    const int cols = pattern[0].size();
    
    for (int i = 1; i < rows; i++) {
        bool flag = true;
        
        for (int c = 0; c < cols && flag; c++) {
            for (int j = 0; j < min(i, rows - i); j++) {
                if (pattern[i - j - 1][c] != pattern[i + j][c]) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
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
        
        for (auto vec : pattern) {
            for (auto c : vec) {
                cout << c;
            }
            cout << endl;
        }
        cout << endl;
        
        int ver = find_vertical_reflection(pattern);
        cout << "ver: " << ver << endl;
        
        if (ver != -1) {
            res += ver;
        }
        
        int hor = find_horizontal_reflection(pattern);
        cout << "hor: " << hor << endl;
        if (hor != -1) {
            res += 100 * hor;
        }
        
    }
    f.close();
    
    cout << "Result: " << res << endl;
    
}
