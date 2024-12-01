#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

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

    sort(col1.begin(), col1.end());
    sort(col2.begin(), col2.end());

    int n = col1.size();
    int distance = 0;

    for (int i = 0; i < n; i++) {
        distance += abs(col2[i] - col1[i]);
    }

    cout << distance << endl;

    return 0;
}