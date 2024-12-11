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

// enumeracja dla wyniku sprawdzania stanu planszy;
// NO -- brak rozstrzygnięcia,
// TIE -- remis;
// wygrane O i X są sygnalizowane za pomocą wartości z enumeracji Square
enum Result {
    NO,
    TIE = -1
};

// plansza
int board[BOARD_SIZE][BOARD_SIZE] = {Square::EMPTY};

// funkcja rysująca planszę
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

// funkcja sprawdzająca stan planszy
// zwraca jedną z czterech wartości: NO, TIE, O albo X
Result check()
{
    // sprawdzanie, czy są jeszcze puste pola;
    // zakładamy, że nie
    bool has_empty = false;

    // pętla przechodząca trzy razy (dokładniej: BOARD_SIZE)
    for (int i=0; i<BOARD_SIZE; i++) {
        // wiersze
        if (board[i][0] != Square::EMPTY) 
            if ((board[i][0] == board[i][1]) && (board[i][0] == board[i][2]))
                return (Result)board[i][0];
        // kolumny
        if (board[0][i] != Square::EMPTY) 
            if ((board[0][i] == board[1][i]) && (board[0][i] == board[2][i]))
                return (Result)board[0][i];

        // przekątne
        if (i == 1 && board[1][1] != Square::EMPTY) {
            if ((board[1][1] == board[0][0]) && (board[1][1] == board[2][2]))
                return (Result)board[1][1];
            if ((board[1][1] == board[2][0]) && (board[1][1] == board[0][2]))
                return (Result)board[1][1];
        }

        // sprawdzenie pustych
        for (int j=0; j<BOARD_SIZE; j++) {
            if (board[i][j] == Square::EMPTY)
                has_empty = true; // znalezione puste!
        }
        //// zoptymalizowana wersja sprawdzania pustych
        //// (do zastanowienia: znajdźcie różnicę)
        // for (int j=0; !has_empty && j<BOARD_SIZE; j++) {
        //     if (board[i][j] == Square::EMPTY)
        //         has_empty = true;
        // }
    }

    if (has_empty)
        return Result::NO;
    else
        return Result::TIE;

    //// to samo ^^^ można zrealizować z wykorzystaniem ternary operator:
    // return (has_empty) ? Result::NO : Result::TIE;
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

        Result res = check();
        if (res != Result::NO) {
            cout << "\n\n";
            if (res == Result::TIE) {
                cout << "*********\n"
                        "* Remis *\n"
                        "*********\n";
            }
            else {
                cout << "************************************\n"
                        "* Gra zakończyła się zwycięstwem " <<
                        ((res == (Result)Square::O) ? "O" : "X") << " *\n"
                        "************************************\n";
                // dwie linijki wyżej ^^^ zastosowałem tzw. ternary operator
            }
            break;
        }


        // // ruch komputera
        // // komputer nie ma strategii: losuje współrzędne;

        // // pętla powtarzająca losowanie w przypadku strzału w zajęte pole 
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