#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <tuple>
using namespace std;
/* Solution to program 4
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
std::tuple<int, int, std::vector<int>> program4(int n, int W, std::vector<int> heights, std::vector<int> widths) {
    vector<int> dp;
    //Fill the dp vector with INT_MAX
    for(int i = 0; i < n+1; i++)
        dp.push_back(INT_MAX);

    vector<int> track;
    //Fill track vector with -1
    for(int i = 0; i < n+1; i++)
        track.push_back(-1);

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int currentWidth = 0;
        int maxHeight = 0;

        for (int j = i; j > 0; j--) {
            currentWidth += widths[j - 1];
            if (currentWidth > W)
                break;

            maxHeight = max(maxHeight, heights[j - 1]);

            if (dp[j - 1] + maxHeight < dp[i]) {
                dp[i] = dp[j - 1] + maxHeight;
                track[i] = j - 1;
            }
        }
    }

    vector<int> rows;
    for (int i = n; i > 0; i = track[i]) {
        rows.push_back(i - track[i]);
    }

    //reverse the order of the rows function
    for(int i = 0; i < rows.size()/2; i++){
        int temp = rows[rows.size() - (i + 1)];
        rows[rows.size() - (i + 1)] = rows[i];
        rows[i] = temp;
    }

    return make_tuple(rows.size(), dp[n], rows);
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
    auto result = program4(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << ", ";
    }
    return 0; 
}