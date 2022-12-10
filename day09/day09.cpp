#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>

using namespace std;


struct PairHasher {
    int operator() (const pair<int, int> &p) const {
        return 1009 * p.first + p.second;
    }
};


int get_int_len(const string &s, int start = 0) {
    while (start < s.size() && isdigit(s[start])) {
        start++;
    }
    return start;
}


int main()
{
    const unordered_map<char, pair<int, int>> dir = {{'R', {0, 1}}, {'L', {0, -1}}, {'U', {1, 0}}, {'D', {-1, 0}}};
    const int rope_len = 2;  // Part 1 : rope_len = 2, Part 2: rope_len = 10
        
    vector<pair<int, int>> rope(rope_len, {0, 0});
    
    unordered_set<pair<int, int>, PairHasher> visited;
    visited.emplace(rope.back());
    
    ifstream f("input.txt");
    string s;
    while (getline(f, s)) {
        const auto d = dir.at(s[0]);
        int steps = stoi(s.substr(2, get_int_len(s, 2)));
        for (int j = 0; j < steps; j++){
            auto &head = rope.front();
            head.first += d.first;
            head.second += d.second;
            for (int i = 1; i < rope.size(); i++) {
                auto &curr = rope[i];
                const auto &prev = rope[i - 1];
                int dr = prev.first - curr.first;
                int dc = prev.second - curr.second;
                // int step_r = dr / 2 + abs(dc / 2) * dr;  // works for Part 1, but not for Part 2
                // int step_c = dc / 2 + abs(dr / 2) * dc;  // works for Part 1, but not for Part 2
                int step_r = dr / 2 + abs(dc / 2) * (dr % 2);
                int step_c = dc / 2 + abs(dr / 2) * (dc % 2);
                curr.first += step_r;
                curr.second += step_c;
                if (step_r == 0 && step_c == 0)
                    break;
            }
            visited.emplace(rope.back());
        }
    }
    f.close();

    if (rope_len == 2) {
        cout << "Part One: " << visited.size() << endl;
    }
    else if (rope_len == 10) {
        cout << "Part Two: " << visited.size() << endl;
    }
}
