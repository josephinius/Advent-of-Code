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
        vector<int> v;
        int i = 0;
        while (i < s.size()) {
            int j = i;
            while (j < s.size() && s[j] != '-' && s[j] != ',')
                j++;
            int x = stoi(s.substr(i, j - i));
            v.push_back(x);
            i = ++j;
        }
        if ((v[0] <= v[2] && v[3] <= v[1]) || (v[2] <= v[0] && v[1] <= v[3])) {
            ans1++;
        }
    }
    
    cout << "Part One: " << ans1 << endl;
    
    // f.close();
    
    f.clear();
    f.seekg(0);
    
    int ans2 = 0;
    
    while (getline(f, s)) {
        vector<int> v;
        int i = 0;
        while (i < s.size()) {
            int j = i;
            while (j < s.size() && s[j] != '-' && s[j] != ',')
                j++;
            int x = stoi(s.substr(i, j - i));
            v.push_back(x);
            i = ++j;
        }
        int s1 = v[0];
        int e1 = v[1];
        int s2 = v[2];
        int e2 = v[3];
        if (s1 <= e2 && e1 >= s2) {
            ans2++;
        }
    }
    cout << "Part Two: " << ans2 << endl;
    f.close();
}
