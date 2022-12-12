#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>
#include <unordered_map>
#include <cctype>


using namespace std;

typedef pair<int, int> pii;


const vector<int> dirs = {0, 1, 0, -1, 0};


struct PairHasher {
    int operator() (const pii &p) const {
        return 1009 * p.first + p.second;
    }
};


bool is_active(const int &M, const int &N, const vector<vector<char>> &hmap, const unordered_map<pii, int, PairHasher> &visited, const int h, const int i, const int j) {
    return 0 <= i && i < M && 0 <= j && j <= N && visited.find({i, j}) == visited.end() && hmap[i][j] >= h - 1;
}


vector<pii> active_neighbors(const vector<vector<char>> &hmap, const unordered_map<pii, int, PairHasher> &visited, pii pos) {
    const int M = hmap.size();
    const int N = hmap[0].size();
    auto [i, j] = pos;
    vector<pii> neighbors;
    const auto &h = hmap[i][j];
    for (int a = 0; a < 4; a++) {
        int ni = i + dirs[a];
        int nj = j + dirs[a + 1];
        if (is_active(M, N, hmap, visited, h, ni, nj)) {
            neighbors.emplace_back(ni, nj);
        }
    }
    return neighbors;
}


void bfs(const vector<vector<char>> &hmap, pii start, unordered_map<pii, int, PairHasher> &dist) {
    const int M = hmap.size();
    const int N = hmap[0].size();
    vector<pii> frontier;
    frontier.push_back(start);
    vector<pii> next;
    dist[start] = 0;
    while (!frontier.empty()) {
        next.clear();
        for (auto [i, j] : frontier) {
            for (auto [ni, nj] : active_neighbors(hmap, dist, {i, j})) {
                next.emplace_back(ni, nj);
                dist[{ni, nj}] = dist[{i, j}] + 1;
            }
        }
        swap(frontier, next);
    }
}


int main()
{
    vector<vector<char>> hmap;

    ifstream f("input.txt");
    string s;
    while (getline(f, s)) {
        vector<char> curr_line;
        for (auto c : s) {
            curr_line.push_back(c);
        }
        hmap.push_back(curr_line);
    }
    f.close();

    pii S;  // coordinates of starting point in Part One
    pii start;  // We will start from the end :-)
    
    const int M = hmap.size();
    const int N = hmap[0].size();
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (hmap[i][j] == 'S') {
                S.first = i;
                S.second = j;
                hmap[i][j] = 'a';
            }
            if (hmap[i][j] == 'E') {
                start.first = i;
                start.second = j;
                hmap[i][j] = 'z';
            }
        }
    }

    unordered_map<pii, int, PairHasher> dist;
    bfs(hmap, start, dist);
    
    int steps_from_S = -1;
    int min_steps = numeric_limits<int>::max();
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (hmap[i][j] == 'a' && dist.find({i, j}) != dist.end()) {
                int d = dist[{i, j}];
                min_steps = min(min_steps, d);
                if (make_pair(i, j) == S) {
                    steps_from_S = d;
                }
            }
        }
    }
    
    cout << "Part One: " << steps_from_S << endl;
    cout << "Part Two: " << min_steps << endl;
}
