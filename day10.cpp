#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace D10 {

using map2d = vector<vector<int>>;
using vecint = vector<int>;

void load_data(map2d& map, vector<pair<int, int>>& start_location)
{

    string input = "../inputs/day10_input.txt";
    ifstream file(input);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        exit(0);
    }

    string line;
    int row = 0;

    while (getline(file, line)) {
        vecint line_data;
        for (size_t col = 0; col < line.size(); col++) {
            size_t num = line[col] - '0';

            line_data.push_back(num);

            if (num == 0)
                start_location.push_back(make_pair(row, col));
        }
        row++;
        map.push_back(line_data);
    }
}

const pair<int, int> direction[4] = {
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

bool inBounds(int x, int y, int lim)
{
    return x >= 0 && y >= 0 && x < lim && y < lim;
}

set<vector<int>> process_data(map2d& map, int x, int y, int previous_alt = -1)
{

    set<vector<int>> visited_points;

    if (!inBounds(x, y, map.size()))
        return { { -1, -1 } };

    if (map[x][y] != previous_alt + 1)
        return { { -1, -1 } };

    if (previous_alt == 8)
        return { { x, y } };

    set<vector<int>> temp;

    temp = process_data(map, x + 1, y, previous_alt + 1);
    visited_points.insert(temp.begin(), temp.end());

    temp = process_data(map, x - 1, y, previous_alt + 1);
    visited_points.insert(temp.begin(), temp.end());

    temp = process_data(map, x, y + 1, previous_alt + 1);
    visited_points.insert(temp.begin(), temp.end());

    temp = process_data(map, x, y - 1, previous_alt + 1);
    visited_points.insert(temp.begin(), temp.end());

    return visited_points;
}

void process_data2(map2d& map, int x, int y, set<map2d>& unique_trail, map2d path, int previous_alt = -1)
{

    if (!inBounds(x, y, map.size()))
        return;

    if (map[x][y] != previous_alt + 1)
        return;

    if (previous_alt == 8) {
        path.push_back({ x, y });
        unique_trail.insert(path);
        return;
    }

    path.push_back({ x, y });

    process_data2(map, x + 1, y, unique_trail, path, previous_alt + 1);

    process_data2(map, x - 1, y, unique_trail, path, previous_alt + 1);

    process_data2(map, x, y + 1, unique_trail, path, previous_alt + 1);

    process_data2(map, x, y - 1, unique_trail, path, previous_alt + 1);
}

void run()
{

    int solution1 = 0, solution2 = 0;

    map2d filedata;
    vector<pair<int, int>> start_locations;

    load_data(filedata, start_locations);

    for (auto loc : start_locations) {
        solution1 += process_data(filedata, loc.first, loc.second, -1).size() - 1;

        set<map2d> temp;
        process_data2(filedata, loc.first, loc.second, temp, {}, -1);
        solution2 += temp.size();
    }

    cout << "Solution to part 1 " << solution1 << endl;

    cout << "Solution to part 2 " << solution2 << endl;
}
}

int main()
{
    D10::run();
    return 0;
}