#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <sstream>

using namespace std;


struct Node {
    string name;
    Node* left;
    Node* right;
    Node(string& name) : name(name) {
        left = nullptr;
        right = nullptr;
    };
};


int main() {
    ifstream f("input.txt");
    string s;
        
    getline(f, s);
    
    string instructions = s;
    cout << instructions << endl;
    
    getline(f, s);  // empty line
    
    unordered_map<string, Node*> nodes;
    
    while (getline(f, s)) {
        int i = 0;
        int j = i;
        while (s[j] != ' ') {
            j++;
        }
        string name = s.substr(i, j - i);
        if (nodes.count(name) == 0) {
            nodes[name] = new Node(name);
        }
        cout << name << " = ";
        i = j;
        while (!isalpha(s[i])) {
            i++;
        }
        j = i;
        while (s[j] != ',') {
            j++;
        }
        string left = s.substr(i, j - i);
        if (nodes.count(left) == 0) {
            nodes[left] = new Node(left);
        }
        nodes[name]->left = nodes[left];
        cout << "(" << left << ",";
        i = j;
        while (!isalpha(s[i])) {
            i++;
        }
        while (s[j] != ')') {
            j++;
        }
        string right = s.substr(i, j - i);
        if (nodes.count(right) == 0) {
            nodes[right] = new Node(right);
        }
        nodes[name]->right = nodes[right];
        cout << right << ")" << endl;
    }
    
    /*
    for (auto &[name, node] : nodes) {
        cout << " " << node->name << " : " << node->left->name << ", " << node->right->name << endl;
    }
     */
    
    Node* node = nodes["AAA"];
    
    int step = 0;
    
    while (node->name != "ZZZ") {
        cout << "node->name: " << node->name << endl;
        char dir = instructions[step % instructions.size()];
        if (dir == 'L') {
            node = node->left;
        }
        else {
            node = node->right;
        }
        step++;
    }
    
    cout << "Result: " << step << endl;
    
    f.close();
}
