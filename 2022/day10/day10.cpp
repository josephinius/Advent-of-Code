#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int get_int_len(const string &s, int start = 0);
int increment_signal(int curr_cycle, int x);
void draw_pixel(string &screen, int cycle, int x);


int main()
{
    int curr_cycle = 1;
    int x = 1;
    int signal = 0;
    string screen;
    
    ifstream f("input.txt");
    string s;
    while (getline(f, s)) {
        if (s[0] == 'n') {  // noop (one cycle)
            draw_pixel(screen, curr_cycle, x);
            signal += increment_signal(curr_cycle++, x);
        }
        else if (s[0] == 'a') {  // addx (two cycles)
            draw_pixel(screen, curr_cycle, x);
            signal += increment_signal(curr_cycle++, x);
            draw_pixel(screen, curr_cycle, x);
            signal += increment_signal(curr_cycle++, x);
            x += stoi(s.substr(5, get_int_len(s, 5)));
        }
    }
    f.close();
    
    cout << "Part One: " << signal << endl;

    cout << "Part Two (screen rendering):" << endl;
    int i = 0;
    for (auto c : screen) {
        cout << c;
        i++;
        if (i % 40 == 0)
            cout << endl;
    }
}


int get_int_len(const string &s, int start) {
    while (start < s.size() && isdigit(s[start])) {
        start++;
    }
    return start;
}


int increment_signal(int curr_cycle, int x) {
    if (curr_cycle >= 20) {
        if ((curr_cycle - 20) % 40 == 0) {
            return curr_cycle * x;
        }
    }
    return 0;
}


void draw_pixel(string &screen, int cycle, int x) {
    int pos = ((cycle - 1) % 40);
    if (x - 1 <= pos && pos <= x + 1) {
        screen.push_back('#');
    }
    else {
        screen.push_back('.');
    }
}
