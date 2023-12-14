#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;


int get_int_len(const string &s, int j) {
    while (j < s.size() && isdigit(s[j])) {
        j++;
    }
    return j;
}


int main()
{
    int sum = 0;
    ifstream f("input.txt");
    string s;
    const int r_max = 12, g_max = 13, b_max = 14;
    int result = 0;
    while (getline(f, s)) {
        cout << s << endl;
        int i = 5;
        int j = get_int_len(s, i);
        int id = stoi(s.substr(i, j - i));
        cout << "id: " << id << endl;
        i = j + 2;
        bool flag = true;
        cout << "i: " << i << endl;
        while (i < s.size()) {
            cout << "s[i]: " << s[i] << endl;
            int j = get_int_len(s, i);
            int n = stoi(s.substr(i, j - i));
            i = j + 1;
            if (s[i] == 'r') {  // red
                if (n > r_max) {
                    flag = false;
                    break;
                }
                i += 3;
            }
            else if (s[i] == 'g') { // green
                if (n > g_max) {
                    flag = false;
                    break;
                }
                i += 5;
            }
            else if (s[i] == 'b') { // blue
                if (n > b_max) {
                    flag = false;
                    break;
                }
                i += 4;
            }
            i += 2;
        }
        if (flag) {
            result += id;
        }
    }
    cout << "**** Result: " << result << endl;
    f.close();
}
