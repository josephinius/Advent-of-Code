#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;


int main()
{
    int sum = 0;
    ifstream f("input.txt");
    string s;
    while (getline(f, s)) {
        cout << s << endl;
        int first;
        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                cout << s[i] << endl;
                first = s[i] - '0';
                break;
            }
        }
        int last;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (isdigit(s[i])) {
                cout << s[i] << endl;
                last = s[i] - '0';
                break;
            }
        }
        int num = 10 * first + last;
        cout << "num: " << num << endl;
        sum += num;
    }
    cout << sum << endl;
    f.close();
}
