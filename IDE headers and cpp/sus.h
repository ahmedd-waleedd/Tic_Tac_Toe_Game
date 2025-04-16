//
// Created by Ahmed Waleed on 12/5/2024.
//

#ifndef SUS_H
#define SUS_H

#include <iostream>
#include <iomanip>
#include <cctype> 
#include <climits>
#include <algorithm>
using namespace std;

#include "BoardGame_Classes.h"

template <typename T>
class sus:public Board<T> {
public:
    int sus_ridx;
    int sus_cidx;
    int sus_c;
    char sus_ch;
    sus();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    void count_score();
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    string get_game_result(); 
private:
    int player1score = 0;
    int player2score = 0;
    string game_result = "";

    vector<bool>combinations_OF_wins{
        //first three goes to horizontal
        false, false,false
        //second three goes to vertical
        ,false, false,false
        //third two goes to diagonal
        ,false,false
    };

};

template <typename T>
class sus_Player : public Player<T> {
public:
    sus_Player();
    sus_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class sus_Random_Player : public RandomPlayer<T>{
public:
    sus_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
private:
};



//--------------------------------------- IMPLEMENTATION


template <typename T>
sus<T>::sus() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool sus<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x > this->rows || y < 0 || y > this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);

        }
        count_score();
        return true;
    }
    return false;
}


// Display the board and the pieces on it
template <typename T>
void sus<T>::display_board() {
    cout<<endl;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            //cout << "(" << i << "," << j << ")";
            if(this->board[i][j] == 'S' || this->board[i][j] == 'U') {
                cout <<this->board[i][j] << " ";
            }
            else {
                cout << "-" << " ";
            }
        }
        cout <<endl;
    }
    cout << endl;
}


template<typename T>
void sus<T>::count_score() {
    // Determine the current player
    int current_player = (this->n_moves % 2 == 0) ? 2 : 1;

    // Check horizontal rows
    for (int i = 0; i < 3; ++i) {
        if (!combinations_OF_wins[i]) { // Only check unused combinations
            if (this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S') {
                combinations_OF_wins[i] = true; // Mark as used
                if (current_player == 1) {
                    player1score++;
                }
                else {
                    player2score++;
                }
            }
        }
    }

    // Check vertical columns
    for (int i = 0; i < 3; ++i) {
        if (!combinations_OF_wins[i + 3]) {
            if (this->board[0][i] == 'S' && this->board[1][i] == 'U' && this->board[2][i] == 'S') {
                combinations_OF_wins[i + 3] = true; // Mark as used
                if (current_player == 1) {
                    player1score++;
                }
                else {
                    player2score++;
                }
            }
        }
    }

    // Check right diagonal
    if (!combinations_OF_wins[6]) {
        if (this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S') {
            combinations_OF_wins[6] = true; // Mark as used
            if (current_player == 1) {
                player1score++;
            }
            else {
                player2score++;
            }
        }
    }

    // Check left diagonal
    if (!combinations_OF_wins[7]) {
        if (this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S') {
            combinations_OF_wins[7] = true; // Mark as used
            if (current_player == 1) {
                player1score++;
            }
            else {
                player2score++;
            }
        }
    }

}


template <typename T>
bool sus<T>::is_win(){
    if (this->n_moves == 9) {
        if (this->player1score > this->player2score) {
            game_result = "Player 1 wins";
        }
        else if (this->player2score > this->player1score) {
            game_result = "Player 2 wins";
        }
        return true;
    }
    return false;
}


// Return true if 9 moves are done and no winner
template <typename T>
bool sus<T>::is_draw() {
    if (this->n_moves == 9 && !is_win()) {
        game_result = "Draw!";
        return true;
    }
    return false;
}

template <typename T>
bool sus<T>::game_is_over() {
    return is_win() || is_draw();
}

template<typename T>
 string sus<T>::get_game_result()
{
     return game_result;
}

//--------------------------------------

template <typename T>
sus_Player<T>::sus_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void sus_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces:";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
sus_Random_Player<T>::sus_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void sus_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}



//Ai Plaeyer Code is DOWN HERE // AiPlayer.cpp


template <typename T>
class SusAIPlayer : public Player<T> {
public:
    SusAIPlayer(T symbol);

    void getmove(int& x, int& y) override;
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
    void setBoardPointer(sus<T>* board);
private:
sus<T>* boardPtr;
};







//--------------------------------------- IMPLEMENTATION

#include <limits>
#include <algorithm> // For std::max and std::min
using namespace std;
// Constructor for the templated class
template <typename T>
SusAIPlayer<T>::SusAIPlayer(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void SusAIPlayer<T>::getmove(int& x, int& y) {

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
int SusAIPlayer<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    }
    else if (this->boardPtr->is_draw()) {
        return 0;
    }
    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
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
pair<int, int> SusAIPlayer<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };
    T opponentSymbol = 'S';
    this->symbol = 'U';
    // If no immediate win or block, use MinMax to find the best move

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, 'U')) {
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
void SusAIPlayer<T>::setBoardPointer(sus<T>* board) {
    this->boardPtr = board;
}




#endif //SUS_H
