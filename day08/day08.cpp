#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <utility>

using namespace std;


void check_one_line(const pair<int, int> start_point, const pair<int, int> end_point, const pair<int, int> step, vector<vector<int>> &heights, int &count_visible, vector<vector<int>> &score) {
    auto [r, c] = start_point;  // c++17
    auto [r_end, c_end] = end_point;  // c++17
    auto [dr, dc] = step;  // c++17
    int curr_max = -1;
    stack<pair<int, int>> st;  // {heigh, count} pairs, keeping item with smallest height on top
    int rs = (dr >= 0) ? 1 : -1;  // used for fixing the direction of inequality in while loop
    int cs = (dc >= 0) ? 1 : -1;
    while ((rs * (r + dr) <= rs * r_end) && (cs * (c + dc) <= cs * c_end)) {
        if (abs(heights[r][c]) > curr_max) {
            curr_max = max(abs(heights[r][c]), curr_max);
            if (0 < heights[r][c]) {
                heights[r][c] *= -1;
                count_visible++;
            }
        }
        if (st.empty()) {
            score[r][c] = 0;
            st.emplace(abs(heights[r][c]), 1);
        }
        else {
            int p = 0;
            while (!st.empty() && st.top().first < abs(heights[r][c])) {
                p += st.top().second;
                st.pop();
            }
            score[r][c] *= (p + (int)!st.empty());
            st.emplace(abs(heights[r][c]), p + 1);
        }
        r += dr;
        c += dc;
    }
}


int main()
{
    ifstream f("input.txt");
    string s;
    vector<vector<int>> heights;
    while (getline(f, s)) {
        vector<int> row;
        for (auto c : s) {
            row.push_back(c - '0' + 1);  // we add 1 to avoid zero values
        }
        heights.push_back(row);
    }
    f.close();
    
    int m = heights.size();
    int n = heights[0].size();
    
    int count_visible = 0;
    vector<vector<int>> score(m, vector<int>(n, 1));
    for (int r = 0; r < m; r++) {
        check_one_line({r, 0}, {r, n}, {0, 1}, heights, count_visible, score);
        check_one_line({r, n - 1}, {r, -1}, {0, -1}, heights, count_visible, score);
    }
    for (int c = 0; c < n; c++) {
        check_one_line({0, c}, {m, c}, {1, 0}, heights, count_visible, score);
        check_one_line({m - 1, c}, {-1, c}, {-1, 0}, heights, count_visible, score);
    }
    cout << "Part One: " << count_visible << endl;
    int ans = -1;
    for (auto row : score)
        for (auto x : row)
            ans = max(ans, x);
    cout << "Part Two: " << ans << endl;
}
