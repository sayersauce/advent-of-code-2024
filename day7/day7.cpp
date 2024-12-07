#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>

using namespace std;

void cartesianProduct(const vector<char>& set, int size, vector<char>& current, vector<vector<char>>& result) {
    if (current.size() == size) {
        result.push_back(current);
        return;
    }

    for (char c : set) {
        current.push_back(c);
        cartesianProduct(set, size, current, result);
        current.pop_back();
    }
}

int main() {
    ifstream file("input.txt");
    string line;
    map<long long, vector<int>> equations;
    set<int> equationLengths;

    while (getline(file, line)) {
        istringstream ss(line);
        string s;
        bool first = true;
        long long total;
        vector<int> numbers;

        while (ss >> s) {
            if (first) {
                total = stoll(s.substr(0, s.size() - 1));
                first = false;
            } else {
                numbers.push_back(stoll(s));
            }
        }
    
        equations[total] = numbers;
        equationLengths.insert(numbers.size());
    }

    // debug
    for (auto [key, vals] : equations) {
        cout << key << ": ";

        for (int val : vals) {
            cout << val << ", ";
        }

        cout << endl;
    }

    map<int, vector<vector<char>>> operatorCombinations;

    for (int length : equationLengths) {
        cout << "equation len " << length << endl; // debug
        vector<char> ops = {'*', '+'};

        vector<vector<char>> combinations;
        vector<char> current;

        cartesianProduct(ops, length - 1, current, combinations);

        operatorCombinations[length] = combinations;
    }


// debug
    // for (auto [key, vals] : operatorCombinations) {
    //     cout << key << endl;

    //     for (vector<char> v : vals) {
    //         for (char c : v) {
    //             cout << c << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    long long part1 = 0;
 
    for (auto [target, numbers] : equations) {
        // cout << endl << "processing equation " << target << endl;

        vector<vector<char>> combinations = operatorCombinations[numbers.size()];

        for (vector<char> combination : combinations) {
            long long total = numbers[0];
            int i = 1;

            while (i < numbers.size()) {
                char op = combination[i - 1];
                if (total > target) {
                    break;
                }

                if (op == '+') {
                    total += numbers[i];
                } else if (op == '*') {
                    total *= numbers[i];
                }
                
                i++;
            }

            if (total == target) {
                // cout << target << " this equation works" << endl;
                part1 += target;
                break;
            }
        }
    }

    cout << part1 << endl;
    
}