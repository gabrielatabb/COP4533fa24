#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
/* Solution to program 5A
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/

//helper function to allow memoization
int minHeight(int idx, int n, int W, std::vector<int>& heights, std::vector<int>& widths,
              std::vector<int>& memo, std::vector<int>& platforms, std::vector<std::vector<int>>& paintingPlaced){
    if (idx == n) // base case
        return 0;

    if (memo[idx] != -1) //already computed
        return memo[idx];

    int totWidth = 0;
    int maxHeight = 0;
    int minCost = INT_MAX;

    //checks all the platform combinations from idx to n
    for (int i = idx; i < n; i++){
        totWidth += widths[i];

        //if max platform width is exceeded
        if (totWidth > W)
            break;

        //the recursive call and cost of the current config
        maxHeight = std::max(maxHeight, heights[i]);
        int currCost = maxHeight + minHeight(i + 1, n, W, heights, widths,
                                             memo, platforms, paintingPlaced);

        // If this config is better, update minCost and the vectors
        if(currCost < minCost){
            minCost = currCost;
            if (i + 1 < n) {
                platforms[idx] = platforms[i + 1] + 1;
                paintingPlaced[idx] = paintingPlaced[i + 1];
            }
            else{
                platforms[idx] = 1;
                paintingPlaced[idx].clear();
            }
            paintingPlaced[idx].insert(paintingPlaced[idx].begin(), i - idx + 1);
        }
    }

    //memoize, return
    return memo[idx] = minCost;
}

std::tuple<int, int, std::vector<int>> program5A(int n, int W, std::vector<int> heights, std::vector<int> widths){
    std::vector<int> memo(n, -1); //memoization array
    std::vector<int> platforms(n, 0); //num platforms used up until i
    std::vector<std::vector<int>> paintingPlaced(n); //how many plaintings on each platform

    //solve the problem, starting at the first painting. the helper function handles the recursive calls.
    int sol = minHeight(0, n, W, heights, widths, memo, platforms, paintingPlaced);
    return std::make_tuple(platforms[0], sol, paintingPlaced[0]);
}

int main(){
    int n, W;
    std::cin >> n >> W;
    std::vector<int> heights(n);
    std::vector<int> widths(n);
    for(int i = 0; i < n; i++){
        std::cin >> heights[i];
    }
    for(int i = 0; i < n; i++){
        std::cin >> widths[i];
    }
    auto result = program5A(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0;
}
