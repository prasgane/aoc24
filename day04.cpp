#include <regex>
#include <iostream>
#include <fstream>


using namespace std;

namespace D04{

    void run(){

        string input = "../inputs/day4_input.txt";

        ifstream file(input);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file." << std::endl;
            exit(0);
        }

        string ln;
        vector<string> wordgrid;

        while (getline(file, ln))
            wordgrid.push_back(ln);

        unsigned long solution=0;

        for (string& s : wordgrid){
            for (int i = 0; i < s.length() - 3; i++){
                string xmas = s.substr(i, 4);
                if (xmas == "XMAS" || xmas == "SAMX")
                    solution++;
            }
        }

        for (int i = 0; i < wordgrid[0].length(); i++){
            for(int j = 0; j < wordgrid.size()-3; j++){
                stringstream xmas;
			    xmas << wordgrid[j][i] << wordgrid[j+1][i] << wordgrid[j+2][i] << wordgrid[j+3][i];
                
                if (xmas.str() == "XMAS" || xmas.str() == "SAMX")
                    solution++;
            }
        }

        for (int i = 0; i < wordgrid.size() -3; i++){
            for(int j = 3; j <  wordgrid[i].length(); j++){

                stringstream xmas;
			    xmas << wordgrid[i][j] << wordgrid[i + 1][j - 1] << wordgrid[i + 2][j - 2] << wordgrid[i + 3][j - 3];

                if (xmas.str() == "XMAS" || xmas.str() == "SAMX")
                    solution++;
            }
        }

        //right diagonal
        for (int i = 0; i < wordgrid.size() - 3; i++){
            for (int j = 0; j < wordgrid[i].length() - 3; j++){
                stringstream xmas;
			    xmas << wordgrid[i][j] << wordgrid[i + 1][j + 1] << wordgrid[i + 2][j + 2] << wordgrid[i + 3][j + 3];
                if (xmas.str() == "XMAS" || xmas.str() == "SAMX")
                    solution++;
            }
        }

        unsigned long solution2 = 0;

        for (int i = 1; i < wordgrid.size() - 1; i++){
            for (int j = 1; j < wordgrid[i].length() - 1; j++){

                stringstream left, right;
                left << wordgrid[i - 1][j - 1] << wordgrid[i][j] << wordgrid[i + 1][j + 1];
                right << wordgrid[i + 1][j - 1] << wordgrid[i][j] << wordgrid[i - 1][j + 1];

                if( (left.str() == "MAS" || left.str() == "SAM") && (right.str() == "MAS" || right.str() == "SAM"))
                    solution2++;
            }
        }
        cout << "Solution for Part 1 is: " << solution << endl;
        cout << "Solution for Part 2 is: " << solution2 << endl;

    }
}

int main(){
    D04::run();
    return 0;
}