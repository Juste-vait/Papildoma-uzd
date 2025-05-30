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
    ofstream url_output("urls.txt");

    if (!input.is_open()) {
        cerr << "Nepavyko atidaryti input.txt\n";
        return 1;
    }

    map<string, int> word_count;
    map<string, set<int>> word_lines;
    set<string> urls;

    regex url_pattern(R"((https?:\/\/[^\s]+)|(www\.[^\s]+)|([a-zA-Z0-9.-]+\.[a-zA-Z]{2,}))");

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

        sregex_iterator begin(line.begin(), line.end(), url_pattern);
        sregex_iterator end;
        for (auto it = begin; it != end; ++it) {
            urls.insert(it->str());
        }
    }

    for (const auto& [word, count] : word_count) {
        if (count > 1) {
            word_output << word << ": " << count << "\n";
        }
    }

    for (const auto& [word, lines] : word_lines) {
        if (word_count[word] > 1) {
            cross_ref_output << word << " pasirodė eilutėse: ";
            for (int ln : lines) {
                cross_ref_output << ln << " ";
            }
            cross_ref_output << "\n";
        }
    }

    for (const string& url : urls) {
        url_output << url << "\n";
    }

    return 0;
}
