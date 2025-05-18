#include <iostream>
#include <vector>


void maximizeTapeUsage(int n, std::vector<int>& tracks) {
    
    std::vector<std::vector<int>> dp(tracks.size() + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= tracks.size(); ++i) {
        for (int j = 0; j <= n; ++j) {
            if (tracks[i - 1] <= j) {
                dp[i][j] = std::max(dp[i - 1][j], tracks[i - 1] + dp[i - 1][j - tracks[i - 1]]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    std::vector<int> selectedTracks;
    int remainder = n;
    
    for (int i = tracks.size(); i > 0 && remainder > 0; --i) {
        if (dp[i][remainder] != dp[i - 1][remainder]) {
            selectedTracks.push_back(tracks[i - 1]);
            remainder -= tracks[i - 1];
        }
    }

    for (int i = selectedTracks.size() - 1; i >= 0; --i) {
        std::cout << selectedTracks[i] << " ";
    }
    std::cout << "sum:" << dp[tracks.size()][n] << std::endl;
}

int main() {
    int n;
    int numberOfTracks;
    
    while (std::cin >> n >> numberOfTracks) {
        std::vector<int> tracks(numberOfTracks);
        for (int i = 0; i < numberOfTracks; ++i) {
            std::cin >> tracks[i];
        }
        maximizeTapeUsage(n, tracks);
    }

    return 0;
}
