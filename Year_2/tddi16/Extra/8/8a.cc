#include <iostream>
#include <vector>
#include <algorithm>

/**
 * • number of tracks on the CD does not exceed 20
 * • no track is longer than N minutes
 * • tracks do not repeat
 * • length of each track is expressed as an integer number
 * • N is also integer
 */

std::vector<int> maxTape(int n, std::vector<int>& tracks)
{
    
    std::vector<std::vector<int>> dp(tracks.size() + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= tracks.size(); ++i)
    {
        for (int j{}; j <= n; ++j)
        {
            
            if (tracks[i - 1] <= j)
                dp[i][j] = std::max(dp[i - 1][j], tracks[i - 1] + dp[i - 1][j - tracks[i - 1]]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    std::vector<int> selectedTracks;
    int remainder = n;

    for (int i = tracks.size(); i > 0 && remainder > 0; --i)
    {
        if (dp[i][remainder] != dp[i - 1][remainder])
        {
            selectedTracks.push_back(tracks[i - 1]);
            remainder -= tracks[i - 1];
        }
    }

    for (auto const& track : selectedTracks)
        std::cout << track << " ";
    std::cout << std::endl;

    return selectedTracks;
}

int main()
{
    int n; // Data
    int numberOfTracks; // Number of tracks

    while (std::cin >> n >> numberOfTracks)
    {
        
        std::vector<int> tracks(numberOfTracks);
        for (int i{}; i < numberOfTracks; ++i)
            std::cin >> tracks[i];
        
        std::vector selectedTracks{maxTape(n, tracks)};

        for (auto const& track : selectedTracks)
            std::cout << track << " ";
        std::cout << "sum: " << n << std::endl;
    }

    

}