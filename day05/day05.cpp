#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>


using namespace std;


int get_int_len(const string &s, int j) {
    while (j < s.size() && isdigit(s[j])) {
        j++;
    }
    return j;
}


int main()
{
    bool part2 = false;  // Part One: false, Part Two: true
    vector<vector<char>> stacks;
    ifstream f("input.txt");
    string s;
    while (getline(f, s)) {
        if (stacks.size() == 0) {
            for (int i = 1; i < s.size(); i += 4) {
                stacks.push_back({});
            }
        }
        for (int i = 1; i < s.size(); i += 4) {
            if (isalpha(s[i])) {
                stacks[i / 4].push_back(s[i]);
            }
        }
        if (isdigit(s[1])) {
            break;
        }
    }
    for (auto & stack : stacks) {
        reverse(stack.begin(), stack.end());
    }
    getline(f, s);
    while (getline(f, s)) {
        int i = 5;
        int j = get_int_len(s, i);
        int num = stoi(s.substr(i, j - i));
        i = j + 6;
        j = get_int_len(s, i);
        int from = stoi(s.substr(i, j - i));
        i = j + 4;
        j = get_int_len(s, i);
        int to = stoi(s.substr(i, j - i));
        vector<char> buffer;
        for (int i = 0; i < num; i++) {
            char x = stacks[from - 1].back();
            stacks[from - 1].pop_back();
            buffer.push_back(x);
        }
        if (part2) {
            reverse(buffer.begin(), buffer.end());
        }
        for (auto x : buffer) {
            stacks[to - 1].push_back(x);
        }
    }
    f.close();
    string ans;
    for (auto s : stacks) {
        ans += s.back();
    }
    if (part2) {
        cout << "Part Two: " << ans << endl;
    }
    else {
        cout << "Part One: " << ans << endl;
    }
}
