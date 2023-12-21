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


void drop_north(vector<vector<char>>& platform, int r, int c) {
    platform[r][c] = '.';
    int i = r;
    while (i > 0 && platform[i - 1][c] == '.') {
        i--;
    }
    platform[i][c] = 'O';
}


void tilt_north(vector<vector<char>>& platform) {
    for (int r = 0; r < platform.size(); r++) {
        for (int c = 0; c < platform[r].size(); c++) {
            if (platform[r][c] == 'O') {
                drop_north(platform, r, c);
            }
        }
    }
}


int calculate_total_load(const vector<vector<char>>& platform) {
    int res = 0;
    for (int r = 0; r < platform.size(); r++) {
        for (int c = 0; c < platform[r].size(); c++) {
            if (platform[r][c] == 'O') {
                res += platform.size() - r;
            }
        }
    }
    return res;
}


int main() {
    ifstream f("input.txt");
    string s;
    vector<vector<char>> platform;
    while (getline(f, s)) {
        platform.push_back({});
        for (auto c : s) {
            platform.back().push_back(c);
        }
    }
    
    /*
    for (auto vec : platform) {
        for (auto c : vec) {
            cout << c;
        }
        cout << endl;
    }
     */
    
    tilt_north(platform);
    cout << endl;
    
    /*
    for (auto vec : platform) {
        for (auto c : vec) {
            cout << c;
        }
        cout << endl;
    }
     */
    
    int res = calculate_total_load(platform);
    
    cout << "Result: " << res << endl;
    
    f.close();
}
