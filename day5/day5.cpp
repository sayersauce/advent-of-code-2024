#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void loadRulesAndUpdates(ifstream& file, map<int, set<int>>& rules, vector<vector<int>>& updates) {
    string line;
    bool lineIsRule = true;

    while (getline(file, line)) {
        if (line == "") {
            lineIsRule = false;
            continue;
        }

        if (lineIsRule) {
            // loading in rules
            // pages are always 2 digit

            int pageBefore = stoi(line.substr(0, 2));
            int page = stoi(line.substr(3, 2));

            rules[page].insert(pageBefore);
        } else {
            // loading in updates

            stringstream stream(line);
            string page;
            vector<int> update;

            while(getline(stream, page, ',')) {
                update.push_back(stoi(page));
            }

            updates.push_back(update);
        }
    }
}

void findValidUpdates(map<int, set<int>>& rules, vector<vector<int>>& updates, vector<int>& valid, vector<int>& invalid) {
    for (int i = 0; i < updates.size(); i++) {
        vector<int> update = updates[i];
        int n = update.size();
        bool validUpdate = true;

        // don't need to check last page
        for (int j = 0; j < n - 1; j++) {
            int page = update[j];
            set<int> pagesToCheck = rules[page];

            for (int k = j + 1; k < n; k++) {
                if (pagesToCheck.find(update[k]) != pagesToCheck.end()) {
                    // page found after this one, breaking the rule
                    validUpdate = false;
                    invalid.push_back(i);
                    break;
                }
            }

            if (!validUpdate) {
                break;
            }
        }

        if (validUpdate) {
            valid.push_back(i);
        }
    }
}

int part1(vector<vector<int>>& updates, vector<int>& valid) {
    int total = 0;

    for (int i : valid) {
        total += updates[i][(updates[i].size() - 1) / 2];
    }

    return total;
}

int part2(vector<vector<int>>& updates, vector<int>& invalid, map<int, set<int>>& rules) {
    // Kahn's algorithm for topological sorting
    // Rules is the dependency list
    int total = 0;

    for (int i : invalid) {
        vector<int> update = updates[i];
        map<int, set<int>> dependencies;
        map<int, int> degrees;

        // Making dependency lists for this particular update

        for (int page : update) {
            dependencies[page] = {};
            degrees[page] = 0;
            if (rules.find(page) != rules.end()) {
                for (int dep : rules[page]) {
                    if (find(update.begin(), update.end(), dep) != update.end()) {
                        dependencies[page].insert(dep);
                        degrees[page]++;
                    }
                }
            }
        }

        // Kahn's

        queue<int> q;
        vector<int> ordered;

        // Add all pages with degree 0 to the queue
        for (const auto& pair : degrees) {
            int page = pair.first;
            int degree = pair.second;

            if (degree == 0) {
                q.push(page);
            }
        }

        while (!q.empty()) {
            int at = q.front();
            q.pop();
            ordered.push_back(at);

            // Inefficient because of incorrect adjacency list, should be node -> neighbours not node <- neighbours in the map
            // Loop through all pages in the dependencies map
            for (const auto& [page, deps] : dependencies) {
                if (deps.find(at) != deps.end()) {
                    degrees[page]--;

                    if (degrees[page] == 0) {
                        q.push(page);
                    }
                }
            }
        }

        total += ordered[(ordered.size() - 1) / 2];
    }

    return total;
}

int main() {
    // considering which data structure to use, thinking a dictionary of page numbers to sets
    // each page number has a set of page numbers that must come before it
    // loop through each page number in the update and check if any page numbers after this break the rule
    // n^2?

    ifstream file("input.txt");
    map<int, set<int>> rules;
    vector<vector<int>> updates;

    loadRulesAndUpdates(file, rules, updates);

    vector<int> valid;
    vector<int> invalid;

    findValidUpdates(rules, updates, valid, invalid);

    cout << part1(updates, valid) << endl;

    cout << part2(updates, invalid, rules) << endl;

    return 0;
}