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
    string s;
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
            cout << n << ", ";
            i = j;
            while (!isdigit(s[i]) && s[i] != '|') {
                i++;
            }
        }
        cout << endl;
        i++;
        while (s[i] == ' ') {
            i++;
        }
        int score = 0;
        while (i < s.size()) {
            int j = get_int_len(s, i);
            int n = stoi(s.substr(i, j - i));
            
            if (wins.count(n)) {
                if (score == 0) {
                    score = 1;
                }
                else {
                    score *= 2;
                }
            }
            i = j;
            while (i < s.size() && !isdigit(s[i])) {
                i++;
            }
        }
        result += score;
    }

    cout << "**** Result: " << result << endl;
    f.close();
}
