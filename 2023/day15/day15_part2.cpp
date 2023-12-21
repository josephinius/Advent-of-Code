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
#include <list>

using namespace std;


int HASH(const string& s) {
    int res = 0;
    for (auto c : s) {
        res += c - ' ' + 32;
        res *= 17;
        res %= 256;
    }
    return res;
}


void remove(vector<list<pair<string, int>>>& box, string label) {
    int box_id = HASH(label);
    auto it = box[box_id].begin();
    while (it != box[box_id].end() && it->first != label) {
        it++;
    }
    if (it != box[box_id].end()) {
        box[box_id].erase(it);
    }
}


void add(vector<list<pair<string, int>>>& box, string label, int focal_length) {
    int box_id = HASH(label);
    auto it = box[box_id].begin();
    while (it != box[box_id].end() && it->first != label) {
        it++;
    }
    if (it != box[box_id].end()) {
        it->second = focal_length;
    }
    else {
        box[box_id].push_back({label, focal_length});
    }
}


int main() {
    ifstream f("input.txt");
    string s;
    
    vector<list<pair<string, int>>> box(256);
    
    while (getline(f, s)) {
        int i = 0;
        while (i < s.size()) {
            int j = i;
            while (j < s.size() && s[j] != ',') {
                j++;
            }
            if (s[j - 1] == '-') {
                string label = s.substr(i, j - i - 1);
                // cout << "removing: " << label << endl;
                remove(box, label);
            }
            else {
                string label = s.substr(i, j - i - 2);
                int fl = stoi(s.substr(j - 1)); // focal length
                // cout << "adding: " << label << ", with: " << fl << endl;
                add(box, label, fl);
            }
            i = j + 1;
        }
    }
    f.close();
    
    int res = 0;
    
    int i = 0;
    for (auto b : box) {
        int j = 0;
        for (auto it = b.begin(); it != b.end(); it++) {
            res += (i + 1) * (j + 1) * it->second;
            j++;
        }
        i++;
    }
    
    cout << "Result: " << res << endl;
    
}

