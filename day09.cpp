#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

namespace D09{

    struct Data{
        int id; //file number
        int size; //size
    };
    
    void load_data(list<Data>& filedata){

        string input = "../inputs/day9_input.txt";
        ifstream file(input);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file." << std::endl;
            exit(0);
        }

        string line;
        bool isfile = true;
        int idx = 0;

        while (getline(file, line)){

            for (auto c : line) {

                size_t size = c - '0';

                if(isfile){
                    filedata.push_back(Data(idx, size));
                } else{
                    filedata.push_back(Data(-1, size));
                    idx++;    
                }
                
                isfile = !isfile;
            }        
		}

        cout << "File data " << filedata.size() << endl;

    }

    vector<int> map_to_blocks(const list<Data>& map){

        vector<int> blocks;

        for(auto num: map){
            for(int i=0; i < num.size; i++)
                blocks.push_back(num.id);
        }

        return blocks;
    }

    long process_data(const list<Data>& map){

        vector<int> blocks = map_to_blocks(map);

        while(true){

            auto empty_slot = find(blocks.begin(), blocks.end(), -1);

            auto last_block = find_if(blocks.rbegin(), blocks.rend(), [](auto x) {return x!=-1;});

            size_t idx1 = distance(blocks.begin(), empty_slot);
            size_t idx2 = blocks.size() - (distance(blocks.rbegin(), last_block) + 1);

            if(idx2 < idx1)
                break;

            iter_swap(empty_slot, last_block);
        }

        long checksum = 0;
        int idx = 0;
        for (auto data : blocks){

            if (data != -1)
                checksum += data * idx;

            idx++;
        }

        return checksum;
        
    }
    // credit to https://github.com/mike919192/advent2024/blob/main/day9/day9.cpp
    long process_data2(list<Data>& map){

        auto backward_itr = find_if(map.rbegin(), map.rend(),  [](auto a) {return a.id != -1;});
        int id = (*backward_itr).id;

        for (int i = id; i >= 0; i--){

            backward_itr = find_if(backward_itr, map.rend(), [i](auto a) {return a.id == i;});
            size_t backward_idx = map.size() - (distance(map.rbegin(), backward_itr) + 1);
            
            auto itr = std::next(map.begin(), backward_idx);

            auto empty_itr = find_if(map.begin(), map.end(), 
                                [itr](auto a) {return a.id == -1 && a.size >= (*itr).size;});

            size_t empty_index = std::distance(map.begin(), empty_itr);

            if(backward_idx < empty_index || empty_itr == map.end())
                continue;

            int size_diff = (*empty_itr).size - (*itr).size;
            iter_swap(empty_itr, itr);

            (*itr).size = (*empty_itr).size;

            if(size_diff > 0)
                map.insert(next(empty_itr,1), Data(-1, size_diff));
        }

        int j = 0;
        long checksum = 0;

        for(const auto &datael : map){
            if(datael.id != -1){
                for (int i = 0; i < datael.size; i++) {
                    checksum += datael.id * j;
                    j++;
                }
            } else
                j += datael.size;
            
        }
        return checksum;
    }
            

    void run(){
  
        long solution1 = 0, solution2 = 0;

        list<Data> filedata;
        vector<int> blocks;

        load_data(filedata);
        // solution1 = process_data(filedata);

        solution2 = process_data2(filedata);

        cout << "Solution to part 1 " << solution1 << endl;

        cout << "Solution to part 2 " << solution2 << endl;

    }
}

int main(){
    D09::run();
    return 0;
}