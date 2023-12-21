#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <sstream>

using namespace std;


struct GridHasher {
    long long operator() (const vector<vector<char>>& grid) const {
        long long hash = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 'O') {
                    hash += 97 * i + j;
                }
            }
        }
        return hash;
    }
};


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


void drop_south(vector<vector<char>>& platform, int r, int c) {
    platform[r][c] = '.';
    int i = r;
    while (i < platform.size() - 1 && platform[i + 1][c] == '.') {
        i++;
    }
    platform[i][c] = 'O';
}


void tilt_south(vector<vector<char>>& platform) {
    for (int r = platform.size() - 1; r >= 0; r--) {
        for (int c = 0; c < platform[r].size(); c++) {
            if (platform[r][c] == 'O') {
                drop_south(platform, r, c);
            }
        }
    }
}


void drop_west(vector<vector<char>>& platform, int r, int c) {
    platform[r][c] = '.';
    int i = c;
    while (i > 0 && platform[r][i - 1] == '.') {
        i--;
    }
    platform[r][i] = 'O';
}


void tilt_west(vector<vector<char>>& platform) {
    for (int c = 0; c < platform[0].size(); c++) {
        for (int r = 0; r < platform.size(); r++) {
            if (platform[r][c] == 'O') {
                drop_west(platform, r, c);
            }
        }
    }
}


void drop_east(vector<vector<char>>& platform, int r, int c) {
    platform[r][c] = '.';
    int i = c;
    while (i < platform[r].size() - 1 && platform[r][i + 1] == '.') {
        i++;
    }
    platform[r][i] = 'O';
}


void tilt_east(vector<vector<char>>& platform) {
    for (int c = platform[0].size() - 1; c >= 0; c--) {
        for (int r = 0; r < platform.size(); r++) {
            if (platform[r][c] == 'O') {
                drop_east(platform, r, c);
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
        
    unordered_map<int, vector<vector<char>>> cycle_to_grid;
    unordered_map<vector<vector<char>>, int, GridHasher> grid_to_cycle;
    
    cycle_to_grid[0] = platform;
    grid_to_cycle[platform] = 0;
    
    for (long long i = 0; i < 1000000000; i++) {
        tilt_north(platform);
        tilt_west(platform);
        tilt_south(platform);
        tilt_east(platform);
        if (grid_to_cycle.count(platform)) {
            int N = grid_to_cycle[platform];
            int period = i - N + 1;
            vector<vector<char>> final_grid = cycle_to_grid[N + (1000000000 - (long long) N) % period];
            int res = calculate_total_load(final_grid);
            cout << "Result: " << res << endl;
            break;
        }
        cycle_to_grid[i + 1] = platform;
        grid_to_cycle[platform] = i + 1;
    }
    f.close();
}
