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

/*
 
 Ordering (from strongest to weakest):
 - 7) five of a kind: (5)
 - 6) four of a kind: (1, 4)
 - 5) full house: (2, 3)
 - 4) three of a kind: (1, 1, 3)
 - 3) two pair: (1, 2, 2)
 - 2) one pair: (1, 1, 1, 2)
 - 1) high card: (1, 1, 1, 1, 1)
 
 A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2
 
 */


int type(const string& a) {
    unordered_map<char, int> counter;
    for (auto c: a) {
        counter[c]++;
    }
    vector<int> counts;
    for (auto &[c, n] : counter) {
        counts.push_back(n);
    }
    sort(begin(counts), end(counts));
    if (counts == vector<int>{5,}) {
        return 7;
    }
    else if (counts == vector<int>{1, 4}) {
        return 6;
    }
    else if (counts == vector<int>{2, 3}) {
        return 5;
    }
    else if (counts == vector<int>{1, 1, 3}) {
        return 4;
    }
    else if (counts == vector<int>{1, 2, 2}) {
        return 3;
    }
    else if (counts == vector<int>{1, 1, 1, 2}) {
        return 2;
    }
    else if (counts == vector<int>{1, 1, 1, 1, 1}) {
        return 1;
    }
    else {
        return -1;
    }
}


const string kLabel = "AKQJT98765432";


int idx_in_label(char c) {
    for (int i = 0; i < kLabel.size(); i++) {
        if (c == kLabel[i]) {
            return i;
        }
    }
    return -1;
}


bool compare(const string& a, const string& b) {
    if (type(a) == type(b)) {
        for (int i = 0; i < 5; i++) {
            if (a[i] != b[i]) {
                return idx_in_label(b[i]) < idx_in_label(a[i]) ;
            }
        }
        return false;
    }
    if (type(a) < type(b)) {
        return true;
    }
    else {
        return false;
    }
}


int main() {
    ifstream f("input.txt");
    string s;
    
    vector<pair<string, int>> cards;
    
    while (getline(f, s)) {
        stringstream ss(s);
        string token;
        ss >> token;
        string hand = token;
        cout << token << ", ";
        ss >> token;
        int n = stoi(token);
        cout << token << endl;
        cards.push_back({hand, n});
    }
    
    sort(begin(cards), end(cards), [](const pair<string, int> x, const pair<string, int> y) {
        return compare(x.first, y.first);
    });
    
    int rank = 1;
    int result = 0;
    
    for (auto card: cards) {
        cout << card.first << endl;
        result += rank * card.second;
        rank += 1;
    }
    
    cout << "Result: " << result << endl;
    
    /*
    cout << type("AAAAA") << endl;
    cout << type("AA8AA") << endl;
    cout << type("23332") << endl;
    cout << type("TTT98") << endl;
    cout << type("23432") << endl;
    cout << type("A23A4") << endl;
    cout << type("23456") << endl;
    */

    f.close();
}
