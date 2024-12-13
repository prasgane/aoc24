#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace D07 {
struct CalibrationData {
    CalibrationData(long long tv, vector<int> nums)
        : test_value(tv)
        , rhs(nums)
    {
    }

    long long test_value;
    vector<int> rhs;
};

void load_data(vector<CalibrationData>& calibration_data)
{

    string input = "../inputs/day7_input.txt";
    ifstream file(input);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        exit(0);
    }

    string ln;

    while (getline(file, ln)) {

        vector<int> rhs_data;
        size_t colon_pos = ln.find(':');
        long long test_val = stoll(ln.substr(0, colon_pos));

        stringstream line_stream(ln.substr(colon_pos + 1));
        int num;

        while (line_stream >> num)
            rhs_data.push_back(num);

        CalibrationData line_data(test_val, rhs_data);
        calibration_data.emplace_back(line_data);
    }
}
// credit to https://github.com/anuraglamsal/AdventOfCode2024
bool process_data(vector<int> rhs, long long solution, long long result, int current_idx)
{
    if (current_idx != rhs.size()) {
        result += rhs[current_idx];
        if (!process_data(rhs, solution, result, current_idx + 1)) {
            result -= rhs[current_idx];
            result *= rhs[current_idx];
            if (!process_data(rhs, solution, result, current_idx + 1)) {
                return false;
            }
        }
    } else {
        if (result != solution) {
            return false;
        }
    }
    return true;
}

bool process_data2(vector<int> rhs, long long solution, long long result, int current_idx)
{
    if (current_idx != rhs.size()) {
        result += rhs[current_idx];
        if (!process_data2(rhs, solution, result, current_idx + 1)) {
            result -= rhs[current_idx];
            result *= rhs[current_idx];
            if (!process_data2(rhs, solution, result, current_idx + 1)) {
                result /= rhs[current_idx];
                string num_1 = to_string(result);
                string num_2 = to_string(rhs[current_idx]);
                string cat = num_1 + num_2;
                try {
                    result = stoll(cat);
                    if (!process_data2(rhs, solution, result, current_idx + 1)) {
                        return false;
                    }
                } catch (exception) {
                    return false;
                }
            }
        }
    } else {
        if (result != solution)
            return false;
    }
    return true;
}

void run()
{

    vector<CalibrationData> calibration_data;
    load_data(calibration_data);
    unsigned long long solution1 = 0, solution2 = 0;
    for (auto calData : calibration_data) {
        if (process_data(calData.rhs, calData.test_value, 0, 0))
            solution1 += calData.test_value;

        if (process_data2(calData.rhs, calData.test_value, 0, 0))
            solution2 += calData.test_value;
    }
    cout << "Solution to part 1 " << solution1 << endl;

    cout << "Solution to part 2 " << solution2 << endl;
}
}

int main()
{
    D07::run();
    return 0;
}