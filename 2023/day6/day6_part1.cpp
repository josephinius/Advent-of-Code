#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_set>
#include <limits>
#include <algorithm>

using namespace std;


int get_int_end(const string& s, int i) {
    while (i < s.size() && isdigit(s[i])) {
        i++;
    }
    return i;
}


int main() {
    ifstream f("input.txt");
    string s;
    getline(f, s);
    cout << s << endl;
    
    vector<int> time;
    int i = 0;
    while (i < s.size()) {
        while (i < s.size() && !isdigit(s[i])) {
            i++;
        }
        int j = get_int_end(s, i);
        time.push_back(stoi(s.substr(i, j - i)));
        i = j;
    }
    
    for (auto x : time) {
        cout << x << endl;
    }
    
    getline(f, s);
    cout << s << endl;
    
    vector<int> distance;
    i = 0;
    while (i < s.size()) {
        while (i < s.size() && !isdigit(s[i])) {
            i++;
        }
        int j = get_int_end(s, i);
        distance.push_back(stoi(s.substr(i, j - i)));
        i = j;
    }
    
    for (auto x : distance) {
        cout << x << endl;
    }
    
    int result = 1;
    
    for (int i = 0; i < time.size(); i++) {
        int t = time[i];
        int d = distance[i];
        int count = 0;
        for (int hold = 0; hold <= t; hold++) {
            int speed = hold;
            int time_remaining = t - hold;
            int travel = speed * time_remaining;
            if (travel > d) {
                count++;
            }
        }
        cout << "count: " << count << endl;
        result *= count;
    }
    
    cout << "Result: " << result << endl;
    
    f.close();
}
