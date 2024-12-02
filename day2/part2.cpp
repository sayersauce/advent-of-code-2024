#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool ascending(vector<int> list) {
    int prev, diff;
    int n = list.size();

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            if (list[i] <= prev) {
                return false;
            }

            diff = abs(list[i] - prev);

            if (diff > 3 || diff < 1) {
                return false;
            }
        }

        prev = list[i];
    }

    return true;
}

bool descending(vector<int> list) {
    int prev, diff;
    int n = list.size();

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            if (list[i] >= prev) {
                return false;
            }

            diff = abs(list[i] - prev);

            if (diff > 3 || diff < 1) {
                return false;
            }
        }

        prev = list[i];
    }

    return true;
}

int main() {
    // n^2 approach
    // check if removing each element leads to a sorted list
    ifstream inputFile("input.txt");
    string line;
    int numberSafe = 0;

    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        int level;
        vector<int> levels;

        while (lineStream >> level) {
            levels.push_back(level);
        }

        int n = levels.size();

        for (int i = 0; i < n; i++) {
            vector<int> newLevels = levels;
            newLevels.erase(newLevels.begin() + i);

            if (ascending(newLevels) || descending(newLevels)) {
                numberSafe++;
                break;
            }
        }
    }

    cout << numberSafe << endl;

    return 0;
}