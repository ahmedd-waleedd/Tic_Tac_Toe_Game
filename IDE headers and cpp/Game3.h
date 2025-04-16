#pragma once


#ifndef GAME3_H
#define GAME3_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <limits>
#include <algorithm>
using namespace std;

template<typename T>
class Game3 : public Board<T>  {
protected:
    T currentplayer;
    int turns = 0;
    int player1Score;  // Score for Player 1
    int player2Score;  // Score for Player 2

public:
    Game3();
    T** getBoard();  // Getter for the board
    bool update_board(int x, int y, T symbol);
    void display_board();
    int check_three_consecutive(T symbol); // Check for 3 consecutive symbols
    bool is_win(); 
    bool is_draw();
    bool game_is_over();
    int GetMoves();
    int GetPlayer1Score();
    int GetPlayer2Score();
    ~Game3();
   
};

// Game3player Class
template<typename T>
class Game3player : public Player<T> {
private:
    int Playerscore = 0;

public:
    Game3player(std::string name, T symbol);
    void getmove(int& x, int& y) override;
};

// Game3RandomPlayer Class
template<typename T>
class Game3RandomPlayer : public RandomPlayer<T> {
private:
    int dimension = 5; 
public:
    Game3RandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};



// ...........................IMPLEMENTATION IS HERE.....................................

// Implementation of Game3 methods
template<typename T>
Game3<T>::Game3() {
    this->rows = 5;
    this->columns = 5;
    this->n_moves = 0;
    this->player1Score = 0;
    this->player2Score = 0;


    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
}

template<typename T>
 T** Game3<T>::getBoard() { return this->board; }

 template<typename T>
 bool Game3<T>::update_board(int x, int y, T symbol) {
     if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
         return false; // Out of bounds
     }

     if (symbol != 0) { // Make a move
         if (this->board[x][y] != 0) return false; // Cell already occupied
         this->board[x][y] = symbol;
         this->n_moves++;
         this->turns++;
     }
     else { // Undo a move
         if (this->board[x][y] == 0) return false; // Cell already empty
         this->board[x][y] = 0;
         this->n_moves--;
         this->turns--;
     }

     return true;
 }


template <typename T>
void Game3<T>::display_board() {
    cout << endl;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            //cout << "(" << i << "," << j << ")";
            if (this->board[i][j] == 'X' || this->board[i][j] == 'O') {
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
bool Game3<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

template<typename T>
bool Game3<T>::is_draw() {
    if (this->turns < 24) {
        return false;  // Do not check for draw until after 24 moves
    }

    // After 24 turns, if no winner and board is full, it's a draw
    if (this->n_moves == 25 && !is_win()) {
        return true;  // It's a draw
    }
    return false;  // Not a draw yet
}


template<typename T>
bool Game3<T>::game_is_over() {
    return (this->turns >= 24) && (is_win() || is_draw());  // Only check after 24 turns
}

template<typename T>
int Game3<T>::GetMoves(){ return this->n_moves; }


template<typename T>
int Game3<T>::check_three_consecutive(T symbol) {
    int count = 0;

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i][j + 1] == symbol &&
                this->board[i][j + 2] == symbol) {
                count++;
            }
        }
    }

    // Check columns
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i <= this->rows - 3; i++) {
            if (this->board[i][j] == symbol &&
                this->board[i + 1][j] == symbol &&
                this->board[i + 2][j] == symbol) {
                count++;
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i + 1][j + 1] == symbol &&
                this->board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }
    
    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i + 1][j - 1] == symbol &&
                this->board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }

    return count;
}


template<typename T>
int Game3<T>::GetPlayer1Score() { return this->check_three_consecutive('X'); }


template<typename T>
int Game3<T>::GetPlayer2Score() { return this->check_three_consecutive('O'); }


template<typename T>
inline Game3<T>::~Game3()
{
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

//==========================================================================
//==========================================================================
//                   Implementation of Game3player methods
template<typename T>
Game3player<T>::Game3player(std::string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Game3player<T>::getmove(int& x, int& y) {
    std::cout<< this->getname() << " Enter your move (row and column): ";
    std::cin >> x >> y;
}

// Implementation of Game3RandomPlayer methods
template<typename T>
Game3RandomPlayer<T>::Game3RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {}

template<typename T>
void Game3RandomPlayer<T>::getmove(int& x, int& y) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    x = rand() % this->dimension;  
    y = rand() % this->dimension;
}

//==========================================================================
//==========================================================================



template <typename T>
class Game3AIPlayer : public Player<T> {
public:
    Game3AIPlayer(T symbol);

    void getmove(int& x, int& y) override;
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
    void setBoardPointer(Game3<T>* board);
private:
    Game3<T>* boardPtr;
};


template <typename T>
Game3AIPlayer<T>::Game3AIPlayer(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void Game3AIPlayer<T>::getmove(int& x, int& y) {

    if (!boardPtr) {
        std::cerr << "Error: boardPtr is null." << std::endl;
        exit(1);
    }

    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
template <typename T>
int Game3AIPlayer<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    }
    else if (this->boardPtr->is_draw()) {
        return 0;
    }
    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (this->symbol == 'O') ? 'X' : 'O';

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                }
                else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
template <typename T>
pair<int, int> Game3AIPlayer<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };
    T opponentSymbol = (this->symbol == 'O') ? 'X' : 'O';
    // If no immediate win or block, use MinMax to find the best move

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, 'O')) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move
                if (moveValue > bestValue) {
                    bestMove = { i, j };
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}


template <typename T>
void Game3AIPlayer<T>::setBoardPointer(Game3<T>* board) {
    this->boardPtr = board;
}




#endif // GAME3_H
