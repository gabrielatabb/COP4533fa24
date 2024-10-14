#include <iostream>
#include "./program1.cpp"
#include "./program2.cpp"
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    for (int i = 0; i < 1000; i++) { //change this for larger datasets
        int n = rand() % 50 + 1; // 1-50
        int W = rand() % 41 + 10;
        vector<int> heights;
        vector<int> widths;
        for (int j = 0; j < n; j++){
            heights.push_back(rand() % 30 + 1); //1 - 30
            widths.push_back(rand() % 10 + 1); //1 - 10
        }

        //START TIMING
        auto result = program1(n, W, heights, widths);
        //STOP TIMING
    }
    // at the end of this, we have some variable that stored the total
    // of all 1000 (or 2000 or 5000 or whatever) trials. plot this??
    // or divide by num trials to get average? idk
    // and just plug that into excel

}