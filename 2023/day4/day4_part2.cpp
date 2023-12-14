#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_set>

using namespace std;


int get_int_len(const string &s, int j) {
    while (j < s.size() && isdigit(s[j])) {
        j++;
    }
    return j;
}


int main()
{
    int result = 0;
    ifstream f("input.txt");
    
    int num_of_lines = 0;
    
    string s;
    while (getline(f, s)) {
        num_of_lines++;
    }
    
    // cout << "num_of_lines: " << num_of_lines << endl;
    
    vector<int> counts(num_of_lines, 1);
    
    for (auto x : counts) {
        // cout << x << endl;
    }
    
    f.clear();
    f.seekg(0);
    
    int line = 0;
    
    vector<string> arr;
    while (getline(f, s)) {
        int i = 0;
        while (s[i] != ':') {
            i++;
        }
        i++;
        while (s[i] == ' ') {
            i++;
        }
        unordered_set<int> wins;
        while (s[i] != '|') {
            int j = get_int_len(s, i);
            int n = stoi(s.substr(i, j - i));
            wins.insert(n);
            // cout << n << ", ";
            i = j;
            while (!isdigit(s[i]) && s[i] != '|') {
                i++;
            }
        }
        // cout << endl;
        i++;
        while (s[i] == ' ') {
            i++;
        }
        int score = 0;
        while (i < s.size()) {
            int j = get_int_len(s, i);
            int n = stoi(s.substr(i, j - i));
            if (wins.count(n)) {
                score += 1;
            }
            i = j;
            while (i < s.size() && !isdigit(s[i])) {
                i++;
            }
        }
        // cout << "score: " << score << endl;
        result += counts[line];
        for (int x = 0; x < score; x++) {
            counts[line + 1 + x] += counts[line];
        }
        line++;
    }
    
    for (auto x : counts) {
        // cout << x << endl;
    }

    cout << "**** Result: " << result << endl;
    f.close();
}
