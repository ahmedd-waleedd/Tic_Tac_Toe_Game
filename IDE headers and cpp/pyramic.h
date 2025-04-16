//
// Created by Ahmed Waleed on 12/5/2024.
//

#ifndef PYRAMIC_H
#define PYRAMIC_H


#include <vector>
#include <limits>
#include <algorithm> 
#include "BoardGame_Classes.h"



int pyr_ridx;
int pyr_cidx;
int pyr_c;
char pyr_ch;



template <typename T>
class Pyramic_Board:public Board<T> {
public:

    Pyramic_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    T* operator[](T index) {
        return this->board[index];  // Return the row at 'index'
    }
};

template <typename T>
class Pyramic_Player : public Player<T> {
public:
    Pyramic_Player();
    Pyramic_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Pyramic_Random_Player : public RandomPlayer<T>{
public:
    Pyramic_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Pyramic_Board<T>::Pyramic_Board() {
    this->rows = this->columns = 5;
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
bool Pyramic_Board<T>::update_board(int x, int y, T mark) {
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
        pyr_c = mark ;
        pyr_ch = char(pyr_c);
        pyr_ridx = x;
        pyr_cidx = y;
        //cout<<ch<<endl;
        return true;

    }
    return false;
}


// Display the board and the pieces on it
template <typename T>
void Pyramic_Board<T>::display_board() {
    cout << endl;

    for (size_t i = 2; i < this->rows; ++i) { // Start from the 3rd row (index 2)
        if (i == 2) {
            // For the 3rd row, print only the 3rd element
            for (size_t j = 0; j <= 4; ++j) {
                if (j == 2) {
                    if (this->board[i][j] == 'X' || this->board[i][j] == 'O') {
                        cout << this->board[i][j] << " ";
                    }
                    else {
                        cout << "-" << " ";
                    }
                }
                else {
                    cout << "  ";
                }
            }
        }
        else if (i == 3) { // For the 4th row, print only the 2nd, 3rd, and 4th elements
            for (size_t j = 0; j <= 4; ++j) {
                if (j == 0 || j == 4) {
                    cout << "  ";
                }
                else {
                    if (this->board[i][j] == 'X' || this->board[i][j] == 'O') {
                        cout << this->board[i][j] << " ";
                    }
                    else {
                        cout << "-" << " ";
                    }
                }
            }
        }
        else if (i == 4) { // For the 5th row, print the whole row
            for (size_t j = 0; j <= 4; ++j) {
                if (this->board[i][j] == 'X' || this->board[i][j] == 'O') {
                    cout << this->board[i][j] << " ";
                }
                else {
                    cout << "-" << " ";
                }
            }
        }

        cout << endl; // Move to the next row
    }


    cout << endl << endl;
    // Prompting a helping grid to the user (Pyramid style)
    bool Isecond = true; bool Ithird = true; bool Ifourth = true;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // Row 0: Centered [0,2]
            if (i == 2 && Isecond) {
                Isecond = false;
                cout << "       " << "[2,2]" << endl;
            }
            // Row 1: Slightly shifted left [1,1] [1,2] [1,3]
            if (i == 3 && Ithird) {
                Ithird = false;
                cout << "  " << "[3,1][3,2][3,3]" << endl;
            }
            // Row 2: Further shifted left [2,0] to [2,4]
            if (i == 4 && Ifourth) {
                Ifourth = false;
                cout << "[4,0][4,1][4,2][4,3][4,4]" << endl;
            }
        }
    }

    cout << endl;
}


