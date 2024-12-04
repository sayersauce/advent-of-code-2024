#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <regex>

using namespace std;

int countSubstrings(string str, string substring) {
    return distance(sregex_iterator(str.begin(), str.end(), regex(substring)), sregex_iterator());
}

int countXmases(vector<string> strings) {
    int count = 0;

    for (string str : strings) {
        count += countSubstrings(str, "XMAS") + countSubstrings(str, "SAMX");
    }

    return count;
}

int part1(vector<string> rows, vector<string> cols, map<pair<int, int>, string> primary, map<pair<int, int>, string> secondary) {
    vector<string> diagonals;

    for (auto pair : primary) {
        diagonals.push_back(pair.second);
    }

    for (auto pair : secondary) {
        diagonals.push_back(pair.second);
    }

    return countXmases(rows) + countXmases(cols) + countXmases(diagonals);
}

int part2(map<pair<int, int>, string> primary, map<pair<int, int>, string> secondary, int width) {
    int xmases = 0;

    for (auto pair : primary) {
        int row = pair.first.first;
        int col = pair.first.second;
        string str = pair.second;

        if (str.length() < 3) {
            continue;
        }

        for (int i = 0; i <= str.length() - 3; i++) {
            string sub = str.substr(i, 3);

            if (sub == "MAS" || sub == "SAM") {
                int arow = row + i + 1;
                int acol = col + i + 1;

                // now check if there is a corresponding SAM OR MAS in secondary
                // convert rows and columns coordinates to indices in the secondary string
                // this was slightly confusing, a better method could be used

                string sub2;

                if (arow + acol < width) {
                    string secondStr = secondary[make_pair(0, arow + acol)];
                    sub2 = secondStr.substr(arow - 1, 3);
                } else {
                    string secondStr = secondary[make_pair(arow - (width - acol), width)];
                    sub2 = secondStr.substr(arow - 2 - (arow - (width - acol)), 3);
                }

                if (sub2 == "MAS" || sub2 == "SAM") {
                    xmases++;
                }
            }
        }
    }

    return xmases;
}

int main() {
    ifstream file("input.txt");

    vector<string> rows;
    vector<string> cols;
    map<pair<int, int>, string> primaryDiagonals;
    map<pair<int, int>, string> secondaryDiagonals;

    string line;

    int i = 0;
    int width;
    
    // read file line by line
    while (std::getline(file, line)) {
        int j = 0;
        string row = "";

        for (char ch : line) {
            // rows
            row += ch;
            
            // cols
            if (i == 0) {
                cols.push_back(string(1, ch));
            } else {
                cols[j] += ch;
            }

            // primary diagonals
            if (i == 0 || j == 0) {
                primaryDiagonals[make_pair(i, j)] = string(1, ch);
            } else {
                primaryDiagonals[make_pair(i - min(i, j), j - min(i , j))] += ch;
            }

            // secondary diagonals
            if (i == 0 || j == width) {
                secondaryDiagonals[make_pair(i, j)] = string(1, ch);
            } else if (i + j <= width) {
                secondaryDiagonals[make_pair(0, i + j)] += ch;
            } else {
                secondaryDiagonals[make_pair(i - (width - j), width)] += ch;
            }

            j++;
        }

        rows.push_back(row);

        width = j;

        i++;
    }
    
    cout << "part 1: " << part1(rows, cols, primaryDiagonals, secondaryDiagonals) << endl;
    cout << "part 2: " << part2(primaryDiagonals, secondaryDiagonals, width) << endl;

    return 0;
}