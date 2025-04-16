//
// Created by Ahmed Waleed on 12/8/2024.
//

#ifndef ULTIMATE_H
#define ULTIMATE_H
#include "BoardGame_Classes.h"

char Ult_ridx;
char Ult_cidx;
int Ult_c;
char Ult_ch;





template <typename T>
class Ult_Board:public Board<T>  {

public:

    Ult_Board ();
    char get_win(char& sym);
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Ult_Player : public Player<T> {
public:
    Ult_Player();
    Ult_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Ult_Random_Player : public RandomPlayer<T>{
public:
    Ult_Random_Player (T symbol);
    void getmove(int &x, int &y);
};



//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;


// Constructor for X_O_Board
template <typename T>
Ult_Board<T>::Ult_Board() {
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
bool Ult_Board<T>::update_board(int x, int y, T mark) {
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
        Ult_c = mark;
        Ult_ch = char(mark);
        Ult_ridx=x+48;
        Ult_cidx=y+48;
        return true;
    }
    return false;
}


template <typename T>
char Ult_Board<T>::get_win(char& sym) {
    //cout<<Ult_ridx<<" "<<Ult_cidx<<" "<<endl;
    sym=this->board[Ult_ridx-48][Ult_cidx-48];
    //cout<<sym<<endl;
    return sym;
}

// Display the board and the pieces on it
template <typename T>
void Ult_Board<T>::display_board() {
    cout<<endl;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            //cout << "(" << i << "," << j << ")";
            if(this->board[i][j] == 'X' || this->board[i][j] == 'O') {
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

bool fla = false;

// Returns true if there is any winner
template <typename T>
bool Ult_Board<T>::is_win() {
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
bool Ult_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Ult_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

template <typename T>
Ult_Player<T>::Ult_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Ult_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces:";
    cin >> x >> y;
}

template <typename T>
Ult_Random_Player<T>::Ult_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  
}

template <typename T>
void Ult_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 3;  
    y = rand() % 3;
}

#endif 
