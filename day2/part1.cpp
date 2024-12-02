#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    string line;
    int n = 0;

    // loop through every report
    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        int level;
        int previousLevel;
        bool descending;
        bool safe = true;
        int i = 0;

        // loop through every level on the report
        while (lineStream >> level) {
            if (i == 0) {
                previousLevel = level;
                i++;
                continue;
            } else if (i == 1) {
                if (level > previousLevel) {
                    descending = false;
                } else if (level < previousLevel) {
                    descending = true;
                } else {
                    safe = false;
                    break;
                }
            }

            int diff = abs(level - previousLevel);

            if (diff > 3 || diff < 1) {
                safe = false;
                break;
            } 

            if (level > previousLevel) {
                if (descending) {
                    safe = false;
                    break;
                }
            } else {
                if (!descending) {
                    safe = false;
                    break;
                }
            }

            previousLevel = level;
            i++;
        }

        if (safe) {
            n++;
        }
    }

    cout << n << endl;

    return 0;
}