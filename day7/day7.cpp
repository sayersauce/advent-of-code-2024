#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <utility>

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

long part1(vector<pair<long, vector<int>>> equations, map<int, vector<vector<char>>> operatorCombinations) {
    long result = 0;

    for (auto [target, numbers] : equations) {
        vector<vector<char>> combinations = operatorCombinations[numbers.size()];

        for (vector<char> combination : combinations) {
            long total = numbers[0];
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
                result += target;
                break;
            }
        }
    }

    return result;
}

long part2(vector<pair<long, vector<int>>> equations, map<int, vector<vector<char>>> operatorCombinations) {
    long result = 0;

    for (auto [target, numbers] : equations) {
        vector<vector<char>> combinations = operatorCombinations[numbers.size()];

        for (vector<char> combination : combinations) {
            long total = numbers[0];
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
                } else if (op == '|') {
                    total = stol(to_string(total) + to_string(numbers[i]));
                }
                
                i++;
            }

            if (total == target) {
                result += target;
                break;
            }
        }
    }

    return result;
}

int main() {
    ifstream file("input.txt");
    string line;
    vector<pair<long, vector<int>>> equations;
    set<int> equationLengths;

    while (getline(file, line)) {
        istringstream ss(line);
        string s;
        bool first = true;
        long total;
        vector<int> numbers;

        while (ss >> s) {
            if (first) {
                total = stol(s.substr(0, s.size() - 1));
                first = false;
            } else {
                numbers.push_back(stol(s));
            }
        }
    
        equations.push_back(make_pair(total, numbers));
        equationLengths.insert(numbers.size());
    }

    vector<char> ops = {'*', '+'};
    vector<char> ops2 = {'*', '+', '|'};
    map<int, vector<vector<char>>> operatorCombinations;
    map<int, vector<vector<char>>> operatorCombinations2;

    for (int length : equationLengths) {
        vector<vector<char>> combinations, combinations2;
        vector<char> current, current2;

        cartesianProduct(ops, length - 1, current, combinations);
        cartesianProduct(ops2, length - 1, current2, combinations2);

        operatorCombinations[length] = combinations;
        operatorCombinations2[length] = combinations2;
    }

    cout << part1(equations, operatorCombinations) << endl;
    cout << part2(equations, operatorCombinations2) << endl;
}