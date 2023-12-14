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
    int result = 0;
    while (getline(f, s)) {
        cout << s << endl;
        int i = 5;
        int j = get_int_len(s, i);
        int id = stoi(s.substr(i, j - i));
        cout << "id: " << id << endl;
        i = j + 2;
        int red_max = 0, blue_max = 0, green_max = 0;
        cout << "i: " << i << endl;
        while (i < s.size()) {
            cout << "s[i]: " << s[i] << endl;
            int j = get_int_len(s, i);
            int n = stoi(s.substr(i, j - i));
            i = j + 1;
            if (s[i] == 'r') {  // red
                red_max = max(red_max, n);
                i += 3;
            }
            else if (s[i] == 'g') { // green
                green_max = max(green_max, n);
                i += 5;
            }
            else if (s[i] == 'b') { // blue
                blue_max = max(blue_max, n);
                i += 4;
            }
            i += 2;
        }
        result += blue_max * green_max * red_max;
    }
    cout << "**** Result: " << result << endl;
    f.close();
}

