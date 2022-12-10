#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;


class Node {
public:
    string name;  // for debugging and generalization
    Node* parent;
    vector<Node*> kids;
    vector<int> sizes_of_files;
    Node(string name) : name(name) {}
};


int get_int_len(const string &s, int start = 0) {
    while (start < s.size() && isdigit(s[start])) {
        start++;
    }
    return start;
}


int dfs(Node* root, vector<int> &dir_sizes) {
    if (root == nullptr) {
        return 0;
    }
    int size = 0;
    for (auto x : root->sizes_of_files) {
        size += x;
    }
    for (auto child : root->kids) {
        size += dfs(child, dir_sizes);
    }
    dir_sizes.push_back(size);
    return size;
}


int main()
{
    Node* prehead = new Node("");
    Node* curr = prehead;
    
    ifstream f("input.txt");
    string s;
    
    while (getline(f, s)) {  // assuming valid input...
        if (s[0] == '$') {
            if (s[2] == 'c') {  // "cd"
                if (s[5] == '.') { // ".."
                    curr = curr->parent;
                }
                else {
                    Node* node = new Node(s.substr(5));
                    curr->kids.push_back(node);
                    node->parent = curr;
                    curr = node;
                }
            }
            else if (s[2] == 'l') {}  // "ls"
        }
        else {
            if (isdigit(s[0])) {
                curr->sizes_of_files.push_back(stoi(s.substr(0, get_int_len(s))));
            }
        }
    }
    
    f.close();

    vector<int> dir_sizes;
    dfs(prehead->kids.front(), dir_sizes);
    
    int acc = 0;
    for (auto x : dir_sizes) {
        if (x <= 100000) {  // 100000 is threshold from problem statement (Part One)
            acc += x;
        }
    }

    cout << "Part One: " << acc << endl;
            
    int free = 70000000 - *max_element(begin(dir_sizes), end(dir_sizes));  // 70000000 is total disk space (Part Two)
    int needed = 30000000 - free;  // 30000000 is required unused space (Part Two)
    int to_del = numeric_limits<int>::max();
    for (auto x : dir_sizes) {
        if (needed <= x) {
            to_del = min(to_del, x);
        }
    }
    
    cout << "Part Two: " << to_del << endl;
}
