#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    vector<int> col1, col2;
    int one, two;

    ifstream inputFile("input.txt");

    while (inputFile >> one >> two) {
        col1.push_back(one);
        col2.push_back(two);
    }

    inputFile.close();

    unordered_map<int, int> counts;
    
    for (int num : col2) {
        counts[num]++;
    }

    int similarity = 0;

    for (int num : col1) {
        similarity += num * counts[num];
    }

    cout << similarity << endl;

    return 0;
}