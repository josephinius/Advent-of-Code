#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;


int main()
{
    vector<int> cals;
    int rs = 0;
    ifstream f("input.txt");
    string s;
    while (getline(f, s)) {
        if (s.size() == 0) {
            cals.push_back(rs);
            rs = 0;
        }
        else {
            rs += stoi(s);
        }
    }
    f.close();
    cals.push_back(rs);
    priority_queue<int> q(cals.begin(), cals.end());
    int ans1 = q.top();
    cout << "Part One: " << ans1 << endl;
    int ans2 = 0;
    for (int i = 0; i < 3; i++) {
        ans2 += q.top();
        q.pop();
    }
    cout << "Part Two: " << ans2 << endl;
}
