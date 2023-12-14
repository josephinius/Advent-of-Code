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


bool finished(vector<Node*>& pos) {
    for (auto node : pos) {
        if (node->name[2] != 'Z') {
            return false;
        }
    }
    return true;
}


int main() {
    ifstream f("input.txt");
    string s;
        
    getline(f, s);
    
    string instructions = s;
    cout << instructions << endl;
    
    getline(f, s);  // empty line
    
    unordered_map<string, Node*> nodes;
    
    while (getline(f, s)) {
        string name = s.substr(0, 3);
        if (nodes.count(name) == 0) {
            nodes[name] = new Node(name);
        }
        cout << name << " = ";
        string left = s.substr(7, 3);
        if (nodes.count(left) == 0) {
            nodes[left] = new Node(left);
        }
        nodes[name]->left = nodes[left];
        cout << "(" << left << ",";
        string right = s.substr(12, 3);
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
    
    // Node* node = nodes["AAA"];
    
    vector<Node*> pos;
    
    for (auto &[name, node] : nodes) {
        if (name[2] == 'A') {
            pos.emplace_back(node);
        }
    }
    
    long long step = 0;
    
    cout << numeric_limits<long long>::max() << endl;
    
    while (!finished(pos)) {
        /*
        for (auto node : pos) {
            cout << node->name << ", ";
        }
         cout << endl;
         */
        char dir = instructions[step % instructions.size()];
        for (auto& node : pos) {
            if (dir == 'L') {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        step++;
    }
    
    cout << "Result: " << step << endl;
    
    f.close();
}
