#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
/* Solution to program 5B
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/

/*
 * BOTTOM UP!!!!!
 * OPT[i] = min total height needed for 1 to i
 * GOAL: OPT[n]
 *
 * OPT[i] = min(dp[i], dp[j-1] + max(heights[i to j])
 */
std::tuple<int, int, std::vector<int>> program5B(int n, int W, std::vector<int> heights, std::vector<int> widths){
    std::vector<int> dp(n + 1, INT_MAX); // our dp array, as outlined above. INT_MAX since we are minimizing
    std::vector<int> platforms(n + 1, 0); // num platforms used up until i
    std::vector<std::vector<int>> paintingPlaced(n + 1); // how many paintings on each platform

    dp[0] = 0; // base case

    for (int i = 0; i <= n; i++){
        int totWidth = 0;
        int maxHeight = 0;

        for (int j = i; j >= 1; j--){
            totWidth += widths[j - 1];
            if (totWidth > W)
                break;

            maxHeight = std::max(maxHeight, heights[j - 1]);
            if (dp[j - 1] + maxHeight  < dp[i]){
                dp[i] = dp[j - 1] + maxHeight;
                platforms[i] = platforms[j - 1] + 1;
                paintingPlaced[i] = paintingPlaced[j - 1];
                paintingPlaced[i].push_back(i - j + 1);
            }
        }
    }

    return std::make_tuple(platforms[n], dp[n], paintingPlaced[n]);
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
    auto result = program5B(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0;
}
