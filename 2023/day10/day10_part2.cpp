#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include <sstream>
#include <utility>

using namespace std;

typedef pair<int, int> pii;


struct PairHasher {
    int operator() (const pii& p) const {
        return 97 * p.first + p.second;
    }
};


bool is_inside(unordered_set<pii, PairHasher>& visited, const vector<vector<char>>& map, pair<int, int> pos) {
    int row = pos.first, col = pos.second;
    int count = 0;
    char history = '.';
    for (int c = col + 1; c < map[row].size(); c++) {
        if (visited.count({row, c})) {
            if (map[row][c] == '|') {
                count++;
            }
            else if (map[row][c] == '7' && history == 'L') {
                count++;
            }
            else if (map[row][c] == 'J' && history == 'F') {
                count++;
            }
            else if (map[row][c] == 'S') {
                count++;
            }
            if (map[row][c] != '-') {
                history = map[row][c];
            }
        }
    }
    // cout << "count: " << count << endl;
    return count % 2;
}


pair<int, int> make_step(unordered_set<pii, PairHasher>& visited, const vector<vector<char>>& map, pair<int, int> pos) {
    int row = pos.first, col = pos.second;
    char c = map[row][col];
    if (c == '|') {
        if (visited.count({row + 1, col})) {
            return {row - 1, col};
        }
        else {
            return {row + 1, col};
        }
    }
    if (c == '-') {
        if (visited.count({row, col - 1})) {
            return {row, col + 1};
        }
        else {
            return {row, col - 1};
        }
    }
    if (c == 'L') {
        if (visited.count({row - 1, col})) {
            return {row, col + 1};
        }
        else {
            return {row - 1, col};
        }
    }
    if (c == 'J') {
        if (visited.count({row - 1, col})) {
            return {row, col - 1};
        }
        else {
            return {row - 1, col};
        }
    }
    if (c == '7') {
        if (visited.count({row + 1, col})) {
            return {row, col - 1};
        }
        else {
            return {row + 1, col};
        }
    }
    if (c == 'F') {
        if (visited.count({row + 1, col})) {
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
    
    unordered_set<pii, PairHasher> visited;
    // map[start.first][start.second] = 'V';  // marking as visited
    visited.insert(start);
    
    while (x1 != x2) {
        // step from x1
        pair<int, int> x1p = make_step(visited, map, x1);
        visited.insert(x1);  // marking as visited
        x1 = x1p;
        // step from x2
        pair<int, int> x2p = make_step(visited, map, x2);
        visited.insert(x2);  // marking as visited
        x2 = x2p;
        distance++;
    }
    visited.insert(x1);  // marking as visited

    cout << "Result (part one): " << distance << endl;
    
    int num_of_inside = 0;
             
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (visited.count({i, j}) == 0 && is_inside(visited, map, {i, j})) {
                num_of_inside++;
                // cout << i << ", " << j << endl;
            }
        }
    }
         
    cout << "Result (part two): " << num_of_inside << endl;
}
