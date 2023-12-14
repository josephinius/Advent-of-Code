#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_set>
#include <limits>
#include <algorithm>

using namespace std;

struct Map {
    vector<vector<long long>> ranges;  // {destination, source, range}
    long long map(long long source) {
        for (auto& vec : ranges) {
            if (vec[1] <= source && source <= vec[1] + vec[2] - 1) {
                return vec[0] + (source - vec[1]);
            }
        }
        return source;
    }
};


long long get_long_long(const string &s, int& i) {
    long long res = 0;
    while (i < s.size() && isdigit(s[i])) {
        res = res * 10 + (s[i] - '0');
        i++;
    }
    return res;
}


vector<vector<long long>> map_interval(long long start, long long end, Map& m) {
    vector<vector<long long>> intervals;
    for (auto vec: m.ranges) {
        intervals.push_back({vec[1], vec[1] + vec[2] - 1});
    }
    vector<vector<long long>> empty;
    long long last_point = numeric_limits<long long>::min();
    for (auto interval: intervals) {
        if (interval[0] - 1 >= last_point) {
            empty.push_back({last_point, interval[0] - 1});
        }
        last_point = interval[1] + 1;
    }
    empty.push_back({last_point, numeric_limits<long long>::max()});
    
    vector<vector<long long>> result;
    
    for (auto interval: intervals) {
        if (interval[1] >= start && interval[0] <= end) {
            long long left = max(start, interval[0]);
            long long right = min(end, interval[1]);
            result.push_back({m.map(left), m.map(right)});
        }
    }
    
    for (auto interval: empty) {
        if (interval[1] >= start && interval[0] <= end) {
            // cout << "overlap with empty" << endl;
            long long left = max(start, interval[0]);
            long long right = min(end, interval[1]);
            // cout << "left: " << left << ", right: " << right << endl;
            result.push_back({left, right});
        }
    }
    
    return result;
}


int main() {
    // cout << numeric_limits<int>::max() << endl;
    ifstream f("input.txt");
    string s;
    getline(f, s);
    cout << s << endl;
    int i = 7;
    vector<long long> seeds;
    while (i < s.size()) {
        long long n = get_long_long(s, i);
        seeds.emplace_back(n);
        i++;
    }
    for (auto x: seeds)
        cout << x << endl;
    cout << endl;
    
    getline(f, s);  // empty line
    getline(f, s);  // seed-to-soil map:

    getline(f, s);  // first line with ranges
    
    vector<Map> maps;
    
    for (int q = 0; q < 7; q++) {
        Map m;
        while (s.size() != 0) {
            vector<long long> range;
            int j = 0;
            for (int i = 0; i < 3; i++) {
                long long n = get_long_long(s, j);
                range.push_back(n);
                j++;
            }
            m.ranges.push_back(range);
            getline(f, s);
        }
        
        sort(begin(m.ranges), end(m.ranges), [](const vector<long long>& a, const vector<long long>& b) {
            return a[1] < b[1];
        });
        
        for (auto range : m.ranges) {
            for (auto x : range) {
                cout << x << ", ";
            }
            cout << endl;
        }

        maps.emplace_back(m);
        cout << endl;
        getline(f, s);
        getline(f, s);
    }
    f.close();

    long long result = numeric_limits<long long>::max();
    
    vector<vector<long long>> intervals;
    
    for (int i = 0; i < seeds.size(); i += 2) {
        intervals.push_back({seeds[i], seeds[i] + seeds[i + 1] - 1});
    }
    
    for (auto m : maps) {
        vector<vector<long long>> intervals_new;
        for (auto interval : intervals) {
            for (auto x: map_interval(interval[0], interval[1], m)) {
                intervals_new.push_back(x);
            }
        }
        intervals = intervals_new;
    }
    
    for (auto x : intervals) {
        cout << "x[0]: " << x[0] << endl;
        result = min(result, x[0]);
    }
    
    cout << "Result: " << result << endl;
    
    /*
     
    vector<vector<long long>> res = map_interval(45, 55, maps[0]);
    
    for (auto vec : res) {
        for (auto x : vec) {
            cout << " " << x << ",";
        }
        cout << endl;
    }
    
     */
     
}
