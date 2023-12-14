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
    
    long long T = 0;
    long long p = 1;
    
    for (int i = time.size() - 1; i >= 0; i--) {
        int t = time[i];
        while (t > 0) {
            int last_digit = t % 10;
            T += p * last_digit;
            p *= 10;
            t /= 10;
        }
    }
    
    cout << "T: " << T << endl;
    
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
    
    long long D = 0;
    p = 1;
    
    for (int i = distance.size() - 1; i >= 0; i--) {
        int d = distance[i];
        while (d > 0) {
            int last_digit = d % 10;
            D += p * last_digit;
            p *= 10;
            d /= 10;
        }
    }
    
    cout << "D: " << D << endl;
    
    int result = 0;
    
    for (long long hold = 0; hold <= T; hold++) {
        long long speed = hold;
        long long time_remaining = T - hold;
        long long travel = speed * time_remaining;
        if (travel > D) {
            result++;
        }
    }
    
    cout << "Result: " << result << endl;
    
    f.close();
}
