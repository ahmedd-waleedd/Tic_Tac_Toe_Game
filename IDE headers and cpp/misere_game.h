#ifndef MISERE_GAME_H
#define MISERE_GAME_H
#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class Mis_Board:public Board<T> {
public:
    char mis_ridx;
    char mis_cidx;
    Mis_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Mis_Player : public Player<T> {
public:
    Mis_Player();
    Mis_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
    void setname(string Name){this->name = Name;}
};

template <typename T>
class Mis_Random_Player : public Player<T>{
public:
    Mis_Random_Player (string name , T symbol);
    void getmove(int &x, int &y) ;
private:
int dimension;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()


template <typename T>
Mis_Board<T>::Mis_Board() {
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
bool Mis_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        mis_ridx=x+48;
        mis_cidx=y+48;
        return true;
    }
    return false;
}

template <typename T>
void Mis_Board<T>::display_board() {
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


// Returns true if there is any winner
template <typename T>
bool Mis_Board<T>::is_win() {
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

// Return true if 9 moves are done and no winner
template <typename T>
bool Mis_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Mis_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Mis_Player<T>::Mis_Player(string name, T symbol) : Player<T>(name, symbol) {  }

template <typename T>
void Mis_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces:";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Mis_Random_Player<T>::Mis_Random_Player(string name , T symbol) : Player<T>(symbol) {
   int dimension = 3;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Mis_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 3;  // Random number between 0 and 2
    y = rand() % 3;
}



// Ai Player part 

template <typename T>
class MisAIPlayer : public Player<T> {
public:
    MisAIPlayer(T symbol);

    void getmove(int& x, int& y) override;
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
    void setBoardPointer(Mis_Board<T>* board);
private:
    Mis_Board<T>* boardPtr;
};


template <typename T>
MisAIPlayer<T>::MisAIPlayer(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void MisAIPlayer<T>::getmove(int& x, int& y) {

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
int MisAIPlayer<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    }
    else if (this->boardPtr->is_draw()) {
        return 0;
    }
    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (this->symbol == 'O') ? 'X' : 'O';

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
pair<int, int> MisAIPlayer<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };
    T opponentSymbol = (this->symbol == 'O') ? 'X' : 'O';
    // If no immediate win or block, use MinMax to find the best move

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, 'O')) {
                int moveValue = calculateMinMax(this->symbol, true);
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
void MisAIPlayer<T>::setBoardPointer(Mis_Board<T>* board) {
    this->boardPtr = board;
}






#endif //MISERE_GAME_H
