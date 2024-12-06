#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <set>

using namespace std;

int main() {
    ifstream file("input.txt");
    string line;
    vector<vector<char>> grid;
    vector<vector<int>> obstructions;
    vector<int> guard;

    int i = 0;

    while (getline(file, line)) {
        int j = 0;
        vector<char> row;

        for (char c : line) {
            row.push_back(c);

            if (c == '^') {
                guard = {i, j};
            } else if (c == '#') {
                obstructions.push_back({i , j});
            }

            j++;
        }

        grid.push_back(row);

        i++;
    }

    // debug
    if (true) {
        int n = grid[0].size();

        cout << " ";

        for (int i = 0; i < n; i++) {
            cout << i;
        }

        cout << endl;

        int i = 0;

        for (auto row : grid) {
            cout << i;
            for (auto c : row) {
                cout << c;
            }
            cout << endl;
            i++;
        }

        cout << "guard " << guard[0] << ", " << guard[1] << endl;
    }

    // The grid is a square
    int n = grid[0].size();
    char dir = '^';
    set<pair<int, int>> visited;

    while (guard[0] < n && guard[0] >= 0 && guard[1] < n && guard[1] >= 0) {
        visited.insert(make_pair(guard[0], guard[1]));

        if (dir == '^') {
            if (guard[0] - 1 == -1) {
                guard[0]--;
            } else if (grid[guard[0] - 1][guard[1]] == '#') {
                dir = '>';
            } else {
                guard[0]--;
            }
        } else if (dir == '>') {
            if (guard[1] + 1 == n) {
                guard[1]++;
            } else if (grid[guard[0]][guard[1] + 1] == '#') {
                dir = 'v';
            } else {
                guard[1]++;
            }
        } else if (dir == 'v') {
            if (guard[0] + 1 == n) {
                guard[0]++;
            } else if (grid[guard[0] + 1][guard[1]] == '#') {
                dir = '<';
            } else {
                guard[0]++;
            }
        } else {
            if (guard[1] + -1 == -1) {
                guard[1]--;
            } else if (grid[guard[0]][guard[1] - 1] == '#') {
                dir = '^';
            } else {
                guard[1]--;
            }
        }
    }

    cout << visited.size() << endl;
    
    return 0;
}