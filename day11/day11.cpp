#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;


enum OP {MULTIPLY, ADD, SQUARE};


class Monkey {
public:
    static string part; // "One" or "Two"
    static long long Q; // used in modulo in Part Two
    vector<long long> items; // stores worry levels
    OP op;
    long long o; // operand in method inspect
    long long test_val; // testing value used in throw_to
    int test_true;
    int test_false;
    long long inspect(long long old) {
        long long rv = o;
        switch(op)
        {
            case MULTIPLY:
                rv *= old; break;
            case ADD:
                rv += old; break;
            case SQUARE:
                rv = old * old; break;
        }
        if (part == "One") {
            return rv / 3;
        }
        else if (part == "Two") {
            return rv % Q;
        }
        return rv;
    }
    
    int throw_to(long long worry) {
        if (worry % test_val == 0) {
            return test_true;
        }
        return test_false;
    }
    
    Monkey(OP op, long long o, long long test_val, int test_true, int test_false) :
    op(op), o(o), test_val(test_val), test_true(test_true), test_false(test_false) {
        Q *= test_val;
    }
    
};


long long Monkey::Q = 1;
string Monkey::part = "";


int main()
{
    Monkey::part = "One";  // Select "One" or "Two"
    
    ifstream input_file("input.txt");
    vector<Monkey> monkeys;
    string line;
    while (getline(input_file, line)) {
        vector<long long> starting_items;
        OP op;
        long long o = 0;
        long long test_val;
        int test_true;
        int test_false;

        stringstream ss(line);
        string token;
        
        ss >> token; // read "Monkey"
        ss >> token; // read monkey number

        getline(input_file, line);
        ss = stringstream(line);
        ss >> token; // read "Starting:"
        ss >> token; // read "items:"
        while (ss >> token) {
            starting_items.push_back(stoi(token));
        }
        
        getline(input_file, line);
        ss = stringstream(line);
        ss >> token; // "Operation:"
        ss >> token; // "new"
        ss >> token; // "="
        ss >> token; // "old"
        ss >> token; // "*" or "+"
        op = token == "*" ? MULTIPLY : ADD;
        ss >> token; // a number or "old"
        if (token == "old") {
            op = SQUARE;
        }
        else {
            o = stoi(token);
        }

        getline(input_file, line);
        ss = stringstream(line);
        ss >> token; // "Test:"
        ss >> token; // "divisible"
        ss >> token; // "by"
        ss >> token; // a number
        test_val = stoi(token);

        getline(input_file, line);
        ss = stringstream(line);
        ss >> token; // "If"
        ss >> token; // "true:"
        ss >> token; // "throw"
        ss >> token; // "to"
        ss >> token; // "monkey"
        ss >> token; // monkey number
        test_true = stoi(token);

        getline(input_file, line);
        ss = stringstream(line);
        ss >> token; // "If"
        ss >> token; // "false:"
        ss >> token; // "throw"
        ss >> token; // "to"
        ss >> token; // "monkey"
        ss >> token; // monkey number
        test_false = stoi(token);
                
        monkeys.emplace_back(op, o, test_val, test_true, test_false);
        monkeys.back().items = starting_items;
        
        getline(input_file, line);  // reads empty line
    }
    input_file.close();
    
    vector<long long> ops_count(monkeys.size(), 0);
         
    int num_of_rounds = Monkey::part == "One" ? 20 : 10000;
    for (int i = 0; i < num_of_rounds; i++) {
        int j = 0;
        for (auto &m : monkeys) {
            for (auto item : m.items) {
                long long x = m.inspect(item);
                int to = m.throw_to(x);
                monkeys[to].items.push_back(x);
                ops_count[j]++;
            }
            m.items.clear();
            j++;
        }
    }
    
    sort(ops_count.begin(), ops_count.end());
    cout << "Answer: " << ops_count[ops_count.size() - 1] * ops_count[ops_count.size() - 2] << endl;
}
