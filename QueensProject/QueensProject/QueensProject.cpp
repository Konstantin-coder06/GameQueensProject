#include <iostream>
using namespace std;
int const commandSize=20;
int const maxSizeOfBoard = 15;
int** createMatrix(int n, int m) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m] {0};
    }
    return matrix;
}
void printMatrix(int n, int m, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void deleteMatrix(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
void printHelp() {
    cout << "Commands:" << endl;
    cout << "new N M       - start new game with size N x M" << endl;
    cout << "play x y      - place queen at (x, y)" << endl;
    cout << "free          - show all valid cells" << endl;
    cout << "show          - visualize board" << endl;
    cout << "save file.txt - save current state" << endl;
    cout << "load file.txt - load state from file" << endl;
    cout << "turn          - show whose turn it is" << endl;
    cout << "help          - show this menu" << endl;
    cout << "exit          - exit program" << endl;
}
bool myStrcmp(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    return a[i] == b[i]; 
}
int main()
{
    cout << "Welcome to the game \"Queens\"" << endl << endl;
    cout << "Enter command: ";
    char command[commandSize];
    cin >> command;
    while (myStrcmp(command, "end") == false) {
        if (myStrcmp(command, "new")) {
            cout << "Enter size of the board: ";
            int n, m;
            cin >> n >> m;
            if ((n<1 || n>maxSizeOfBoard) || (m<1 || m>maxSizeOfBoard)) {
                cout << "N and M must be in the interval [1,15]" << endl;
              
            }
            else {
                cout << "Board " << n << "x" << m << endl;
                int** matrix = createMatrix(n, m);
                printMatrix(n, m, matrix);
            }
            cout << "Enter new command: ";
            cin >> command;
        }
        if (myStrcmp(command, "play")) {

        }
        if (myStrcmp(command, "free")) {

        }
        if (myStrcmp(command, "show")) {
           // printMatrix(n, m, matrix);
        }
        if (myStrcmp(command, "save")) {

        }
        if (myStrcmp(command, "load")) {

        }
        if (myStrcmp(command, "turn")) {

        }
        if (myStrcmp(command, "help")) {
            printHelp();
        }
        if (myStrcmp(command, "exit")) {
            return 0;
        }




    }
    return 0;
}



