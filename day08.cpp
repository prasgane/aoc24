#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>
#include <boost/functional/hash.hpp>

using namespace std;

namespace D09{
    struct AntenaLocation{
        AntenaLocation(int x_, int y_) : x(x_), y(y_) {}

        constexpr inline AntenaLocation& operator+=(AntenaLocation const& second_location) noexcept {
            x += second_location.x;
            y += second_location.y;
            return *this;
        }

        constexpr inline AntenaLocation& operator-=(AntenaLocation const& second_location) noexcept {
            x -= second_location.x;
            y -= second_location.y;
            return *this;
        }

        constexpr inline AntenaLocation& operator+(AntenaLocation const& second_location) noexcept{
            return AntenaLocation{*this} += second_location;
        }

        constexpr inline AntenaLocation& operator-(AntenaLocation const& second_location) noexcept{
            return AntenaLocation{*this} -= second_location;
        }

        constexpr inline bool operator==(AntenaLocation const& second_location) const{
            return x == second_location.x && y == second_location.y;
        }

        float computeSlope(AntenaLocation const& second_location){
            return ((second_location.y - y)/(second_location.x - x));
        }

        bool inbounds(pair<int, int> map_size){
            return x >=0 && x < map_size.first && y >= 0 && y < map_size.second;
        }

        struct Hash {
            size_t operator()(const AntenaLocation& p) const {
                // Combine hash values of x and y coordinates
                size_t seed = 0;
                boost::hash_combine(seed, p.x);
                boost::hash_combine(seed, p.y);
                return seed;
            }
        };

        int x, y;
    };

    

    void load_data(unordered_map<char, vector<AntenaLocation>>& map, pair<int,int>& map_size){

        string input = "../inputs/day8_input.txt";
        ifstream file(input);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file." << std::endl;
            exit(0);
        }

        string line;
        int row = 0, col_length = 0;

        while (getline(file, line)){

            for(int col=0; col < line.size(); col++){

                if(line[col] != '.'){
                    map[line[col]].emplace_back(AntenaLocation(row, col));
                }
            }
            row++;
            col_length = line.size();            
		}
        map_size.first=row;
        map_size.second=col_length;

    }
    // credit to https://github.com/anuraglamsal/AdventOfCode2024
    void process_data(const unordered_map<char, vector<AntenaLocation>> map, pair<int, int> map_size, unordered_set<AntenaLocation, AntenaLocation::Hash>& unique_locations){
        for(const auto& pair: map){
            auto locations = pair.second;
            for(int i = 0; i < locations.size(); i++){
                AntenaLocation p1 = locations[i];
                for(int j=i; j < locations.size(); j++){
                    if(i==j)
                        continue;
                    AntenaLocation p2 = locations[j];
                    AntenaLocation delta{p2-p1};
                    
                    AntenaLocation temp{p1-delta};

                    if(temp.inbounds(map_size))
                        unique_locations.insert(temp);

                    AntenaLocation temp2{p2 + delta};
                    
                    if(temp2.inbounds(map_size))
                        unique_locations.insert(temp2);
                }
            }
        }
    }

    void process_data2(const unordered_map<char, vector<AntenaLocation>> map, pair<int, int> map_size, unordered_set<AntenaLocation, AntenaLocation::Hash>& unique_locations){
        for(const auto& pair: map){
            auto locations = pair.second;
            for(int i = 0; i < locations.size(); i++){
                AntenaLocation p1 = locations[i];
                for(int j=i; j < locations.size(); j++){
                    if(i==j)
                        continue;
                    AntenaLocation p2 = locations[j];
                    AntenaLocation delta{p2-p1};
                    unique_locations.insert(p2);
                    unique_locations.insert(p1);

                    AntenaLocation temp{p1-delta};
                    while(temp.inbounds(map_size)){
                        unique_locations.insert(temp);
                        temp -= delta;
                    }

                    AntenaLocation temp2{p2+delta};
                    while(temp2.inbounds(map_size)){
                        unique_locations.insert(temp2);
                        temp2 += delta;
                    }
                }
            }
        }
    }

    void run(){
  
        unordered_map<char, vector<AntenaLocation>> map;
        pair<int,int> map_size;
        unordered_set<AntenaLocation, AntenaLocation::Hash> unique_locations, unique_locations2;

        int solution1 = 0, solution2 = 0;

        load_data(map, map_size);
        process_data(map, map_size, unique_locations);

        process_data2(map, map_size, unique_locations2);

        solution1 = unique_locations.size();
        solution2 = unique_locations2.size();

        cout << "Solution to part 1 " << solution1 << endl;

        cout << "Solution to part 2 " << solution2 << endl;

    }
}

int main(){
    D09::run();
    return 0;
}