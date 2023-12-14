#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;


/*
 
 Rock: A, X
 Paper: B, Y
 Scissors: C, Z
 
 Rock > Scissors
 Scissors > Paper
 Paper > Rock
 
 Rock: 1
 Paper: 2
 Scissors: 3
 
 Lost: 0
 Draw: 3
 Won: 6
 
 Part 1:
 
 A X 3
 A Y 6
 A Z 0
 
 B X 0
 B Y 3
 B Z 6
 
 C X 6
 C Y 0
 C Z 3
 
 Part 2:
 
 X - lose
 Y - draw
 Z - win
 
 A X : 0 + 3
 A Y : 3 + 1
 A Z : 6 + 2
 
 B X : 0 + 1
 B Y : 3 + 2
 B Z : 6 + 3
 
 C X : 0 + 2
 C Y : 3 + 3
 C Z : 6 + 1
 
 */


int main()
{
    const vector<int> tb1 = {1, 2, 3};
    const vector<vector<int>> tb2 = {{3, 6, 0}, {0, 3, 6}, {6, 0, 3}};
    int total = 0;
    ifstream f("input.txt");
    string s;
    while (getline(f, s)) {
        char a = s[0];
        char x = s[2];
        total += tb1[x - 'X'] + tb2[a - 'A'][x - 'X'];
    }
    f.close();
    cout << "Part One: " << total << endl;
    const vector<vector<int>> tb3 = {{3, 4, 8}, {1, 5, 9}, {2, 6, 7}};
    total = 0;
    ifstream ff("input.txt");
    while (getline(ff, s)) {
        char a = s[0];
        char x = s[2];
        total += tb3[a - 'A'][x - 'X'];
    }
    ff.close();
    cout << "Part Two: " << total << endl;
}
