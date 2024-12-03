#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

int main() {
    ifstream file("input.txt");

    ostringstream buffer;
    buffer << file.rdbuf();

    string text = buffer.str(); 
    regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");

    sregex_iterator begin(text.begin(), text.end(), pattern);
    sregex_iterator end;

    int total = 0;
    bool enabled = true;

    for (std::sregex_iterator it = begin; it != end; it++) {
        string match = it->str();

        if (match == "do()") {
            enabled = true;
        } else if (match == "don't()") {
            enabled = false;
        } else {
            if (enabled) {
                string x = it->str(1);
                string y = it->str(2);

                total += stoi(x) * stoi(y);
            }
        }
    }

    cout << total << endl;

    return 0;
}