# Tic_Tac_Toe_Game

# Tic-Tac-Toe Games Project

A comprehensive C++ project featuring classic and advanced Tic-Tac-Toe variants, word-based games, and modular AI/human player support. This README provides a detailed overview, game rules, instructions, and technical structure for easy understanding and extension.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Game Types Included](#game-types-included)
  - [1. Classic Tic-Tac-Toe](#1-classic-tic-tac-toe)
  - [2. Word Tic-Tac-Toe](#2-word-tic-tac-toe)
  - [3. Ultimate Tic-Tac-Toe](#3-ultimate-tic-tac-toe)
  - [4. Other Variants (Extendable)](#4-other-variants-extendable)
- [How to Play Each Game](#how-to-play-each-game)
- [Project Structure](#project-structure)
- [How to Build and Run](#how-to-build-and-run)
- [How to Extend](#how-to-extend)
- [Sample Console Output](#sample-console-output)
- [Credits](#credits)
- [License](#license)

---

## Project Overview

This project is a modular C++ framework for building and playing various Tic-Tac-Toe and board game variants. It supports both human and AI players and is designed for easy extension to new game types. Word-based games are supported via an included dictionary of three-letter English words.

---

## Game Types Included

### 1. Classic Tic-Tac-Toe

- **Board:** 3x3 grid.
- **Players:** Two (X and O), human or AI.
- **Goal:** First to align three of their marks horizontally, vertically, or diagonally wins.
- **Draw:** If all cells are filled and no winner.

### 2. Word Tic-Tac-Toe

- **Board:** 3x3 grid.
- **Players:** Two, each placing a letter per turn.
- **Goal:** Form a valid three-letter English word (row, column, or diagonal) using the provided `dic.txt` dictionary.
- **Draw:** If no valid word is formed and the board is full.

### 3. Ultimate Tic-Tac-Toe

- **Board:** 3x3 grid of 3x3 sub-grids.
- **Players:** Two, alternating turns.
- **Goal:** Win three sub-grids in a line on the meta-board. Each move determines the sub-grid for the next player.
- **Draw:** If all sub-grids are filled with no meta-winner.

### 4. Other Variants (Extendable)

- **Misère Tic-Tac-Toe:** The player who completes three in a row **loses**.
- **Numerical Tic-Tac-Toe:** Players place numbers; win by making 15 in a line.
- **Connect Four, 5x5 Tic-Tac-Toe, and more:** Easily implemented with the provided templates.

---

## How to Play Each Game

### Classic Tic-Tac-Toe

1. Start the game; choose player types (human or AI).
2. Players take turns entering the row and column for their move.
3. The board updates after each move.
4. The first to align three marks wins; if the board fills with no winner, it's a draw.

### Word Tic-Tac-Toe

1. Start the game; each player enters a letter on their turn.
2. The board updates after each move.
3. After every move, the game checks if any row, column, or diagonal forms a valid word (using `dic.txt`).
4. The first to form a valid word wins; if the board fills with no valid word, it's a draw.

### Ultimate Tic-Tac-Toe

1. Start the game; the first player can play anywhere.
2. Each move determines the sub-grid for the next player's move.
3. Win three sub-grids in a row on the meta-board to win the game.
4. If all sub-grids are filled with no winner, it's a draw.

---

## Project Structure

| File                   | Description                                                                                      |
|------------------------|--------------------------------------------------------------------------------------------------|
| `BoardGame_Classes.h`  | Core engine: templates for `Board`, `Player`, `RandomPlayer`, and `GameManager`                  |
| `dic.txt`              | Dictionary of valid three-letter English words for word-based variants                           |
| `main.cpp`             | (Not included) Entry point—instantiates games, boards, and players                              |
| *Other files*          | (Not included) Implement specific games and players by inheriting from the base classes          |

### `BoardGame_Classes.h` Highlights

- **`Board`**: Abstract base for all board types. Handles board state, move validation, and win/draw logic.
- **`Player`**: Abstract base for all player types (human/AI). Handles player identity and move selection.
- **`RandomPlayer`**: AI player that generates random valid moves.
- **`GameManager`**: Runs the game loop, alternates turns, checks for win/draw, and displays results.

### `dic.txt` Usage

- Contains a list of valid three-letter English words (one per line).
- Used in word-based variants to check if a word has been formed.

---

## How to Build and Run

1. **Clone the repository** and add your `main.cpp`.
2. **Compile** (example using g++):
   
   g++ main.cpp -o tictactoe -std=c++17
   
3. **Run**:
   
   ./tictactoe
   
4. **Follow prompts** to select the game variant and play.

---

## How to Extend

To add a new game variant:

1. **Define a Board Class**
   - Inherit from `Board`.
   - Implement required methods: `update_board`, `display_board`, `is_win`, `is_draw`, `game_is_over`.

2. **Define Player Classes**
   - Inherit from `Player` or `RandomPlayer`.
   - Implement `getmove(int& x, int& y)` for move logic.

3. **Update `main.cpp`**
   - Instantiate your custom board and player objects.
   - Use `GameManager` to run the game.

---

## Sample Console Output

### Classic Tic-Tac-Toe


Current Board:
X | O | X
---------
O | X |  
---------
  | O | X

Player X's turn.
Enter row and column:


### Word Tic-Tac-Toe


Current Board:
C | A | T
---------
D | O | G
---------
   |   |   

Player 2's turn. Enter a letter and position:
Word formed: CAT! Player 1 wins!

---

> **Tip:** For word-based games, reference dic.txt to validate words formed on the board.  

---
