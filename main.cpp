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

// Function to convert a Fruit enum to its corresponding string name
string fruitToString(Fruit fruit) {
    switch (fruit) {
        case Fruit::CHERRY: return "Cherry";
        case Fruit::ORANGE: return "Orange";
        case Fruit::LEMON: return "Lemon";
        case Fruit::PLUM: return "Plum";
        case Fruit::WATERMELON: return "Watermelon";
        case Fruit::GRAPE: return "Grape";
        default: return "Unknown";
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

// Function to check for wins in a specific direction (left or right)
int checkLineDirection(Fruit matrix[][5], int numRows, int numCols, int curRow, int startCol, int colStep) {
    Fruit currentFruit = matrix[curRow][startCol];
    Fruit winningFruit;
    int consecutiveCount = 1;
    int maxConsecutiveCount = 1;
    int totalPoints = 0;

    int lineNum;
    if (curRow == 0) {
        lineNum = 2;
    } else if (curRow == 1) {
        lineNum = 1;
    } else {
        lineNum = 3;
    }

    for (int j = startCol + colStep; j >= 0 && j < numCols; j += colStep) {
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
        cout << "Figure: " << fruitToString(winningFruit) << endl;
        cout << "Win: " << winPoints << "p" << endl;
        cout << "Figures: " << maxConsecutiveCount << endl << endl;
    }

    return totalPoints;
}

// Function to check for wins on a single line
int checkLine(Fruit matrix[][5], int numRows, int numCols, int curRow) {
    int totalPoints = 0;
    
    // Check for wins left to right
    totalPoints += checkLineDirection(matrix, numRows, numCols, curRow, 0, 1);

    // Check for wins right to left
    totalPoints += checkLineDirection(matrix, numRows, numCols, curRow, numCols - 1, -1);

    return totalPoints;
}




// Function to check for wins in a specific vertical direction (upward or downward) and specific columns
int checkLineVDirection(Fruit matrix[][5], int numRows, int numCols, int startRow, int startCol, int colStep) {
    bool isDiag4;
    int totalPoints = 0;
    Fruit winningFruit;
    Fruit currentFruit = matrix[startRow][startCol];
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
    if(startCol == 0)
    {
        startCol++;
    }
    else if(startCol == numCols - 1)
    {
        startCol--;
    }

    while (startRow >= 0 && startRow < numRows && startCol >= 0 && startCol < numCols) {
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

        startCol += colStep;  // Move to the next column
    }

    if (maxConsecutiveCount >= 3) {
        int winPoints = getPoints(winningFruit, maxConsecutiveCount);
        totalPoints += winPoints;
        cout << "Diagonal " << (isDiag4 == true ? 4 : 5) << ":" << endl;
        cout << "Figure: " << fruitToString(winningFruit) << endl;
        cout << "Win: " << winPoints << "p" << endl;
        cout << "Figures: " << maxConsecutiveCount << endl << endl;
    }

    return totalPoints;
}

// Function to check for wins on a V line in both directions, starting from the last column towards the first
int checkLineVStyle(Fruit matrix[][5], int numRows, int numCols, int startRow) {
    int totalPoints = 0;
    
    // Check for wins downward, starting from the last column towards the first
    totalPoints += checkLineVDirection(matrix, numRows, numCols, startRow, 0, 1);

    // Check for wins upward, starting from the last column towards the first
    totalPoints += checkLineVDirection(matrix, numRows, numCols, startRow, numCols - 1, -1);

    return totalPoints;
}


// Function to check for wins in a specific horizontal direction (left or right) and specific rows
int checkLineWDirection(Fruit matrix[][5], int numRows, int numCols, int startCol, int startRow, int rowStep) {
    int totalPoints = 0;
    Fruit winningFruit;
    Fruit currentFruit = matrix[startRow][startCol];
    int consecutiveCount = 1;
    int maxConsecutiveCount = 1;
    
    bool goRight = (startCol == 0);  // Start from the left or right based on startCol

    // Skip the first fruit if startCol is strictly less than the boundary
    if (startCol == 0) {
        startCol++;
    }
    else {
        startCol--;
    }
    if(startRow == numRows - 2)
    {
        startRow++;
    }
    else    //in case we deside to change the size of our matrix (currently wound't be called)
    {
        startRow--;
    }

    while (startRow >= 0 && startRow < numRows && startCol >= 0 && startCol < numCols) {
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

        if (goRight)
            startCol++;
        else 
            startCol--;

        if (startRow >= numRows-1) 
            startRow = numRows - 2;
        else if (startRow <= numRows-2) 
            startRow = numRows - 1;
    }

    if (maxConsecutiveCount >= 3) {
        int winPoints = getPoints(winningFruit, maxConsecutiveCount);
        totalPoints += winPoints;
        cout << "Diagonal " << (goRight ? 7 : 8) << ":" << endl;
        cout << "Figure: " << fruitToString(winningFruit) << endl;
        cout << "Win: " << winPoints << "p" << endl;
        cout << "Figures: " << maxConsecutiveCount << endl << endl;
    }

    return totalPoints;
}


// Function to check for wins on a W line in both directions, starting from the first row towards the last
int checkLineWStyle(Fruit matrix[][5], int numRows, int numCols) {
    int totalPoints = 0;
    
    // Check for wins rightward, starting from the first row towards the last
    totalPoints += checkLineWDirection(matrix, numRows, numCols, 0, numRows - 2, 1);

    // Check for wins leftward, starting from the first row towards the last
    totalPoints += checkLineWDirection(matrix, numRows, numCols, numCols - 1, numRows - 2, -1);

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
