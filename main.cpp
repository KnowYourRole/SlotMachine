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
    cout << endl;
}

// Function to check for wins on a single line
int checkLine(Fruit matrix[][5], int numRows, int numCols, int curRow) {
    Fruit currentFruit = matrix[curRow][0];
    Fruit winningFruit;
    int consecutiveCount = 1;
    int maxConsecutiveCount = 1;
    int totalPoints = 0;

    int lineNum;
    if(curRow == 0)
    {
        lineNum = 2;
    }
    else if(curRow == 1)
    {
        lineNum = 1;
    }
    else
    {
        lineNum = 3;
    }

    for (int j = 1; j < numCols; j++) {
        if (matrix[curRow][j] == currentFruit) {
            consecutiveCount++;
            if (consecutiveCount > maxConsecutiveCount) {
                maxConsecutiveCount = consecutiveCount;
                winningFruit = currentFruit;
            }
        } else {
            currentFruit = matrix[curRow][j];
            consecutiveCount = 1;
        }
    }

    if (maxConsecutiveCount >= 3) {
        int winPoints = getPoints(winningFruit, maxConsecutiveCount);
        totalPoints += winPoints;
        cout << "Line " << lineNum << ":" << endl;
        cout << "Figure: " << fruitToChar(winningFruit) << endl;
        cout << "Win: " << winPoints << "p" << endl;
        cout << "Figures: " << maxConsecutiveCount << endl << endl;
    }

    return totalPoints;
}

// Function to check for wins on a V line
int checkLineVStyle(Fruit matrix[][5], int numRows, int numCols, int startRow) {
    bool isDiag4;
    int totalPoints = 0;
    Fruit winningFruit;
    Fruit currentFruit = matrix[startRow][0];
    int consecutiveCount = 1;
    int maxConsecutiveCount = 1;
    
    bool goDown = (startRow == 0);  // Start from the top or bottom based on startRow

    // Skip the first fruit if startRow is strictly less than the boundary
    if (startRow == 0) {
        startRow++;
        isDiag4 = true;
    }
    else {
        startRow--;
        isDiag4 = false;
    }

    int startCol = 1;  // Always start from the second column

    while (startRow < numRows && startCol < numCols) {
        if (matrix[startRow][startCol] == currentFruit) {
            consecutiveCount++;
            if (consecutiveCount > maxConsecutiveCount) {
                maxConsecutiveCount = consecutiveCount;
                winningFruit = currentFruit;
            }
        } else {
            currentFruit = matrix[startRow][startCol];
            consecutiveCount = 1;
        }

        if (goDown) {
            startRow++;
            if (startRow == numRows) {
                goDown = false;
                startRow = numRows - 2;
            }
        } else {
            startRow--;
            if (startRow < 0) {
                goDown = true;
                startRow = 1;
            }
        }

        startCol++;  // Move to the next column
    }

    if (maxConsecutiveCount >= 3) {
        int winPoints = getPoints(winningFruit, maxConsecutiveCount);
        totalPoints += winPoints;
        cout << "Diagonal " << (isDiag4 == true ? 4 : 5) << ":" << endl;
        cout << "Figure: " << fruitToChar(winningFruit) << endl;
        cout << "Win: " << winPoints << "p" << endl;
        cout << "Figures: " << maxConsecutiveCount << endl << endl;
    }

    return totalPoints;
}

int checkLineWStyle(Fruit matrix[][5], int numRows, int numCols) {
    int totalPoints = 0;    
    int consecutiveCount = 1;
    int maxConsecutiveCount = 1;    
    bool goDown = true;  // Start from the top or bottom based on startRow
    
    int startRow = numRows - 2;
    Fruit currentFruit = matrix[startRow][0];
    Fruit winningFruit;
    int startCol = 1;  // Always start from the second column
    startRow++;

    while (startRow < numRows && startCol < numCols) {
        if (matrix[startRow][startCol] == currentFruit) {
            consecutiveCount++;
            if (consecutiveCount > maxConsecutiveCount) {
                maxConsecutiveCount = consecutiveCount;
                winningFruit = currentFruit;
            }
        } else {
            currentFruit = matrix[startRow][startCol];
            consecutiveCount = 1;
        }

        if (goDown) {
            startRow--;            
            goDown = false;
        } 
        else 
        {
            startRow++;
            goDown = true;
        }

        startCol++;  // Move to the next column
    }

    if (maxConsecutiveCount >= 3) {
        int winPoints = getPoints(winningFruit, maxConsecutiveCount);
        totalPoints += winPoints;
        cout << "Diagonal " << 6 << ":" << endl;
        cout << "Figure: " << fruitToChar(winningFruit) << endl;
        cout << "Win: " << winPoints << "p" << endl;
        cout << "Figures: " << maxConsecutiveCount << endl << endl;
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

    totalWon += checkLineVStyle(matrix, numRows, numCols, 0);
    totalWon += checkLineVStyle(matrix, numRows, numCols, numRows-1);
    totalWon += checkLineWStyle(matrix, numRows, numCols);

    if (totalWon == 0) {
        cout << "Better luck next time!" << endl;
    } else {
        cout << "Total Won: " << totalWon << "p" << endl;
    }

    return 0;
}

