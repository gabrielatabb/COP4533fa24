#include <iostream>
#include <vector>
#include <tuple>

/* Solution to program 1
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
std::tuple<int, int, std::vector<int>> program1(int n, int W, std::vector<int> heights, std::vector<int> widths) {
    int platforms = 0;
    int totalHeight = 0;
    std::vector<int> paintingsPerPlatform;

    int currentWidth = 0;
    int currentHeight = 0;
    int paintingsOnCurrentPlatform = 0;

    for (int i = 0; i < n; i++) {

        if (currentWidth + widths[i] > W) {
            totalHeight += currentHeight;
            platforms++;
            paintingsPerPlatform.push_back(paintingsOnCurrentPlatform);

            currentWidth = widths[i];
            currentHeight = heights[i];
            paintingsOnCurrentPlatform = 1;
        } else {
            currentWidth += widths[i];
            currentHeight = std::max(currentHeight, heights[i]);
            paintingsOnCurrentPlatform++;
        }
    }

    if (paintingsOnCurrentPlatform > 0) {
        totalHeight += currentHeight;
        platforms++;
        paintingsPerPlatform.push_back(paintingsOnCurrentPlatform);
    }
    return std::make_tuple(platforms, totalHeight, paintingsPerPlatform);
}

int main() {
    int n, W;
    std::cin >> n >> W;
    std::vector<int> heights(n);
    std::vector<int> widths(n);

    for (int i = 0; i < n; i++) {
        std::cin >> heights[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> widths[i];
    }

    auto result = program1(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for (int i = 0; i < std::get<0>(result); i++) {
        std::cout << std::get<2>(result)[i] << std::endl;
    }

    return 0;
}
