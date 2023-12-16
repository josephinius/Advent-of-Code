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


pair<int, int> make_step(const vector<vector<char>>& map, pair<int, int> pos) {
    int row = pos.first, col = pos.second;
    char c = map[row][col];
    if (c == '|') {
        if (map[row + 1][col] == 'V') {
            return {row - 1, col};
        }
        else {
            return {row + 1, col};
        }
    }
    if (c == '-') {
        if (map[row][col - 1] == 'V') {
            return {row, col + 1};
        }
        else {
            return {row, col - 1};
        }
    }
    if (c == 'L') {
        if (map[row - 1][col] == 'V') {
            return {row, col + 1};
        }
        else {
            return {row - 1, col};
        }
    }
    if (c == 'J') {
        if (map[row - 1][col] == 'V') {
            return {row, col - 1};
        }
        else {
            return {row - 1, col};
        }
    }
    if (c == '7') {
        if (map[row + 1][col] == 'V') {
            return {row, col - 1};
        }
        else {
            return {row + 1, col};
        }
    }
    if (c == 'F') {
        if (map[row + 1][col] == 'V') {
            return {row, col + 1};
        }
        else {
            return {row + 1, col};
        }
    }
    return {-1, -1};
}


int main() {
    ifstream f("input.txt");
    string s;
    vector<vector<char>> map;
    pair<int, int> start;
    int row = 0;
    while (getline(f, s)) {
        int col = 0;
        map.push_back({});
        for (auto c : s) {
            if (c == 'S') {
                start.first = row;
                start.second = col;
            }
            map.back().push_back(c);
            col++;
        }
        row++;
    }
    f.close();
    
    vector<pair<int, int>> entrances;  // entrances into the pipe (should be exactly two)
    
    auto [r, c] = start;
    // try west (left)
    if (c > 0) {
        char x = map[r][c - 1];
        if (x == 'F' || x == 'L' || x == '-') {
            entrances.push_back({r, c - 1});
        }
    }
    // try east (right)
    if (c < map[0].size() - 1) {
        char x = map[r][c + 1];
        if (x == '-' || x == 'J' || x == '7') {
            entrances.push_back({r, c + 1});
        }
    }
    // try north (up)
    if (r > 0) {
        char x = map[r - 1][c];
        if (x == 'F' || x == '7' || x == '|') {
            entrances.push_back({r - 1, c});
        }
    }
    // try south (down)
    if (r < map.size() - 1) {
        char x = map[r + 1][c];
        if (x == '|' || x == 'L' || x == 'J') {
            entrances.push_back({r + 1, c});
        }
    }
    
    int distance = 1;
    pair<int, int> x1 = entrances[0];
    pair<int, int> x2 = entrances[1];
    
    map[start.first][start.second] = 'V';  // marking as visited
    
    while (x1 != x2) {
        // step from x1
        pair<int, int> x1p = make_step(map, x1);
        map[x1.first][x1.second] = 'V';  // marking as visited
        x1 = x1p;
        // step from x2
        pair<int, int> x2p = make_step(map, x2);
        map[x2.first][x2.second] = 'V';  // marking as visited
        x2 = x2p;
        distance++;
    }
    
    cout << "Result: " << distance << endl;
}
