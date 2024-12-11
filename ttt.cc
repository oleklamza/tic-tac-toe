#include <iostream>
using namespace std;

#define BOARD_SIZE 3

// enumeracja przechowująca wartości pól planszy;
// dzięki niej w kodzie posługujemy się symbolami,
// a nie tajemniczymi liczbami (magic numbers!)
enum Square {
    EMPTY,
    O,
    X
};

// plansza
int board[BOARD_SIZE][BOARD_SIZE] = {Square::EMPTY};

// rysowanie planszy przeniesione do funkcji
void draw()
{   
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
}

int main()
{
    // inicjalizacja generatora liczb pseudolosowych
    // potrzebnego do losowania pola
    srand(time(nullptr));
    // wywołanie funkcji rysującej planszę
    cout << ">>> Kółko i krzyżyk <<<\n";
    draw();

    // pętla rund
    while (true) {
        // ruch gracza
        // użytkownik podaje współrzędne jako łańcuch <kolumna><wiersz>, np. a2
        
        // pętla wprowadzania współrzędnych
        int col, row;
        while (true) {
            cout << "\nPodaj współrzędne: ";
            string s;
            cin >> s;
            // sprawdzenie poprawności wprowadzonych danych
            // jeżeli są niepoprawne, pętla while wykonuje ponowną iterację
            // jeżeli są poprawne, wyskakujemy z pętli (break)
            if (s.length() == 2) {
                col = s[0] - 'a';
                row = s[1] - '1';

                if ( (col >= 0 && col <= 2) && (row >= 0 && row <= 2) )
                    break;
            }
            cout << "Niepoprawne współrzędne. Ma być [a-c][1-3].\n";
        }
        
        // ustawienie pola i narysowanie planszy
        board[row][col] = Square::O;
        draw();

        // ruch komputera
        // komputer nie ma strategii: losuje współrzędne;
        
        // pętla powtarzająca losowanie w przypadku strzału w zajęte pole 
        do {
            col = rand() % 3;
            row = rand() % 3;
        } while (board[row][col] != Square::EMPTY);
        // wyświetlenie komunikatu o wylosowanych współrzędnych
        cout << "\nKomputer:" << char(col + 'a') << char(row + '1') << endl;

        // ustawienie pola i narysowanie planszy
        board[row][col] = Square::X;
        draw();

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }

    return 0;
}