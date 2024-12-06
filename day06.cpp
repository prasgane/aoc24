#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

template<typename T>
struct Coordinate{

    constexpr bool operator <  (const Coordinate& p) const { if (x < p.x) return true; else if (p.x < x) return false; else return y < p.y; }
	constexpr Coordinate operator + (const Coordinate& p) const { return Coordinate(x + p.x, y + p.y); }

	template<typename U, std::enable_if_t<std::is_integral_v<T>, bool> = true>
	bool InBounds(const U& grid) const { return x >= 0 && y >= 0 && x < grid.size() && y < grid[x].size(); }
	template<typename U, std::enable_if_t<std::is_integral_v<T>, bool> = true>
	const auto& EntityInPosition(const U& grid) const { return grid[x][y]; }

	T x = {}, y = {};
};
using Point = Coordinate<int>;
constexpr std::array<Point, 4> directions = { Point(-1, 0), Point(0, 1), Point(1, 0), Point(0, -1), };
using Guard = std::pair<Point, int>;

namespace D06{

    void load_data(vector<std::string>& map, Point& guard){

        string input = "../inputs/day6_input.txt";
        ifstream file(input);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file." << std::endl;
            exit(0);
        }

        string ln;

        while (getline(file, ln)){
            if (auto pos = ln.find('^'); pos != std::string::npos)
			    guard = {(int)map.size(), (int)pos};
                
		    map.push_back(std::move(ln));
        }
    }

    void run(){
	    vector<std::string> map;
        Point guard;

        load_data(map, guard);

        Guard cyclical_test = {guard, 0};

        set<Point> pointsVisited = {guard};
        int dir = 0;
        int solution2 = 0;

        while(true){
            Point next_position = guard + directions[dir];

            if (!next_position.InBounds(map))
                break;
            if (next_position.EntityInPosition(map) == '#')
                dir = (dir+1)%4;
            else{
                guard = next_position;
                pointsVisited.insert(guard);
            }
        }

        for (int x = 0; x < map.size(); ++x)
            for (int y = 0; y < map.front().size(); ++y)
                if (map[x][y] == '.' && pointsVisited.find({x, y}) != pointsVisited.cend())
                {
                    map[x][y] = '#';
                    std::set<Guard> check = {cyclical_test};
                    guard = cyclical_test.first;
                    dir = 0;
                    while (true)
                    {
                        Point next_position = guard + directions[dir];
                        if (!next_position.InBounds(map))
                            break;
                        if (next_position.EntityInPosition(map) == '#')
                            dir = (dir+1)%4;
                        else
                            guard = next_position;
                        if (!check.insert({next_position, dir}).second)
                        {
                            ++solution2;
                            break;
                        }
                    }
                    map[x][y]= '.';
                }


        cout << "Unique Positions visits " << pointsVisited.size() << endl;
        cout << "Cyclic Paths " << solution2 << endl;
  
    }
}

int main(){
    D06::run();
    return 0;
}