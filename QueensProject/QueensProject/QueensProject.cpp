#include <iostream>
using namespace std;
int const commandSize=20;
int const maxSizeOfBoard = 15;
char** createMatrix(int n, int m) {
    char** matrix = new char* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new char[m];
        for (int j = 0; j < m; j++) {
            matrix[i][j] = '0';
        }
    }
    return matrix;
}
void printMatrix(int n, int m, char** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void deleteMatrix(int n, char** matrix) {
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
void freePlaces(char** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '0') {
                cout << "(" << i << ", " << j << ") ";
            }
        }
    }
    cout << endl;
}
void playOnPlace(char**matrix,int N,int M, int x,int y,char&turn) {
    if (matrix[x][y] != '0') {
        cout << "This place is taken";
    }
    else {
        matrix[x][y] = turn;
        for (int i = 0;i < N;i++) {
            if (i != x) {
                matrix[i][y] = '*';
            }
        }
        for (int i = 0;i < M;i++) {
            if (i != y) {
                matrix[x][i] = '*';
            }
        }
        int i, j;

        i = x - 1; j = y - 1;
        while (i >= 0 && j >= 0) matrix[i--][j--] = '*';

        i = x + 1; j = y + 1;
        while (i < N && j < M) matrix[i++][j++] = '*';

        i = x - 1; j = y + 1;
        while (i >= 0 && j < M) matrix[i--][j++] = '*';

        i = x + 1; j = y - 1;
        while (i < N && j >= 0) matrix[i++][j--] = '*';

    }
    if (turn == '1') {
        turn = '2';
    }
    else {
        turn = '1';
    }
}
int main()
{
    cout << "Welcome to the game \"Queens\"" << endl << endl;
    cout << "Enter command: ";
    char command[commandSize];
    cin >> command;
    int N = 0, M = 0;
    char** matrix = nullptr;
    char turn = '1';
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
                matrix = createMatrix(n, m);
                N = n;
                M = m;
                printMatrix(n, m, matrix);

            }
            cout << "Enter new command: ";
            cin >> command;
        }
        else if (myStrcmp(command, "play")) {
            if (matrix == nullptr) {
                cout << "No board. Use 'new' first." << endl;
            }
            else {
                cout << "Enter place on board(row col): ";
                int x, y;
                cin >> x >> y;
                if ((x < 0 || x >= N) || (y < 0 || y >= M)) {
                    cout << "The coordinates must be in the interval [0," << N << "] and [0," << M << "]" << endl;
                }
                else {
                    playOnPlace(matrix,N,M,x,y,turn);
                }
            }
            cout << "Enter new command: ";
            cin >> command;
            
            
        }
        else if (myStrcmp(command, "free")) {
             freePlaces(matrix, N, M);
             cout << "Enter new command: ";
             cin >> command;
        }
        else if (myStrcmp(command, "show")) {
           printMatrix(N, M, matrix);
           cout << "Enter new command: ";
           cin >> command;
        }
        else if (myStrcmp(command, "save")) {

        }
        else if (myStrcmp(command, "load")) {

        }
        else if (myStrcmp(command, "turn")) {
            cout << "Player: " << turn << " is now" << endl;
            cout << "Enter new command: ";
            cin >> command;
        }
        else if (myStrcmp(command, "help")) {
            printHelp();
            cout << "Enter new command: ";
            cin >> command;
        }
        else if (myStrcmp(command, "back")){}
        else if (myStrcmp(command, "history")){
        
        
        }
        else if (myStrcmp(command, "exit")) {
            return 0;
        }
        else {
            cout << "This command was not valid"<<endl;
            cout << "Enter new command: ";
            cin >> command;
        }




    }
    return 0;
}