// Returns true if there is any winner
template <typename T>
bool Pyramic_Board<T>::is_win() {

    // Horizontal check
    if(this->board[pyr_ridx][pyr_cidx] != 'X' && this->board[pyr_ridx][pyr_cidx] != 'O') {
        cout<<"Let's start!"<<endl ;
        return false;
    }
    else {

    }
    string hchk="";
    for(int i = 0; i < this->rows; i++) {
        hchk+=this->board[pyr_ridx][i];
    }
    //cout<<"Horizontal check: "<<hchk<<endl;
    bool match=false;
    int counter=0;
    int j = 0;
    for(int i = 0 ; i < hchk.size(); i++) {
        if(hchk[i] == pyr_ch) {
            counter++;
            j++;
            if(counter == 3) {
                return true;
            }
        }
        else {
            counter = 0 ;
            j=0;
        }
    }


    //Vertical check
    string vchk="";
    for(int i = 0; i < this->rows; i++) {
        vchk+=this->board[i][pyr_cidx];
    }
    //cout<<"Vertical check: "<<vchk<<endl;
    bool match1=false;
    int counter1=0;
    int j1 = 0;
    for(int i = 0 ; i < vchk.size(); i++) {
        if(vchk[i] == pyr_ch) {
            counter1++;
            j1++;
            if(counter1 == 3) {
                return true;
            }
        }
        else {
            counter1 = 0 ;
            j1=0;
        }
    }



    //Right Diagonal check
    string rchk="";

    int rstart;
    int cstart;

    if (pyr_cidx == pyr_ridx  ){
        rstart = 0;
        cstart = 0;
    }
    else if(pyr_ridx>pyr_cidx){
        rstart = pyr_ridx-pyr_cidx;
        cstart = 0;
    }
    else {
        rstart = 0;
        cstart = pyr_cidx-pyr_ridx;
    }


    for(int i = 0; i < this->rows; i++) {
        if(rstart +i < this->rows && cstart + i < this->columns) {
            rchk+=this->board[rstart+i][cstart+i];
        }
        else {
            break;
        }
    }
    //cout<<"Right Diagonal check: "<<rchk<<endl;
    bool match2=false;
    int counter2=0;
    int j2 = 0;
    for(int i = 0 ; i < rchk.size(); i++) {
        if(rchk[i] == pyr_ch) {
            counter2++;
            j2++;
            if(counter2 == 3) {
                return true;
            }
        }
        else {
            counter2 = 0 ;
            j2=0;
        }
    }



    //Left Diagonal check
    string lchk;
    int lrstart;
    int lcstart;

    if ((pyr_ridx + pyr_cidx ) == this->columns - 1){
        lrstart = 0;
        lcstart = this->columns-1;
    }
    else if((pyr_ridx + pyr_cidx ) < this->columns) {
        lrstart = 0;
        lcstart = (pyr_ridx + pyr_cidx) ;

    }
    else {
        lrstart =  (pyr_ridx + pyr_cidx) - (this->columns - 1);
        lcstart = this->columns-1;
    }

    for(int i = 0; i < this->rows; i++) {
        if(lrstart +i < 3 && lcstart - i >= 0) {
            lchk+=this->board[lrstart+i][lcstart-i];
        }
    }
    //cout<<"Left Diagonal check: "<<lchk<<endl;
    bool match3=false;
    int counter3=0;
    int j3 = 0;
    for(int i = 0 ; i < lchk.size(); i++) {
        if(lchk[i] == pyr_ch) {
            counter3++;
            j3++;
            if(counter3 == 3) {
                return true;
            }
        }
        else {
            counter3 = 0 ;
            j3=0;
        }
    }


    return false;
}





// Return true if 9 moves are done and no winner
template <typename T>
bool Pyramic_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramic_Board<T>::game_is_over() {

    return is_win() || is_draw();
}

//--------------------------------------

template <typename T>
Pyramic_Player<T>::Pyramic_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramic_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces:";
    cin >> x >> y;
    
}
template <typename T>
Pyramic_Random_Player<T>::Pyramic_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Pyramic_Random_Player<T>::getmove(int& x, int& y) {
    std::vector<std::pair<int, int>> valid_moves = {
                 {2,2},         
          {3,1}, {3 ,2}, {3, 3},  
       {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4} 
    };

    // Initialize random seed
    srand(time(0));

    // Select a random valid move
    int random_index = rand() % valid_moves.size();
    std::pair<int, int> selected_move = valid_moves[random_index];

    // Use the selected coordinates (x, y) from the valid moves
     x = selected_move.first;
     y = selected_move.second;
}



