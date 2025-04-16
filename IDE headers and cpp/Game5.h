#ifndef T2_5_NUMERICAL_TIC_TAC_TOE_H
#define T2_5_NUMERICAL_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"

template <typename T>
class Game5 :public Board<T> {
protected:
    vector<char> vec_odd = { '1', '3', '5', '7', '9' };
    vector<char> vec_even = { '2', '4', '6','8' };
public:
    Game5();
    T* operator[](T index);
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int get_n_moves() const { return this->n_moves; }
    vector<char>& get_vec_even() { return vec_even; }
    vector<char>& get_vec_odd() { return vec_odd; }
};

template <typename T>
class Game5_player : public Player<T> {
public:
    Game5_player(string name, T symbol);
    void getmove(int& x, int& y);
    char getsymbol() { return this->symbol; }

};


template <typename T>
class Game5_Random_Player : public RandomPlayer<T> {
    Game5<T>* game;  // Pointer to the game instance to access vec_odd and vec_even
public:
    void getmove(int& x, int& y) override;
    void SetBoardPtr(Game5<T>* boartPtr);
    Game5_Random_Player(T symbol);
    T get_random_number();  // Randomly choose a number from available vec_odd/vec_even
};



//---------------------------------------IMPLEMENTATION----------------------------------------------

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template <typename T>
Game5<T>::Game5() {
    this->rows = 3;
    this->columns = 3;
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
T* Game5<T>::operator[](T index) {
    if (index < 0 || index >= this->rows) {
        throw out_of_range("Index out of range");
    }
    return this->board[index];
}

template <typename T>
bool Game5<T>::update_board(int x, int y, T mark) {
    // Handle player input
    if (this->n_moves % 2 == 0) {  // Even turn: player 1 or random even-numbered player
        if (mark == 0) {
            cout << "\nPlayer 1, you have canceled your move.\n";
            this->n_moves--;
            return true; // Cancelling a move doesn't change the board
        }
        cout << "\nPlayer 1, Enter an even number (2, 4, 6, 8): ";
        do {
            cin >> mark;
            if (mark % 2 != 0)
                cout << "Invalid choice. Enter an even number: ";
            cout << endl;
        } while (mark % 2 != 0);
    }
    else {  // Odd turn: player 2 or random odd-numbered player
        if (mark == 0) {
            cout << "\nPlayer 2, you have canceled your move.\n";
            this->n_moves--;
            return true; // Cancelling a move doesn't change the board
        }
        cout << "\nPlayer 2, Enter an odd number (1, 3, 5, 7, 9): ";
        do {
            cin >> mark;
            if (mark % 2 == 0)
                cout << "Invalid choice. Enter an odd number: ";
        } while (mark % 2 == 0);
    }

    // Convert mark to uppercase
    mark = static_cast<char>(toupper(mark));

    // Remove mark from the appropriate vector
    auto it_odd = find(vec_odd.begin(), vec_odd.end(), mark);
    if (it_odd != vec_odd.end()) {
        vec_odd.erase(it_odd);
    }
    auto it_even = find(vec_even.begin(), vec_even.end(), mark);
    if (it_even != vec_even.end()) {
        vec_even.erase(it_even);
    }

    // Validate if the board space is free and within bounds
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = mark;  // Update the board with the player's mark
        return true;
    }

    return false;
}



template <typename T>
void Game5<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            // Check if the current element is a digit
            if (std::isdigit(this->board[i][j])) {
                cout << this->board[i][j] << " ";
            }
            else {
                cout << "- ";
            }
        }
        cout << endl; // Move to the next row
    }
}

template <typename T>
bool Game5<T>::is_win() {
    // Check rows for a sum of 15
    for (int i = 0; i < this->rows; i++) {
        int rowSum = 0;
        for (int j = 0; j < this->columns; j++) {
            rowSum += this->board[i][j] - '0';  // Convert char to int by subtracting '0'
        }
        if (rowSum == 15) {
            return true;
        }
    }

    // Check columns for a sum of 15
    for (int i = 0; i < this->columns; i++) {
        int colSum = 0;
        for (int j = 0; j < this->rows; j++) {
            colSum += this->board[j][i] - '0';  // Convert char to int by subtracting '0'
        }
        if (colSum == 15) {
            return true;
        }
    }

    // Check main diagonal (top-left to bottom-right) for a sum of 15
    int mainDiagonalSum = 0;
    for (int i = 0; i < this->rows; i++) {
        mainDiagonalSum += this->board[i][i] - '0';  // Convert char to int by subtracting '0'
    }
    if (mainDiagonalSum == 15) {
        return true;
    }

    // Check anti-diagonal (top-right to bottom-left) for a sum of 15
    int antiDiagonalSum = 0;
    for (int i = 0; i < this->rows; i++) {
        antiDiagonalSum += this->board[i][this->columns - i - 1] - '0';  // Convert char to int by subtracting '0'
    }
    if (antiDiagonalSum == 15) {
        return true;
    }

    return false;

}

// Return true if 9 moves are done and no winner
template <typename T>
bool Game5<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Game5<T>::game_is_over() {
    return is_win() || is_draw();
}


template <typename T>
Game5_player<T>::Game5_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Game5_player<T>::getmove(int& x, int& y) {
    if(this->getsymbol() == 'X')
        cout << "\nPlayer 1 enter your move x and y (0 to 2) separated by spaces: ";
	else
		cout << "\nPlayer 2 enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}


template <typename T>
Game5_Random_Player<T>::Game5_Random_Player(T symbol)
    : RandomPlayer<T>(symbol), game(nullptr) {  // Initialize game as nullptr
    this->dimension = 3;
    this->name = "Random Computer Player";
}


template <typename T>
T Game5_Random_Player<T>::get_random_number() {
    if (this->symbol == 'O') {  // AI player only plays odd numbers
        if (this->game->get_n_moves() % 2 == 0 && !this->game->get_vec_odd().empty()) {
            auto& odd = this->game->get_vec_odd();
            int index = rand() % odd.size();
            T num = odd[index];
            odd.erase(odd.begin() + index);  // Remove the used number
            return num;  // Return an odd number
        }
    }
    return 0;  // No valid move found
}



template <typename T>
void Game5_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;

    // Find an available cell (empty cell)
    while ((*this->game)[x][y] != 0) {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }

    T mark = get_random_number();  // Get a valid number (odd or even based on turn)
    if (mark != 0) {
        cout << this->name << " placed " << mark << " at (" << x << ", " << y << ")\n";
        this->game->update_board(x, y, mark); // Update board with random move
    }
}



template <typename T>
void Game5_Random_Player<T>::SetBoardPtr(Game5<T>* boartPtr) {
    this->game = boartPtr;
}




#endif //T2_5_NUMERICAL_TIC_TAC_TOE_H