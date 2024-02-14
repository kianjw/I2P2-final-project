/*#include <iostream>
#include <fstream>

// Function to read the best score from a file
int readBestScore() {
    std::ifstream file("best_score.txt");
    int bestScore = 0;
    if (file.is_open()) {
        file >> bestScore;
        file.close();
    }
    return bestScore;
}

// Function to write the best score to a file
void writeBestScore(int bestScore) {
    std::ofstream file("best_score.txt");
    if (file.is_open()) {
        file << bestScore;
        file.close();
    }
}

int main() {
    // Assume you have a variable 'currentScore' representing the player's current score
    int currentScore = 100;

    // Read the best score from the file
    int bestScore = readBestScore();

    // Check if the current score is higher than the best score
    if (currentScore > bestScore) {
        std::cout << "New best score!\n";
        bestScore = currentScore;

        // Update the best score in the file
        writeBestScore(bestScore);
    } else {
        std::cout << "Current best score: " << bestScore << "\n";
    }

    return 0;
}*/
