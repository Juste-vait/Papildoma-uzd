#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <regex>
#include <cctype>
#include <algorithm>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream word_output("output.txt");
    ofstream cross_ref_output("cross_reference.txt");

    if (!input.is_open()) {
        cerr << "Nepavyko atidaryti input.txt\n";
        return 1;
    }

    map<string, int> word_count;
    map<string, set<int>> word_lines;


    return 0;
}
