#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;


int get_int_and_flag(int r, int c, const vector<string>& arr, bool& flag) {
    int rows = arr.size(), cols = arr[r].size();
    flag = false;
    while (c < cols && isdigit(arr[r][c])) {
        if (c > 0 && r > 0 && !isdigit(arr[r - 1][c - 1]) && arr[r - 1][c - 1] != '.') {
            cout << "1) setting flag to true..." << endl;
            flag = true;
        }
        if (r > 0 && !isdigit(arr[r - 1][c]) && arr[r - 1][c] != '.') {
            cout << "2) setting flag to true..." << endl;
            cout << "r: " << r << ", c: " << c << endl;
            cout << "arr[r - 1][c]: " << arr[r - 1][c] << endl;
            flag = true;
        }
        if (r > 0 && c + 1 < cols && !isdigit(arr[r - 1][c + 1]) && arr[r - 1][c + 1] != '.') {
            cout << "3) setting flag to true..." << endl;
            flag = true;
        }
        if (c + 1 < cols && !isdigit(arr[r][c + 1]) && arr[r][c + 1] != '.') {
            cout << "4) setting flag to true..." << endl;
            flag = true;
        }
        if (c + 1 < cols && r + 1 < rows && !isdigit(arr[r + 1][c + 1]) && arr[r + 1][c + 1] != '.') {
            cout << "5) setting flag to true..." << endl;
            flag = true;
        }
        if (r + 1 < rows && !isdigit(arr[r + 1][c]) && arr[r + 1][c] != '.') {
            cout << "6) setting flag to true..." << endl;
            flag = true;
        }
        if (r + 1 < rows && c > 0 && !isdigit(arr[r + 1][c - 1]) && arr[r + 1][c - 1] != '.') {
            cout << "7) setting flag to true..." << endl;
            flag = true;
        }
        if (c > 0 && !isdigit(arr[r][c - 1]) && arr[r][c - 1] != '.') {
            cout << "8) setting flag to true..." << endl;
            flag = true;
        }
        c++;
    }
    return c;
}


int main()
{
    ifstream f("input.txt");
    string s;
    vector<string> arr;
    while (getline(f, s)) {
        arr.push_back("");
        cout << s << endl;
        for (auto c : s) {
            arr.back().push_back(c);
        }
    }
    
    cout << endl;
    
    for (auto row : arr) {
        for (auto c: row) {
            cout << c;
        }
        cout << endl;
    }
    
    int r = 0;
    
    int result = 0;

    while (r < arr.size()) {
        int c = 0;
        while (c < arr[r].size()) {
            while (!isdigit(arr[r][c])) {
                c++;
            }
            if (c < arr[r].size()) {
                bool flag = false;
                int c_new = get_int_and_flag(r, c, arr, flag);
                int n = stoi(arr[r].substr(c, c_new - c));
                cout << "n: " << n << endl;
                if (flag) {
                    cout << "adding..." << endl;
                    result += n;
                }
                else {
                    cout << "not adding..." << endl;
                }
                c = c_new;
            }
        }
        r++;
    }
    
    cout << "**** Result: " << result << endl;
    f.close();
}