// -----------------------------------------------------------------------------------------------


    


  template <typename T>
  class PyramicAiPlayer : public Player<T> {
  public:
      PyramicAiPlayer(T symbol);

      void getmove(int& x, int& y) override;
      int calculateMinMax(T s, bool isMaximizing);
      std::pair<int, int> getBestMove();
      void setBoardPtr(Pyramic_Board<T>* board);
      bool is_valid_move(Pyramic_Board<T>* board, int i, int j);
  private:
      Pyramic_Board<T>* boardPtr; const std::vector<std::pair<int, int>> allowed_indices = {
                     {2, 2},
             {3, 1}, {3, 2}, {3, 3},
      {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}
      };
  };


//--------------------------------------- IMPLEMENTATION

template <typename T>
PyramicAiPlayer<T>::PyramicAiPlayer(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

    // Method to get the best move for the player
    template <typename T>
    void PyramicAiPlayer<T>::getmove(int& x, int& y) {

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
    int PyramicAiPlayer<T>::calculateMinMax(T s, bool isMaximizing) {
        if (this->boardPtr->is_win()) {
            return isMaximizing ? -1 : 1;
        }
        else if (this->boardPtr->is_draw()) {
            return 0;
        }
        int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
        T opponentSymbol = (s == 'O') ? 'X' : 'O';

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (is_valid_move(boardPtr, i, j))
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

    template <typename T>
    std::pair<int, int> PyramicAiPlayer<T>::getBestMove() {
        int bestValue = std::numeric_limits<int>::min();
        std::pair<int, int> bestMove = { -1, -1 };
        T opponentSymbol = (this->getsymbol() == 'O') ? 'X' : 'O';  // Opponent symbol is 'X' if AI is 'O'

        // Check if AI can win in the next move
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (is_valid_move(boardPtr, i, j)) {
                    if (this->boardPtr->update_board(i, j, this->getsymbol())) {
                        if (this->boardPtr->is_win()) {
                            return { i, j };  // AI wins
                        }
                        this->boardPtr->update_board(i, j, 0); // Undo move
                    }
                }
            }
        }

        // Check if opponent can win, and block them
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (is_valid_move(boardPtr, i, j)) {
                    if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                        if (this->boardPtr->is_win()) {
                            this->boardPtr->update_board(i, j, 0); // Undo move
                            return { i, j };  // Block opponent's winning move
                        }
                        this->boardPtr->update_board(i, j, 0); // Undo move
                    }
                }
            }
        }

        // If no immediate win or block, use MinMax to find the best move
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (is_valid_move(boardPtr, i, j)) {
                    if (this->boardPtr->update_board(i, j, this->getsymbol())) {
                        int moveValue = calculateMinMax(this->symbol, true);
                        this->boardPtr->update_board(i, j, 0); // Undo move
                        if (moveValue > bestValue) {
                            bestMove = { i, j };
                            bestValue = moveValue;
                        }
                    }
                }
            }
        }

        return bestMove;
    }

    template <typename T>
    void PyramicAiPlayer<T>::setBoardPtr(Pyramic_Board<T>* board) {
        this->boardPtr = board;
    }


    template <typename T>
    bool PyramicAiPlayer<T>::is_valid_move(Pyramic_Board<T>* board, int i, int j) {
        // Check if (i, j) is in allowed_indices
        bool is_allowed = false;
        for (const auto& pair : allowed_indices) {
            if (pair.first == i && pair.second == j) {
                is_allowed = true;
                break;
            }
        }

        // Check if the cell is empty (board[i][j] == 0)
        if (is_allowed && board->operator[](i)[j] == 0) {
            return true;
        }
        return false;
    }






#endif //PYRAMIC_H
