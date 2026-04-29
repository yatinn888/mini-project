#include <iostream>
using namespace std;
class Board {
private:
    char grid[3][3];

public:
    
    Board() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                grid[i][j] = ' ';
    }

    
    void print() const {
        cout << "\nBoard:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ')
                    cout << " " << i << j;          
                else
                    cout << " " << grid[i][j] << " ";
                if (j < 2) cout << "|";
            }
            cout << "\n";
            if (i < 2) cout << "---+---+---\n";
        }
        cout << "\n";
    }

    
    bool placeMarker(int row, int col, char marker) {
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            cout << "Invalid position! Try again.\n";
            return false;
        }
        if (grid[row][col] != ' ') {
            cout << "Position already taken! Try again.\n";
            return false;
        }
        grid[row][col] = marker;
        return true;
    }

    
    bool hasWon(char marker) const {
        for (int i = 0; i < 3; i++) {
            
            if ((grid[i][0] == marker && grid[i][1] == marker && grid[i][2] == marker) ||
                (grid[0][i] == marker && grid[1][i] == marker && grid[2][i] == marker))
                return true;
        }
        
        return (grid[0][0] == marker && grid[1][1] == marker && grid[2][2] == marker) ||
               (grid[0][2] == marker && grid[1][1] == marker && grid[2][0] == marker);
    }

    
    bool isFull() const {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] == ' ') return false;
        return true;
    }
};

class Player {
private:
    string name;
    char   marker;

public:
  
    Player(const string& playerName, char playerMarker)
        : name(playerName), marker(playerMarker) {}

    char        getMarker() const { return marker; }
    const string& getName() const { return name;   }


    void getMove(int& row, int& col) const {
        cout << name << " (" << marker << "), enter row and column"
             << " (e.g. 1 2 for position 12): ";
        cin >> row >> col;
    }
};


class Game {
private:
    Board  board;               
    Player players[2];         
    int    currentPlayerIndex;  
    
    public:
    Game()
        : players{ Player("Player 1", 'X'), Player("Player 2", 'O') },
          currentPlayerIndex(0) {}

    const Player& currentPlayer() const {
        return players[currentPlayerIndex];
    }

    void switchPlayer() {
        currentPlayerIndex = 1 - currentPlayerIndex;
    }

  
    void play() {
        bool gameOver = false;

        while (!gameOver) {
            board.print();

            int row, col;
            currentPlayer().getMove(row, col);

            
            if (!board.placeMarker(row, col, currentPlayer().getMarker()))
                continue;

            if (board.hasWon(currentPlayer().getMarker())) {
                board.print();
                cout << currentPlayer().getName() << " ("
                     << currentPlayer().getMarker() << ") wins!\n";
                gameOver = true;
            } else if (board.isFull()) {
                board.print();
                cout << "The game is a tie!\n";
                gameOver = true;
            } else {
                switchPlayer();
            }
        }
    }
};

int main() {
    Game game;   
    game.play();
    return 0;
}