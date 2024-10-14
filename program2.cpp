#include <iostream>
#include <vector>
#include <tuple>

std::tuple<int, int, std::vector<int>> program2(int n, int W, std::vector<int> heights, std::vector<int> widths) {
    int platforms = 0;
    int totalHeight = 0;
    std::vector<int> paintingsPerPlatform;

    int currentWidth = 0;
    int currentHeight = 0;
    int paintingsOnCurrentPlatform = 0;

    int turningPoint = 0;
    for (int i = 1; i < n; i++) {
        if (heights[i] > heights[i - 1]) {
            turningPoint = i;
            break;
        }
    }

    for (int i = 0; i < turningPoint; i++) {
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

    currentWidth = 0;
    currentHeight = 0;
    paintingsOnCurrentPlatform = 0;

    for (int i = turningPoint; i < n; i++) {
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

    // Read the heights and widths of the paintings
    for (int i = 0; i < n; i++) {
        std::cin >> heights[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> widths[i];
    }

    // Call program2 and get the result
    auto result = program2(n, W, heights, widths);

    // Output number of platforms
    std::cout << std::get<0>(result) << std::endl;
    // Output total height
    std::cout << std::get<1>(result) << std::endl;
    // Output number of paintings on each platform
    for (int i = 0; i < std::get<0>(result); i++) {
        std::cout << std::get<2>(result)[i] << std::endl;
    }

    return 0;
}
