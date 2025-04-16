#pragma once

#ifndef T2_5_CONNECT_FOUR_H
#define T2_5_CONNECT_FOUR_H
#include<algorithm>
#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm> // For std::max and std::min


template <typename T>
class Game2 :public Board<T> {
public:
    Game2();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

    T* operator[](T index) {
        return this->board[index];  // Return the row at 'index'
    }
};

template <typename T>
class Game2_player : public Player<T> {
public:
    Game2_player(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class Game2_random_player : public RandomPlayer<T> {
public:
    Game2_random_player(T symbol);
    void getmove(int& x, int& y);
    void setBoardPointer(Game2<T>* board);
    bool is_valid_move(Game2<T>* board, int i, int j);
private:
    Game2<T>* boardPtr;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template <typename T>
Game2<T>::Game2() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Game2<T>::update_board(int x, int y, T mark) {
    if (x + 1 < this->rows) { // Ensure the row below is within bounds
        if (this->board[x + 1][y] != 'X' && this->board[x + 1][y] != 'O') {
            return false;
        }
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;



}


// Display the board and the pieces on it
template <typename T>
void Game2<T>::display_board() {
    for (int i = 0; i < this->rows ; i++) {
        for (int j = 0; j < this->columns ; j++) {
            //cout << "(" << i << "," << j << ")";
            if (this->board[i][j] == 'X' || this->board[i][j] == 'O' || this->board[i][j] == 'D') {
                cout << this->board[i][j] << " ";
            }
            else {
                cout << "-" << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


template <typename T>
bool Game2<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= 7 - 4; j++) { // Check horizontally
            if ((this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2] && this->board[i][j + 2] == this->board[i][j + 3]) && this->board[i][j] != 0) {
                return true;
            }
        }
        for (int j = 0; j <= 6 - 4; j++) { // Check vertically
            if ((this->board[j][i] == this->board[j + 1][i] && this->board[j + 1][i] == this->board[j + 2][i] && this->board[j + 2][i] == this->board[j + 3][i]) && this->board[j][i] != 0) {
                return true;
            }
        }
    }

    // Check diagonals for 4 consecutive X or O
    for (int i = 0; i <= 6 - 4; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            // Check main diagonal
            if ((this->board[i][j] == this->board[i + 1][j + 1] && this->board[i + 1][j + 1] == this->board[i + 2][j + 2] && this->board[i + 2][j + 2] == this->board[i + 3][j + 3]) && this->board[i][j] != 0) {
                return true;
            }
            // Check anti-diagonal
            if ((this->board[i][j + 3] == this->board[i + 1][j + 2] && this->board[i + 1][j + 2] == this->board[i + 2][j + 1] && this->board[i + 2][j + 1] == this->board[i + 3][j]) && this->board[i][j + 3] != 0) {
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool Game2<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool Game2<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

template <typename T>
Game2_player<T>::Game2_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Game2_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your a move from BOTTEM to TOP\n" << "X = 0-5  ,  y = 0-6\n" << "Enter here x and y separated by a space :";
    cin >> x >> y;
}

template <typename T>
Game2_random_player<T>::Game2_random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
     // Seed the random number generator
}

template <typename T>
void Game2_random_player<T>::getmove(int& x, int& y) {
    do {
    x = rand() % 6;  
    y = rand() % 7;
    } while (!this->is_valid_move(this->boardPtr, x, y));
}



template <typename T>
void Game2_random_player<T>::setBoardPointer(Game2<T>* board) {
    this->boardPtr = board;
    if (!boardPtr) {
        std::cerr << "Error: boardPtr is null." << std::endl;
        exit(1);
    }

}


template <typename T>
bool Game2_random_player<T>::is_valid_move(Game2<T>* board, int i, int j) {
    // Check if the column index is within bounds (0 to 6)
    if (j < 0 || j >= 7) {
        return false;
    }

    // Check if the row index is within bounds (0 to 5)
    if (i < 0 || i >= 6) {
        return false;
    }

    // Check if the cell at position (i, j) is empty
    // Check if the cell at position (i, j) is empty
    if (board->operator[](i)[j] == 0) {
        // If it's the bottom-most row (i == 5), it's valid because the piece will fall there.
        if (i == 5) {
            return true;
        }

        // Check if the cell below is occupied (only check if i < 5)
        if (board->operator[](i + 1)[j] != 0) {
            return true;
        }
    }
    return false;
}



//--------------------------------------- IMPLEMENTATION  Of AI PLAYER ------------------------------



template <typename T>
class Game2AiPlayer : public Player<T> {
public:
    Game2AiPlayer(T symbol);
    void getmove(int& x, int& y) override;
    int calculateMinMax(T playerSymbol, bool isMaximizing, int depth);
    std::pair<int, int> getBestMove();
    void setBoardPointer(Game2<T>* board);
    bool is_valid_move(int i, int j);

private:
    Game2<T>* boardPtr;
};






//--------------------------------------- IMPLEMENTATION



// Constructor
template <typename T>
Game2AiPlayer<T>::Game2AiPlayer(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Set Board Pointer
template <typename T>
void Game2AiPlayer<T>::setBoardPointer(Game2<T>* board) {
    this->boardPtr = board;
    if (!boardPtr) {
        std::cerr << "Error: boardPtr is null." << std::endl;
        throw std::runtime_error("Board pointer is null");
    }
}

// Validate Move
template <typename T>
bool Game2AiPlayer<T>::is_valid_move(int i, int j) {
    // Ensure we're within bounds
    if (j < 0 || j >= 7) return false;

    // Check the bottom-most available spot in the column
    if (this->boardPtr->operator[](i)[j] == 0) {
        if (i == 5 || this->boardPtr->operator[](i + 1)[j] != 0) {
            return true; // Valid move at the lowest empty spot
        }
    }
    return false;
}

// Minimax Algorithm
template <typename T>
int Game2AiPlayer<T>::calculateMinMax(T playerSymbol, bool isMaximizing, int depth) {
    // Base cases: stop if the game is over or max depth is reached
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -10 + depth : 10 - depth; // Prioritize faster wins
    }
    else if (this->boardPtr->is_draw()) {
        return 0; // Draw condition
    }
    if (depth == 0) {
        return 0; // Limit recursion depth
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (playerSymbol == 'O') ? 'X' : 'O';

    for (int j = 0; j < 7; ++j) { // Loop through columns
        for (int i = 5; i >= 0; --i) { // Bottom to top in each column
            if (is_valid_move(i, j)) {
                this->boardPtr->update_board(i, j, playerSymbol); // Make move

                int value = calculateMinMax(opponentSymbol, !isMaximizing, depth - 1);

                this->boardPtr->update_board(i, j, 0); // Undo move

                // Update bestValue
                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                }
                else {
                    bestValue = std::min(bestValue, value);
                }
                break; // Stop after placing in the first valid row of the column
            }
        }
    }

    return bestValue;
}


// Find the Best Move
template <typename T>
std::pair<int, int> Game2AiPlayer<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };
    T currentSymbol = this->getsymbol();

    const int maxDepth = 7;

    for (int j = 0; j < 7; ++j) { // Loop through columns
        for (int i = 5; i >= 0; --i) { // Bottom to top
            if (is_valid_move(i, j)) {
                this->boardPtr->update_board(i, j, currentSymbol); // Try move

                int moveValue = calculateMinMax(currentSymbol, false, maxDepth); 

                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestMove = { i, j };
                }
                break; // Only test the bottom-most valid row in the column
            }
        }
    }

    return bestMove;
}



// Get Move from AI Player
template <typename T>
void Game2AiPlayer<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}



#endif //T2_5_CONNECT_FOUR_H
