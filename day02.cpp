#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>

using namespace std;

namespace D02 {

bool isSafe(vector<int> report)
{
    int n = report.size();
    if (n < 2)
        return false;

    if (!ranges::is_sorted(report, std::greater {}) && !ranges::is_sorted(report, std::less {})) {
        return false;
    }

    for (int i = 1; i < n; i++) {
        int difference = abs(report[i] - report[i - 1]);
        if (difference < 1 || difference > 3)
            return false;
        if (difference == 0)
            return false;
    }
    return true;
}

bool isSafe2(vector<int> report)
{
    if (report.size() < 2)
        return false;

    if (isSafe(report))
        return true;

    int n = report.size();

    for (int i = 0; i < n; i++) {
        vector<int> reportCopy;
        for (int j = 0; j < n; j++) {
            if (j != i)
                reportCopy.push_back(report[j]);
        }
        if (isSafe(reportCopy))
            return true;
    }

    return false;
}

void run()
{

    string input = "../inputs/day2_input.txt";

    ifstream file(input);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        exit(0);
    }

    string line;
    int result = 0, result2 = 0;

    while (getline(file, line)) {

        stringstream iss(line);
        int number;
        std::vector<int> report;

        while (iss >> number)
            report.push_back(number);
        if (isSafe(report))
            result++;
        else {
            if (isSafe2(report))
                result2++;
        }
    }

    cout << "Number of Safes in the file is " << result << endl;

    cout << "Number of Safes with Safety Damper in the file is " << result + result2 << endl;
}
}

int main()
{
    D02::run();
    return 0;
}