#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <ranges>
#include <unordered_map>

using namespace std;

namespace D01{
    void run(){

        freopen("../input.txt", "r", stdin);
        int n = 1000;
        vector<int> a(n), b(n);

        for (int i = 0; i < n; i++){
            cin >> a [i] >> b [i];
        }

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        long long distance = 0;
        long long similarity = 0;

        std::unordered_map<int,int> frequencyMap;

        for (int i = 0; i < n; i++) 
            distance += abs(a [i] - b [i]);

        for (const auto key : b)
            frequencyMap[key]++;

        for (const auto num : a)
            similarity += num * frequencyMap[num];

        cout << "Distance is: " << distance << endl;
        cout << "Similarity is: "<< similarity << endl;

    }
}

int main(){
    D01::run();
    return 0;
}