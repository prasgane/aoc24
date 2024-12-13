#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

namespace D03 {

void run(bool first_solution = false)
{

    string input = "../inputs/day3_input.txt";

    ifstream file(input);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        exit(0);
    }

    string line;
    regex mul_regex(R"(mul\((\d{1,3}),(\d{1,3})\))");
    regex do_regex(R"(do\(\))");
    regex dont_regex(R"(don't\(\))");
    regex combined_regex(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");

    long long solution = 0;
    bool enabled = true;

    while (getline(file, line)) {

        smatch match;
        sregex_iterator matches_begin(line.begin(), line.end(), combined_regex);
        // sregex_iterator matches_begin(line.begin(), line.end(), mul_regex);
        sregex_iterator matches_end;

        for (auto it = matches_begin; it != matches_end; ++it) {
            match = *it;

            if (regex_match(match.str(), do_regex))
                enabled = true;
            else if (regex_match(match.str(), dont_regex))
                enabled = false;
            else if (enabled && regex_match(match.str(), mul_regex)) {
                int x = stoi(match[1].str());
                int y = stoi(match[2].str());
                solution += x * y;
                // logFile << x << " " << y << endl;
            }
        }
    }
    cout << "Solution is " << solution << endl;
}
}

int main()
{
    D03::run(true);
    return 0;
}