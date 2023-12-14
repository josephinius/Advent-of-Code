#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <utility>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef pair<int, int> pii;


struct PairHasher {
    int operator() (const pii& p) const {
        return 97 * p.first + p.second;
    }
};


int get_int_and_flag(int r, int c, const vector<string>& arr, unordered_map<pii, vector<int>, PairHasher>& mp) {
    int c_start = c;
    int rows = arr.size(), cols = arr[r].size();
    unordered_set<pii, PairHasher> stars;
    while (c < cols && isdigit(arr[r][c])) {
        if (c > 0 && r > 0 && arr[r - 1][c - 1] == '*') {
            stars.insert({r - 1, c - 1});
        }
        if (r > 0 && arr[r - 1][c] == '*') {
            stars.insert({r - 1, c});
        }
        if (r > 0 && c + 1 < cols && arr[r - 1][c + 1] == '*') {
            stars.insert({r - 1, c + 1});
        }
        if (c + 1 < cols && arr[r][c + 1] == '*') {
            stars.insert({r, c + 1});
        }
        if (c + 1 < cols && r + 1 < rows && arr[r + 1][c + 1] == '*') {
            stars.insert({r + 1, c + 1});
        }
        if (r + 1 < rows && arr[r + 1][c] == '*') {
            stars.insert({r + 1, c});
        }
        if (r + 1 < rows && c > 0 && arr[r + 1][c - 1] == '*') {
            stars.insert({r + 1, c - 1});
        }
        if (c > 0 && arr[r][c - 1] == '*') {
            stars.insert({r, c - 1});
        }
        c++;
    }
    int n = stoi(arr[r].substr(c_start, c - c_start));
    for (auto &[row, col]: stars) {
        mp[{row, col}].push_back(n);
    }
    return c;
}


int main()
{
    ifstream f("input.txt");
    string s;
    vector<string> arr;
    while (getline(f, s)) {
        arr.push_back("");
        // cout << s << endl;
        for (auto c : s) {
            arr.back().push_back(c);
        }
    }
    
    cout << endl;
    
    for (auto row : arr) {
        for (auto c: row) {
            // cout << c;
        }
        // cout << endl;
    }
    
    int r = 0;
    
    unordered_map<pii, vector<int>, PairHasher> mp;
    
    while (r < arr.size()) {
        int c = 0;
        while (c < arr[r].size()) {
            while (c < arr[r].size() && !isdigit(arr[r][c])) {
                c++;
            }
            if (c < arr[r].size()) {
                int c_new = get_int_and_flag(r, c, arr, mp);
                c = c_new;
            }
        }
        r++;
    }
        
    int result = 0;

    for (auto &[p, vec]: mp) {
        if (vec.size() == 2) {
            result += vec[0] * vec[1];
            // cout << "vec0: " << vec[0] << endl;
            // cout << "vec1: " << vec[1] << endl;
        }
    }
    
    cout << "**** Result: " << result << endl;
    f.close();
}
