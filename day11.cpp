#include <deque>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

using namespace std;

namespace D11 {

void load_data(deque<uint64_t>& inputData)
{
    string input = "../inputs/day11_input.txt";
    ifstream file(input);

    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        exit(0);
    }

    string line;

    getline(file, line);
    istringstream iss(line);

    int number;
    while (iss >> number)
        inputData.push_back(number);
}

uint64_t process_data(deque<uint64_t> stones, int num_blinks, int multiplication_factor)
{
    for (auto k [[maybe_unused]] : ranges::iota_view(0, num_blinks)) {
        size_t count = stones.size();
        for (size_t i = 0; i < count; i++) {
            uint64_t stone = stones[0]; // always pick the first element of the queue
            if (stone == 0)
                stones.push_back(1);
            else if (const string str = to_string(stone); not(str.size() & 1)) { // not(str.size() & 1) determines if the number of digits are even
                int mid = str.length() / 2;
                istringstream(str.substr(0, mid)) >> stone;
                stones.push_back(stone);
                istringstream(str.substr(mid)) >> stone;
                stones.push_back(stone);
            } else
                stones.push_back(stone * multiplication_factor);

            stones.pop_front();
        }
    }

    return stones.size();
}

vector<uint64_t> one_blink(const uint64_t& stone, const int multiplication_factor){
    if (stone == 0)
        return{1};
    else if (const string str = to_string(stone); not(str.size() & 1)) { // not(str.size() & 1) determines if the number of digits are even
        int mid = str.length() / 2;
        uint64_t first_half, second_half;
        istringstream(str.substr(0, mid)) >> first_half;
        istringstream(str.substr(mid)) >> second_half;
        return{first_half, second_half};
    } else
        return{stone * multiplication_factor};
}

uint64_t process_data2(deque<uint64_t> stones, int num_blinks, int multiplication_factor){
    unordered_map<uint64_t, size_t> map;
    for (const uint64_t& stone : stones)
        map[stone] += 1;

    unordered_map<uint64_t, size_t> next_map;
    for (const auto& k [[maybe_unused]] : ranges::iota_view(0, num_blinks)) {
        for (const auto& [value, count] : map) {
            for (const uint64_t& value_next : one_blink(value, multiplication_factor))
                next_map[value_next] += count;
        }
        map.clear();
        swap(map, next_map);
    }

    size_t count_tot = 0;
    for (const auto& [value, count] : map) 
        count_tot += count;
    return count_tot;
}


void run()
{

    uint64_t solution1 = 0, solution2 = 0;

    deque<uint64_t> inputData;
    load_data(inputData);

    solution1 = process_data(inputData, 25, 2024);

    solution2 = process_data2(inputData, 75, 2024);

    cout << "Solution to part 1 " << solution1 << endl;

    cout << "Solution to part 2 " << solution2 << endl;
}
}

int main()
{
    D11::run();
    return 0;
}