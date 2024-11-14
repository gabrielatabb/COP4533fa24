#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <functional>

std::tuple<int, int, std::vector<int>> program3(int n, int W, std::vector<int> heights, std::vector<int> widths) {
    int minHeightSum = INT_MAX;
    int minPlatforms = INT_MAX;
    std::vector<int> bestPlatformCounts;

    std::function<void(int, int, int, std::vector<int>&)> findArrangement = [&](int start, int totalHeight, int platforms, std::vector<int>& platformCounts) {
        if (start == n) {
            if (totalHeight < minHeightSum || (totalHeight == minHeightSum && platforms < minPlatforms)) {
                minHeightSum = totalHeight;
                minPlatforms = platforms;
                bestPlatformCounts = platformCounts;
            }
            return;
        }

        int currentWidth = 0;
        int maxHeight = 0;
        int paintingsOnCurrentPlatform = 0; //Initialize new platform variables

        for (int i = start; i < n; i++) {
            currentWidth += widths[i];
            if (currentWidth > W) break;

            maxHeight = std::max(maxHeight, heights[i]);
            paintingsOnCurrentPlatform++;

            //Attempt to form a platform by adding current painting
            platformCounts.push_back(paintingsOnCurrentPlatform);

            //Add the max height of the current platform and start a new call
            findArrangement(i + 1, totalHeight + maxHeight, platforms + 1, platformCounts);

            platformCounts.pop_back();
        }
    };

    std::vector<int> platformCounts;
    findArrangement(0, 0, 0, platformCounts);//Recursive call that ensures exponential O(n2^n-1)

    return {minPlatforms, minHeightSum, bestPlatformCounts};
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

    auto result = program3(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for (int i = 0; i < std::get<0>(result); i++) {
        std::cout << std::get<2>(result)[i] << std::endl;
    }

    return 0;
}
