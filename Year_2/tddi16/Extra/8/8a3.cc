#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to find the best track selection for the given tape length
void maximizeTapeUsage(int N, vector<int>& tracks) {
    int num_tracks = tracks.size();
    
    // DP table to store the maximum duration we can achieve with a given tape length
    vector<vector<int>> dp(num_tracks + 1, vector<int>(N + 1, 0));

    // Fill DP table
    for (int i = 1; i <= num_tracks; ++i) {
        for (int j = 0; j <= N; ++j) {
            if (tracks[i - 1] <= j) {
                dp[i][j] = max(dp[i - 1][j], tracks[i - 1] + dp[i - 1][j - tracks[i - 1]]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Backtrack to find which tracks were selected
    vector<int> selected_tracks;
    int remaining_time = N;

    // Start backtracking from the last track and the full tape length (N)
    for (int i = num_tracks; i > 0 && remaining_time > 0; --i) {
        // If the value in dp[i][remaining_time] differs from dp[i-1][remaining_time], it means
        // the i-th track was used in the optimal solution
        if (dp[i][remaining_time] != dp[i - 1][remaining_time]) {
            selected_tracks.push_back(tracks[i - 1]); // Track was included
            remaining_time -= tracks[i - 1];          // Reduce the remaining time
        }
    }

    // Reverse the selected tracks to maintain the original order
    reverse(selected_tracks.begin(), selected_tracks.end());

    // Print the selected tracks in the correct order
    for (int i = 0; i < selected_tracks.size(); ++i) {
        cout << selected_tracks[i] << " ";
    }
    cout << "sum:" << dp[num_tracks][N] << endl;
}

int main() {
    // Reading input until end of file (EOF)
    int N, num_tracks;
    
    while (cin >> N >> num_tracks) {
        vector<int> tracks(num_tracks);
        for (int i = 0; i < num_tracks; ++i) {
            cin >> tracks[i];
        }
        // Process each test case
        maximizeTapeUsage(N, tracks);
    }

    return 0;
}
