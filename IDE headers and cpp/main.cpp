#include <iostream>
#include "BoardGame_Classes.h"
#include "sus.h"
#include "TicTaceToe5×5.h"
#include "pyramic.h"
#include "words.h"
#include "misere_game.h"
#include "ultimate.h"
#include "Ult_helper.h"
#include "Game2.h"
#include "Game5.h"
#include <algorithm>
bool check_number_in_set(vector <string>& , string );
using namespace std;

int main() {
    int Playagain;
    bool firstgame = true;
      

    while (true) {
        if (!firstgame) {
            cout << "\nDo you want to play again ?\n" << "1 -> yes , 0 -> no : ";
            cin >> Playagain;
            if (Playagain != 1)
            {
                cout << "\nSee you later , Good Gamers!";
                return 0;
            }
        }
        //for each board at the Ultimate game there is a game manager of course :D
        GameManager<char>* gameManagers[9];
        Ult_Board<char>* boards[9];
        X_O_Board<char>* mini_matrix = new X_O_Board<char>;
        firstgame = false;
        int choice;
        Player<char>* players[2];
        Board<char>* boardPtr = nullptr;  // Pointer to the board, used for all games
        string playerXName, player2Name;
        system("cls");
        if(firstgame)
            cout << "Welcome to FCAI X-O Game.\n";

        cout << "Choose the game you want to play:\n";
        cout << "1. Pyramic\n";
        cout << "2. Four-in-a-row\n";
        cout << "3. 5*5 \n";
        cout << "4. Words\n";
        cout << "5. Numerical Game\n";
        cout << "6. Misere\n";
        cout << "7. Ultimate\n";
        cout << "8. Sus\n";
        cin >> choice;
        system("cls");
        int playerchoice = choice;
        // Create the board based on the selected game
        switch (choice) {
        case 8:
            boardPtr = new sus<char>();
            break;
        case 1:
            /*
                        Pyramic Board indices are as follows:

                             {2, 2}
                      {3,1}, {3 ,2}, {3, 3},
                   {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}
            */
            boardPtr = new Pyramic_Board<char>();
            break;
        case 4:
            boardPtr = new Word_Board<char>();
            break;
        case 6:
            boardPtr = new Mis_Board<char>();
            break;
        case 7:
            boardPtr = new Ult_Board<char>();
            break;
        case 3:
            boardPtr = new Game3<char>();
            break;
        case 2:
            boardPtr = new Game2<char>();
            break;
        case 5:
            boardPtr = new Game5<char>();
            break;
        default:
            cout << "Invalid game choice. Exiting the game.\n";
            return 1;
        }

        // Set up player 1
        cout << "Enter Player X name: ";
        cin >> playerXName;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            switch (playerchoice)
            {
            case 8:
                players[0] = new sus_Player<char>(playerXName, 'S');
                break;
            case 1:
                players[0] = new Pyramic_Player<char>(playerXName, 'X');
                break;
            case 4:
                players[0] = new Word_Player<char>(playerXName, ' ');
                break;
            case 6:
                players[0] = new Mis_Player<char>(playerXName, 'X');
                break;
            case 7:
                players[0] = new Ult_Player<char>(playerXName, 'X');
                break;
            case 3:
                players[0] = new Game3player<char>(playerXName, 'X');
                break;
            case 2:
                players[0] = new Game2_player<char>(playerXName, 'X');
                break;
            case 5:
                players[0] = new Game5_player<char>(playerXName, 'X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
            }
            break;
        case 2:
            switch (playerchoice)
            {
            case 8:
                players[0] = new sus_Random_Player<char>('S');
                break;
            case 1:
                players[0] = new Pyramic_Random_Player<char>('X');
                break;
            case 4:
                players[0] = new Word_Random_Player<char>(' ');
                break;
            case 6:
                players[0] = new Mis_Random_Player<char>("Random computer player", 'X');
                break;
            case 7:
                players[0] = new Ult_Random_Player<char>('X');
                break;
            case 3:
                players[0] = new Game3RandomPlayer<char>('X');
                break;
            case 2:
                players[0] = new Game2_random_player<char>('X');
                break;
            case 5:
                cout << "Random plyer is only available at the Odd numbers only (for player 2).\n";
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
            }
            break;
        case 3:
            switch (playerchoice)
            {
            case 2:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
            case 8:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
            case 3:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
                break;
            case 6:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
            case 1:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
            case 4:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
            case 5:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
                break;
            case 7:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
                break;
            }
        default:
            cout << "Invalid choice for Player 1 Exiting the game.\n";
            return 1;
        }

        // Set up player 2
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            switch (playerchoice)
            {
            case 8:
                players[1] = new sus_Player<char>(player2Name, 'U');
                break;
            case 1:
                players[1] = new Pyramic_Player<char>(player2Name, 'O');
                break;
            case 4:
                players[1] = new Word_Player<char>(player2Name, ' ');
                break;
            case 6:
                players[1] = new Mis_Player<char>(player2Name, 'O');
                break;
            case 7:
                players[1] = new Ult_Player<char>(player2Name, 'O');
                break;
            case 3:
                players[1] = new Game3player<char>(player2Name, 'O');
                break;
            case 2:
                players[1] = new Game2_player<char>(player2Name, 'O');
                break;
            case 5:
                players[1] = new Game5_player<char>(player2Name, 'O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
            }
            break;
        case 2:
            switch (playerchoice)
            {
            case 8:
                players[1] = new sus_Random_Player<char>('U');
                break;
            case 1:
                players[1] = new Pyramic_Random_Player<char>('O');
                break;
            case 4:
                players[1] = new Word_Random_Player<char>(' ');
                break;
            case 6:
                players[1] = new Mis_Random_Player<char>( "Random Computer Player" ,  'O');
                break;
            case 7:
                players[1] = new Ult_Random_Player<char>('O');
                break;
            case 3:
                players[1] = new Game3RandomPlayer<char>('O');
                break;
            case 2:
                players[1] = new Game2_random_player<char>('O');
                static_cast<Game2_random_player<char>*>(players[1])->setBoardPointer(dynamic_cast<Game2<char>*>(boardPtr));
                break;
            case 5:
                players[1] = new Game5_Random_Player<char>('O');
                static_cast<Game5_Random_Player<char>*>(players[1])->SetBoardPtr(dynamic_cast<Game5<char>*>(boardPtr));
                break;
            default:
                cout << "Invalid choice for Player 2.. Exiting the game.\n";
                return 1;
            }
            break;
        case 3:
            switch (playerchoice)
            {
            case 2:
                players[1] = new Game2AiPlayer<char>('O');
                static_cast<Game2AiPlayer<char>*>(players[1])->setBoardPointer(dynamic_cast<Game2<char>*>(boardPtr));
				break;
            case 8 :
                players[1] = new SusAIPlayer<char>('U');
                static_cast<SusAIPlayer<char>*>(players[1])->setBoardPointer(dynamic_cast<sus<char>*>(boardPtr));
                break;
            case 3:
               cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
               cout << "Please Restart your game\n";
               return -1;
                break;
            case 6:
				players[1] = new MisAIPlayer<char>('O');
				static_cast<MisAIPlayer<char>*>(players[1])->setBoardPointer(dynamic_cast<Mis_Board<char>*>(boardPtr));
				break;
            case 1:
                players[1] = new PyramicAiPlayer<char>('O');
                static_cast<PyramicAiPlayer<char>*>(players[1])->setBoardPtr(dynamic_cast<Pyramic_Board<char>*>(boardPtr));
                break;
            case 4:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
                break;
            case 5:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
                break;
            case 7:
                cout << "THIS FUTURE IS NOT AVAILABLE YET\n";
                cout << "Please Restart your game\n";
                return -1;
                break;
            }
        break;
        default:
            cout << "Invalid choice for Player 2... Exiting the game.\n";
            return 1;
        }
        if (playerchoice == 6) {
            // Get player names using getname()
            string player1 = players[0]->getname();
            string player2 = players[1]->getname();

            // Swap the names
            swap(player1, player2);

            // Cast players to Mis_Player type and set the names if they are indeed of type Mis_Player
            Mis_Player<char>* misPlayer1 = static_cast<Mis_Player<char>*>(players[0]);
            Mis_Player<char>* misPlayer2 = static_cast<Mis_Player<char>*>(players[1]);
           

            // Ensure the cast is successful
            misPlayer1->setname(player1);
            misPlayer2->setname(player2);
        }

        //RUN Ultimate game explicitly
        if (playerchoice == 7) {

            for (int i = 0; i < 9; ++i) {
                boards[i] = new Ult_Board<char>();  // Initialize the boards before using them
                gameManagers[i] = new GameManager<char>(boards[i], players);
            }

            if (!mini_matrix) {
                mini_matrix = new X_O_Board<char>();  // Ensure mini_matrix is initialized
            }


            vector<string> num_mat = { "0", "1", "2" , "3" , "4" , "5" , "6" , "7" , "8" };
            for (int i = 0; i < 9; ++i) {
                gameManagers[i] = new GameManager<char>(boards[i], players);
            }

            // User selects which GameManager object to run
            while (num_mat.size() > 0) {

                for (int i = 1; i <= 9; ++i) {
                    cout << i - 1 << " ";
                    if (i % 3 == 0) {
                        cout << endl;
                    }
                }

                string game_manager_choice;
                cout << "Select which game instance to run (0-8):";
                cin >> game_manager_choice;
                char sym;
                if (check_number_in_set(num_mat, game_manager_choice)) {
                    gameManagers[stoi(game_manager_choice)]->run();
                    if (boards[stoi(game_manager_choice)]->is_win()) {
                        sym = boards[stoi(game_manager_choice)]->get_win(sym);
                    }
                    else {
                        sym = 'D';
                    }
                    mini_matrix->get(sym, stoi(game_manager_choice));
                    mini_matrix->display_board();
                    if (num_mat.size() < 7) {
                        if (mini_matrix->is_win()) {
                            if (sym == 'X') {
                                cout << "We have a winner, " << players[0]->getname() << " won in the ultimate matrix!" << endl;
                                break;
                            }
                            else {
                                cout << "We have a winner, " << players[1]->getname() << " won in the ultimate matrix!" << endl;
                                break;
                            }
                        }
                        else if (num_mat.size() == 0) {
                            cout << "We have a draw!" << endl;
                        }
                    }
                }
                else {
                    cout << "Invalid game instance choice. Exiting the game.\n";
                }
            }

            // Clean up delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            for (int i = 0; i < 9; ++i) {
                delete gameManagers[i];
            }

            return 0;
        }
  
        // Create the game manager and run the game
        GameManager<char> game(boardPtr, players);
        game.run();

        // Clean up
        delete boardPtr;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
        delete mini_matrix;
        firstgame = false;
    }
    return 0;
}


//NEEDED parts out of Headers 
bool check_number_in_set(vector <string>& set, string x) {
    for (int i = 0; i < set.size(); i++) {
        if (set[i] == x) {
            set.erase(remove(set.begin(), set.end(), x), set.end());
            return true;
        }
    }
    return false;
}

