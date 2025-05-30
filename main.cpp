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

string convert(const string& word) {
    string result;
    for (char ch : word) {
        if (isalpha(ch)) {
            result += tolower(ch);
        }
    }
    return result;
}

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

    string line;
    int line_number = 0;

    while (getline(input, line)) {
        ++line_number;

        istringstream iss(line);
        string word;
        while (iss >> word) {
            string converted = convert(word);
            if (!converted.empty()) {
                word_count[converted]++;
                word_lines[converted].insert(line_number);
            }
        }
    }

    for (const auto& [word, count] : word_count) {
        if (count > 1) {
            word_output << word << ": " << count << "\n";
        }
    }
    
    return 0;
}
