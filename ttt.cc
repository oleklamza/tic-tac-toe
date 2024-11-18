#include <iostream>
using namespace std;

#define BOARD_SIZE 3

enum Square {
    EMPTY,
    O,
    X
};


int main()
{
    // plansza
    int board[BOARD_SIZE][BOARD_SIZE] = {Square::EMPTY};

    // przykładowe wypełnienie planszy
    board[0][1] = Square::O;
    board[2][1] = Square::X;

    // rysowanie planszy
    cout << "  a b c\n";
    for (int row=0; row<BOARD_SIZE; row++) {
        cout << row+1 << " ";
        for (int col=0; col<BOARD_SIZE; col++) {
            char c = '-';
            int sq = board[row][col]; 

            if (sq == Square::O) {
                c = 'O';
            }
            else if (sq == Square::X) {
                c = 'X';
            }

            cout << c << " ";
        }
        cout << "\n";
    }

    return 0;
}