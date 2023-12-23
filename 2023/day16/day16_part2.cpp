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

typedef pair<int, int> pii;

const vector<int> dirs = {0, 1, 0, -1, 0};

struct Beam {
    pii pos;
    int dir;  // 0: right, 1: down, 2: left, 3: up
};


vector<Beam> neighbors_helper(int rows, int cols, int r, int c, int dir) {
    int r_new = r + dirs[dir];
    int c_new = c + dirs[dir + 1];
    if (r_new < 0 || r_new >= rows || c_new < 0 || c_new >= cols) {
        return {};  // going outside of the diagram
    }
    Beam b_new;
    b_new.pos = {r_new, c_new};
    b_new.dir = dir;
    return {b_new};
}

vector<Beam> neighbors(const Beam& b, const vector<vector<char>>& diag) {
    const int rows = diag.size(), cols = diag[0].size();
    auto [r, c] = b.pos;
    auto dir = b.dir;
    char x = diag[r][c];
    if (x == '.') {
        return neighbors_helper(rows, cols, r, c, dir);
    }
    if (x == '/') {
        if (dir == 0) {  // right -> up
            dir = 3;
            return neighbors_helper(rows, cols, r, c, dir);
        }
        else if (dir == 1) {  // down -> left
            dir = 2;
            return neighbors_helper(rows, cols, r, c, dir);
        }
        else if (dir == 2) {  // left -> down
            dir = 1;
            return neighbors_helper(rows, cols, r, c, dir);
        }
        else {  // (dir == 3)  // up -> right
            dir = 0;
            return neighbors_helper(rows, cols, r, c, dir);
        }
    }
    if (x == '\\') {
        if (dir == 0) {  // right -> down
            dir = 1;
            return neighbors_helper(rows, cols, r, c, dir);
        }
        else if (dir == 1) {  // down -> right
            dir = 0;
            return neighbors_helper(rows, cols, r, c, dir);
        }
        else if (dir == 2) {  //  left -> up
            dir = 3;
            return neighbors_helper(rows, cols, r, c, dir);
        }
        else {  // (dir == 3)  // up -> right
            dir = 2;
            return neighbors_helper(rows, cols, r, c, dir);
        }
    }
    if (x == '-') {
        if (dir == 0 || dir == 2) {
            return neighbors_helper(rows, cols, r, c, dir);
        }
        else {
            int r_new1 = r + dirs[0], c_new1 = c + dirs[1];

            Beam b_new1;
            b_new1.pos = {r_new1, c_new1};
            b_new1.dir = 0;
            
            int r_new2 = r + dirs[2], c_new2 = c + dirs[3];

            Beam b_new2;
            b_new2.pos = {r_new2, c_new2};
            b_new2.dir = 2;

            bool flag1 = true;
            if (r_new1 < 0 || r_new1 >= rows || c_new1 < 0 || c_new1 >= cols) {
                flag1 = false;
            }
            bool flag2 = true;
            if (r_new2 < 0 || r_new2 >= rows || c_new2 < 0 || c_new2 >= cols) {
                flag2 = false;
            }
            
            if (!flag1 && !flag2) {
                return {};
            }
            if (flag1 && flag2) {
                return {b_new1, b_new2};
            }
            if (flag1) {
                return {b_new1};
            }
            if (flag2) {
                return {b_new2};
            }
        }
    }
    if (x == '|') {
        if (dir == 1 || dir == 3) {
            return neighbors_helper(rows, cols, r, c, dir);
        }
        else {
            int r_new1 = r + dirs[1], c_new1 = c + dirs[2];

            Beam b_new1;
            b_new1.pos = {r_new1, c_new1};
            b_new1.dir = 1;
                
            int r_new2 = r + dirs[3], c_new2 = c + dirs[4];

            Beam b_new2;
            b_new2.pos = {r_new2, c_new2};
            b_new2.dir = 3;

            bool flag1 = true;
            if (r_new1 < 0 || r_new1 >= rows || c_new1 < 0 || c_new1 >= cols) {
                flag1 = false;
            }
            bool flag2 = true;
            if (r_new2 < 0 || r_new2 >= rows || c_new2 < 0 || c_new2 >= cols) {
                flag2 = false;
            }
                
            if (!flag1 && !flag2) {
                return {};
            }
            if (flag1 && flag2) {
                return {b_new1, b_new2};
            }
            if (flag1) {
                return {b_new1};
            }
            if (flag2) {
                return {b_new2};
            }
        }
    }
    return {};
}


void dfs(Beam b, const vector<vector<char>>& diag, vector<vector<vector<int>>>& visited) {
    auto [r, c] = b.pos;
    auto dir = b.dir;
    visited[r][c][dir] = 1;
    for (auto n : neighbors(b, diag)) {
        auto [nr, nc] = n.pos;
        auto ndir = n.dir;
        if (visited[nr][nc][ndir] != 1) {
            dfs(n, diag, visited);
        }
    }
}


int count_energized_tiles(Beam& start, const vector<vector<char>>& diag) {
    const int rows = diag.size(), cols = diag[0].size();
    vector<vector<vector<int>>> visited(rows, vector<vector<int>>(cols, vector<int>(4, 0)));
    dfs(start, diag, visited);
    int counter = 0;
    // vector<vector<char>> schema;
    for (int r = 0; r < rows; r++) {
        // schema.push_back({});
        for (int c = 0; c < cols; c++) {
            bool flag = false;
            for (auto x : visited[r][c]) {
                if (x == 1) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                counter++;
                // schema.back().push_back('#');
            }
            else {
                // schema.back().push_back('.');
            }
        }
    }
    /*
    cout << endl;
    for (auto vec : schema) {
        for (auto c : vec) {
            cout << c;
        } cout << endl;
    }
     */
    return counter;
}


int main() {
    ifstream f("input.txt");
    string s;
    
    vector<vector<char>> diag;
    
    while (getline(f, s)) {
        diag.push_back({});
        for (auto c : s) {
            diag.back().push_back(c);
        }
    }
    
    /*
    for (auto vec : diag) {
        for (auto c : vec) {
            cout << c;
        } cout << endl;
    }
     */
    
    f.close();
    
    const int rows = diag.size(), cols = diag[0].size();

    int res = 0;
    
    for (int r = 0; r < rows; r++) {
        Beam start;
        start.pos = {r, 0};
        start.dir = 0;  // goes to right
        res = max(res, count_energized_tiles(start, diag));
        start.pos = {r, cols - 1};
        start.dir = 2;  // goes to left
        res = max(res, count_energized_tiles(start, diag));
    }
    
    for (int c = 0; c < cols; c++) {
        Beam start;
        start.pos = {0, c};
        start.dir = 1;  // goes to down
        res = max(res, count_energized_tiles(start, diag));
        start.pos = {rows - 1, c};
        start.dir = 3;  // goes to up
        res = max(res, count_energized_tiles(start, diag));
    }
    
    cout << "Result: " << res << endl;
}
