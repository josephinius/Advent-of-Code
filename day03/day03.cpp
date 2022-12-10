#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>


using namespace std;


int main()
{
    int ans1 = 0;
    ifstream f("input.txt");
    string s;
    while (getline(f, s)) {
        unordered_map<char, int> counts;
        int n = s.size();
        for (int i = 0; i < n / 2; i++) {
            counts[s[i]]++;
        }
        for (int i = n / 2; i < n; i++) {
            if (counts.find(s[i]) != counts.end()) {
                int x = s[i] - 'a' + 1;
                if (x < 1)
                    x = s[i] - 'A' + 27;
                ans1 += x;
                break;
            }
        }
    }
    // f.close();
    cout << "Part One: " << ans1 << endl;
    
    f.clear();
    f.seekg(0);
    
    int ans2 = 0;
    int line_id = 0;
    
    unordered_map<char, int> counts;

    while (getline(f, s)) {
        if (line_id % 3 == 0) {
            counts.clear();
        }
        int n = s.size();
        if (line_id % 3 == 0) {
            for (int i = 0; i < n; i++) {
                if (counts.find(s[i]) == counts.end())
                    counts[s[i]] = 1;
            }
        }
        else if (line_id % 3 == 1) {
            for (int i = 0; i < n; i++) {
                if (counts.find(s[i]) != counts.end())
                    counts[s[i]] = 2;
            }
        }
        else {
            for (int i = 0; i < n; i++) {
                if (counts.find(s[i]) != counts.end()) {
                    if (counts[s[i]] == 2) {
                        int x = s[i] - 'a' + 1;
                        if (x < 1)
                            x = s[i] - 'A' + 27;
                        ans2 += x;
                        break;
                    }
                }
            }
        }
        line_id++;
    }
    f.close();
    cout << "Part Two: " << ans2 << endl;
}
