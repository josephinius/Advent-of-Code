#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

int main()
{
    const int num_of_unique = 4;  // Part 1: 4, Part 2: 14
    unordered_map<char, int> counts;
    queue<char> q;
    int ans = -1;
    int pos = 1;
    std::ifstream ifs("input.txt");
    char c;
    while (ifs >> c) {
        if (num_of_unique < pos) {
            unordered_map<char, int>::iterator it = counts.find(q.front());
            it->second--;
            if (it->second == 0) {
                counts.erase(it);
            }
            q.pop();
        }
        q.push(c);
        counts[c]++;
        if (counts.size() == num_of_unique) {
            ans = pos;
            break;
        }
        pos++;
    }
    ifs.close();
    if (num_of_unique == 4) {
        cout << "Part Two: " << ans << endl;
    }
    else if (num_of_unique == 14) {
        cout << "Part One: " << ans << endl;
    }
}
