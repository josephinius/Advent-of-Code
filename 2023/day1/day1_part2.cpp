#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;


int main()
{
    long long sum = 0;
    ifstream f("input.txt");
    string s;
    while (getline(f, s)) {
        cout << s << endl;
        string r;
        int i = 0;
        while (i < s.size()) {
            if (isdigit(s[i])) {
                r += s[i];
                i++;
            }
            else if (s.substr(i, 3) == "one") {
                r += '1';
                i += 1;
            }
            else if (s.substr(i, 3) == "two") {
                r += '2';
                i += 1;
            }
            else if (s.substr(i, 5) == "three") {
                r += '3';
                i += 1;
            }
            else if (s.substr(i, 4) == "four") {
                r += '4';
                i += 1;
            }
            else if (s.substr(i, 4) == "five") {
                r += '5';
                i += 1;
            }
            else if (s.substr(i, 3) == "six") {
                r += '6';
                i += 1;
            }
            else if (s.substr(i, 5) == "seven") {
                r += '7';
                i += 1;
            }
            else if (s.substr(i, 5) == "eight") {
                r += '8';
                i += 1;
            }
            else if (s.substr(i, 4) == "nine") {
                r += '9';
                i += 1;
            }
            else {
                i++;
            }
        }
                
        int first;
        for (int i = 0; i < r.size(); i++) {
            if (isdigit(r[i])) {
                cout << r[i] << endl;
                first = r[i] - '0';
                break;
            }
        }
        int last;
        for (int i = r.size() - 1; i >= 0; i--) {
            if (isdigit(r[i])) {
                cout << r[i] << endl;
                last = r[i] - '0';
                break;
            }
        }
        int num = 10 * first + last;
        // cout << "num: " << num << endl;
        sum += num;
    }
    cout << sum << endl;
    f.close();
}
