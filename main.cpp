#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Enum representing fruit symbols
enum class Fruit { CHERRY, ORANGE, LEMON, PLUM, WATERMELON, GRAPE };

// Function to convert a Fruit enum to its corresponding character
char fruitToChar(Fruit fruit) {
    switch (fruit) {
        case Fruit::CHERRY: return 'C';
        case Fruit::ORANGE: return 'O';
        case Fruit::LEMON: return 'L';
        case Fruit::PLUM: return 'P';
        case Fruit::WATERMELON: return 'W';
        case Fruit::GRAPE: return 'G';
        default: return '?';
    }
}

// Function to generate a random fruit
Fruit getRandomFruit() {
    int random = rand() % 6;
    return static_cast<Fruit>(random);
}

// Function to get points for a specific fruit and number of consecutive fruits
int getPoints(Fruit fruit, int consecutiveCount) {
    switch (fruit) {
        case Fruit::CHERRY:
            return (consecutiveCount == 1) ? 0 : (consecutiveCount == 2) ? 5 : (consecutiveCount == 3) ? 10 : (consecutiveCount == 4) ? 20 : 30;
        case Fruit::ORANGE:
            return (consecutiveCount == 1) ? 0 : (consecutiveCount == 2) ? 35 : (consecutiveCount == 3) ? 40 : (consecutiveCount == 4) ? 50 : 60;
        case Fruit::LEMON:
            return (consecutiveCount == 3) ? 70 : (consecutiveCount == 4) ? 80 : 90;
        case Fruit::PLUM:
            return (consecutiveCount == 3) ? 100 : (consecutiveCount == 4) ? 110 : 120;
        case Fruit::WATERMELON:
            return (consecutiveCount == 3) ? 130 : (consecutiveCount == 4) ? 140 : 150;
        case Fruit::GRAPE:
            return (consecutiveCount == 4) ? 170 : 180;
        default:
            return 0;
    }
}

// Function to fill the matrix with random fruits and print it
void fillAndPrintMatrix(Fruit matrix[][5], int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            matrix[i][j] = getRandomFruit();
            cout << fruitToChar(matrix[i][j]) << " ";
        }
        cout << endl;
    }
}

// Function to check for wins on a single line
int checkLine(Fruit matrix[][5], int numRows, int numCols, int curRow) {
    Fruit currentFruit = matrix[curRow][0];
    int consecutiveCount = 1;
    int maxConsecutiveCount = 1;
    int totalPoints = 0;

    for (int j = 1; j < numCols; j++) {
        if (matrix[curRow][j] == currentFruit) {
            consecutiveCount++;
            if (consecutiveCount > maxConsecutiveCount) {
                maxConsecutiveCount = consecutiveCount;
            }
        } else {
            currentFruit = matrix[curRow][j];
            consecutiveCount = 1;
        }
    }

    if (maxConsecutiveCount >= 3) {
        int winPoints = getPoints(currentFruit, maxConsecutiveCount);
        totalPoints += winPoints;
        cout << "Line " << curRow + 1 << ":" << endl;
        cout << "Figure: " << fruitToChar(currentFruit) << endl;
        cout << "Win: " << winPoints << "p" << endl;
        cout << "Figures: " << maxConsecutiveCount << endl;
    }

    return totalPoints;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    int numRows = 3;
    int numCols = 5;
    Fruit matrix[3][5];

    // Fill and print the matrix
    fillAndPrintMatrix(matrix, numRows, numCols);

    // Check for wins on each row
    int totalWon = 0;
    for (int curRow = 0; curRow < numRows; curRow++) {
        totalWon += checkLine(matrix, numRows, numCols, curRow);
    }

    if (totalWon == 0) {
        cout << "Better luck next time!" << endl;
    } else {
        cout << "Total Won: " << totalWon << "p" << endl;
    }

    return 0;
}
