//
// Created by Ahmed Waleed on 12/5/2024.
//

#ifndef WORDS_H
#define WORDS_H


#include <algorithm>
#include <vector>

#include "BoardGame_Classes.h"
#include <fstream>

template <typename T>
class Word_Board:public Board<T> {
public:
    Word_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Word_Player : public Player<T> {
public:
    Word_Player();
    Word_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class Word_Random_Player : public RandomPlayer<T>{
public:
    Word_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Word_Board<T>::Word_Board() {
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
int ridx;
int cidx;
int c;
char ch;
template <typename T>
bool Word_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    char s;
    cout<<"Enter symbol: ";
    cin >> s;
    mark = s;
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        c = mark ;
        ch = char(c);
        ridx = x;
        cidx = y;
        //cout<<ch<<endl;
        return true;

    }
    return false;
}


// Display the board and the pieces on it
template <typename T>
void Word_Board<T>::display_board() {
    cout<<endl;

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            //cout << "(" << i << "," << j << ")";
            if( this->board[i][j] != 0 ) {
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




























struct fourstrings {
    string h="";
    string v="";
    string rd="";
    string ld="";
};


bool compareStringWithFile(const string& filename, const string& target ) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line == target) {
            return true;
        }
    }

    return false;
}





// Returns true if there is any winner
template <typename T>
bool Word_Board<T>::is_win() {
    int rows = this->rows;
    int cols = this->columns;
    fourstrings result ;


    //horizontal string
    for(int i = 0; i < rows; i++) {
        result.h+=this->board[i][cidx];
    }
    // cout<<"Got it"<<endl;
    //vertical string
    for(int i = 0; i < cols; i++) {
        result.v+=this->board[ridx][i];
    }
    // cout<<"Got it"<<endl;



    //right diagonal string
    int rstart;
    int cstart;

    if (cidx == ridx  ){
        rstart = 0;
        cstart = 0;
    }
    else if(ridx>cidx){
        rstart = ridx-cidx;
        cstart = 0;
    }
    else {
        rstart = 0;
        cstart = cidx-ridx;
    }
    for(int i = 0; i < rows; i++) {
        if(rstart +i < rows && cstart + i < cols) {
            result.rd+=this->board[rstart+i][cstart+i];
        }
        else {
            break;
        }
    }
    // cout<<"Got it"<<endl;




    //left diagonal string
    int lrstart;
    int lcstart;
    if ((ridx + cidx ) == cols - 1){
        lrstart = 0;
        lcstart = cols-1;
    }
    else if((ridx + cidx ) < cols) {
        lrstart = 0;
        lcstart = (ridx + cidx) ;
    }
    else {
        lrstart =  (ridx + cidx) - (cols - 1);
        lcstart = cols-1;
    }
    for(int i = 0; i < rows; i++) {
        if(lrstart +i < rows && lcstart - i >= 0) {
            result.ld+=this->board[lrstart+i][lcstart-i];
        }
    }
    // cout<<"Got it"<<endl;





    string rh= result.h;
    reverse(rh.begin(), rh.end());
    string rv= result.v;
    reverse(rv.begin(), rv.end());
    string rrd= result.rd;
    reverse(rrd.begin(), rrd.end());
    string rld= result.ld;
    reverse(rld.begin(), rld.end());


    string filename = "dic.txt"; // Change this to your actual filename

    if(compareStringWithFile(filename, result.h) || compareStringWithFile(filename, rh )) {
        return true;
    }
    if(compareStringWithFile(filename, result.v) || compareStringWithFile(filename, rv )) {
        return true;
    }
    if(compareStringWithFile(filename, result.rd) || compareStringWithFile(filename, rrd)) {
        return true;
    }
    if(compareStringWithFile(filename, result.ld) || compareStringWithFile(filename, rld)) {
        return true;
    }
    return false;


}













































// Return true if 9 moves are done and no winner
template <typename T>
bool Word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Word_Player<T>::Word_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Word_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces:";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Word_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}









#endif //WORDS_H
