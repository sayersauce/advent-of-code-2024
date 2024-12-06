#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <set>

using namespace std;
using coord = pair<int, int>; // i, j coordinates on grid
using location = pair<coord, char>; // i, j coordinates with the guard's direction ^,>,v,<

set<coord> part1(vector<vector<char>> grid, vector<int> guard) {
    int n = grid[0].size();
    char dir = '^';
    set<coord> visited;

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
            if (guard[1] - 1 == -1) {
                guard[1]--;
            } else if (grid[guard[0]][guard[1] - 1] == '#') {
                dir = '^';
            } else {
                guard[1]--;
            }
        }
    }

    return visited;
}

bool checkIfLoop(vector<vector<char>> grid, vector<int> guard) {
    int n = grid[0].size();
    char dir = '^';

    set<location> visited;

    while (guard[0] < n && guard[0] >= 0 && guard[1] < n && guard[1] >= 0) {
        location loc = make_pair(make_pair(guard[0], guard[1]), dir);

        if (visited.find(loc) != visited.end()) {
            return true;
        }

        visited.insert(loc);

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
            if (guard[1] - 1 == -1) {
                guard[1]--;
            } else if (grid[guard[0]][guard[1] - 1] == '#') {
                dir = '^';
            } else {
                guard[1]--;
            }
        }
    }

    return false;
}

int part2(vector<vector<char>> grid, vector<int> guard, set<pair<int, int>> path) {
    // Brute force.
    // Originally looped through all cells, optimised slightly by only checking the original path of the guard.
    // From ~ 60 seconds to ~ 15 seconds after this change, for this input data.
    int n = grid[0].size();
    int loops = 0;

    for (auto [i, j] : path) {
        vector<vector<char>> newGrid = grid;
        newGrid[i][j] = '#';
        loops += checkIfLoop(newGrid, guard);
    }

    return loops;
}

int main() {
    ifstream file("input.txt");
    string line;
    vector<vector<char>> grid;
    vector<int> guard;

    int i = 0;

    while (getline(file, line)) {
        int j = 0;
        vector<char> row;

        for (char c : line) {
            row.push_back(c);

            if (c == '^') {
                guard = {i, j};
            }

            j++;
        }

        grid.push_back(row);

        i++;
    }

    set<coord> visited = part1(grid, guard);

    cout << visited.size() << endl;
    cout << part2(grid, guard, visited) << endl;
    
    return 0;
}