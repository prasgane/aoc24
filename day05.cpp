#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

namespace D05 {

void load_data(unordered_map<int, std::unordered_set<int>>& rules, vector<std::vector<int>>& updates)
{

    string input = "../inputs/day5_input.txt";

    ifstream file(input);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        exit(0);
    }

    string ln;
    bool first_half = true;

    while (getline(file, ln)) {

        if (ln.empty() || ln == "\n") {
            first_half = false;
            continue;
        }

        if (first_half) {
            const auto idx = ln.find('|');
            int left = stoi(ln.substr(0, idx));
            int right = stoi(ln.substr(idx + 1, ln.size() - idx - 1));

            rules[right].emplace(left);

        } else {
            size_t comma_idx = ln.find(',');
            size_t current = 0;
            vector<int> update;
            while (comma_idx != std::string::npos) {
                update.push_back(stoi(ln.substr(current, comma_idx - current)));
                current = comma_idx + 1;
                comma_idx = ln.find(',', current);
            }
            update.push_back(stoi(ln.substr(current, ln.size() - current)));
            updates.push_back(update);
        }
    }
}

bool checkRule(const unordered_map<int, std::unordered_set<int>>& rules, const vector<int> update)
{

    vector<int> temp_row = update;
    temp_row.erase(temp_row.begin(), temp_row.begin() + 1);

    for (int i = 1; i < update.size() - 1; ++i) {
        temp_row.erase(temp_row.begin(), temp_row.begin() + 1);

        for (int element : temp_row) {
            if (rules.at(update[i]).contains(element))
                return false;
        }
    }
    return true;
}

void run()
{

    // vector<std::pair<int, int>> rules;
    unordered_map<int, std::unordered_set<int>> rules;
    vector<std::vector<int>> updates;

    load_data(rules, updates);

    int count_passed = 0;
    unsigned long solution1 = 0;
    unsigned long solution2 = 0;

    for (std::vector<int>& row : updates) {

        if (checkRule(rules, row)) {
            count_passed++;
            solution1 += row[row.size() / 2];
        } else {

            sort(row.begin(), row.end(), [&rules](int& a, int& b) {
                return !rules[b].contains(a);
            });

            solution2 += row[row.size() / 2];
        }
    }

    cout << "Solution 1 is " << solution1 << " Num passed " << count_passed << endl;

    cout << "Solution 2 is " << solution2 << endl;
}
}

int main()
{
    D05::run();
    return 0;
}