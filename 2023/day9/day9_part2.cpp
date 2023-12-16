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


int get_int(const string& s, int i) {
    while (i < s.size() && isdigit(s[i])) {
        i++;
    }
    return i;
}


bool all_zeros(const vector<int>& vec) {
    for (auto& x : vec) {
        if (x != 0) {
            return false;
        }
    }
    return true;
}


int main() {
    ifstream f("input.txt");
    string s;
    vector<vector<int>> histories;
    while (getline(f, s)) {
        vector<int> history;
        int i = 0;
        while (i < s.size()) {
            bool is_negative = false;
            if (s[i] == '-') {
                is_negative = true;
                i++;
            }
            int j = get_int(s, i);
            int n = stoi(s.substr(i, j - i));
            if (is_negative) {
                n *= - 1;
            }
            history.push_back(n);
            cout << n << ", ";
            i = j + 1;
        }
        histories.push_back(history);
        cout << endl;
    }
    f.close();
    
    long long result = 0;
    
    for (auto& his: histories) {
        vector<vector<int>> diffs;
        diffs.push_back(his);
        while (!all_zeros(diffs.back())) {
            vector<int> diff;
            for (int i = 1; i < diffs.back().size(); i++) {
                diff.push_back(diffs.back()[i] - diffs.back()[i - 1]);
            }
            diffs.push_back(diff);
        }
                
        int pred = 0;
        for (int i = diffs.size() - 1; i >= 0; i--) {
            pred = diffs[i].front() - pred;
        }
        cout << "pred: " << pred << endl;
        result += pred;
        
    }
    
    cout << "Result: " << result << endl;
}
