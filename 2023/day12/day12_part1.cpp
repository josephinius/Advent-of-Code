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


vector<string> generate_arrangements(int i, const string& x) {
    if (i == x.size()) {
        return {""};
    }
    if (x[i] == '.') {
        vector<string> res;
        for (auto a : generate_arrangements(i + 1, x)) {
            res.push_back("." + a);
        }
        return res;
    }
    else if (x[i] == '#') {
        vector<string> res;
        for (auto a : generate_arrangements(i + 1, x)) {
            res.push_back("#" + a);
        }
        return res;
    }
    // x[i] == '?'
    vector<string> res;
    vector<string> arr = generate_arrangements(i + 1, x);
    for (auto a : arr) {
        res.push_back("#" + a);
    }
    for (auto a : arr) {
        res.push_back("." + a);
    }
    return res;
}


bool is_correct(const string& s, vector<int> config) {
    vector<int> check;
    int i = 0;  // index in s
    while (i < s.size()) {
        while (i < s.size() && s[i] == '.') {
            i++;
        }
        int j = i;
        while (j < s.size() && s[j] == '#') {
            j++;
        }
        if (j > i) {
            check.push_back(j - i);
        }
        i = j;
    }
    return check == config;
}


int number_of_arrangements(const string& x, vector<int>& config) {
    int res = 0;
    for (auto& s : generate_arrangements(0, x)) {
        if (is_correct(s, config)) {
            res++;
        }
    }
    return res;
}


int main() {
    ifstream f("input.txt");
    string s;
    int res = 0;
    
    while (getline(f, s)) {
        // cout << s << endl;
        int i = 0;
        while (i < s.size() && s[i] != ' ') {
            i++;
        }
        string x = s.substr(0, i);
        i++;
        vector<int> config;
        while (i < s.size()) {
            int j = i;
            while (j < s.size() && s[j] != ',') {
                j++;
            }
            int n = stoi(s.substr(i, j - i));
            config.push_back(n);
            i = j + 1;
        }
        // cout << x << endl;
        // for (auto n : config) {
        //     cout << n << ", ";
        // }
        // cout << endl;
        int num = number_of_arrangements(x, config);
        cout << "num: " << num << endl;
        res += num;
    }
    f.close();
    
    /*
    for (auto x : generate_arrangements(0, "???.###")) {
        cout << x << ", is correct: " << is_correct(x, vector<int>{1, 1, 3}) << endl;
    }
     */
    
    cout << "Result: " << res << endl;
    
}
