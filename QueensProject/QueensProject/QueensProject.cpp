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
    cout << "new    - start new game with size N x M" << endl;
    cout << "play   - place queen at (x, y)" << endl;
    cout << "free   - show all valid cells" << endl;
    cout << "show   - visualize board" << endl;
    cout << "save   - save current state" << endl;
    cout << "load   - load state from file" << endl;
    cout << "turn   - show whose turn it is" << endl;
    cout << "help   - show this menu" << endl;
    cout << "exit   - exit program" << endl;
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
void playOnPlace(char**matrix,int N,int M, int x,int y,char&turn, int*history,int* historyCounter,int*lastChecked,int *lastCounter) {
    if (matrix[x][y] != '0') {
        cout << "This place is taken"<<endl;
    }
    else {
        *lastCounter = 0;
        matrix[x][y] = turn;
        for (int i = 0;i < N;i++) {
            if (i != x && matrix[i][y] == '0') {
                matrix[i][y] = '*';
                lastChecked[(*lastCounter)++] = i;
                lastChecked[(*lastCounter)++] = y;
            }
        }
        for (int i = 0;i < M;i++) {
            if (i != y && matrix[x][i] == '0') {
                matrix[x][i] = '*';
                lastChecked[(*lastCounter)++] = x;
                lastChecked[(*lastCounter)++] = i;
            }
        }
        int i, j;
        i = x - 1; j = y - 1;
        while (i >= 0 && j >= 0) {
            if (matrix[i][j] == '0') {
                matrix[i][j] = '*';
                lastChecked[(*lastCounter)++] = i;
                lastChecked[(*lastCounter)++] = j;
            }
            i--; j--;
        }

        i = x + 1; j = y + 1;
        while (i < N && j < M) {
            if (matrix[i][j] == '0') {
                matrix[i][j] = '*';
                lastChecked[(*lastCounter)++] = i;
                lastChecked[(*lastCounter)++] = j;
            }
            i++; j++;
        }

        i = x - 1; j = y + 1;
        while (i >= 0 && j < M) {
            if (matrix[i][j] == '0') {
                matrix[i][j] = '*';
                lastChecked[(*lastCounter)++] = i;
                lastChecked[(*lastCounter)++] = j;
            }
            i--; j++;
        }
        i = x + 1; j = y - 1;
        i = x + 1; j = y - 1;
        while (i < N && j >= 0) {
            if (matrix[i][j] == '0') {
                matrix[i][j] = '*';
                lastChecked[(*lastCounter)++] = i;
                lastChecked[(*lastCounter)++] = j;
            }
            i++; j--;
        }

        history[*historyCounter] = x;
        (*historyCounter)++;
        history[*historyCounter] = y;
        (*historyCounter)++;
    }
    if (turn == '1') {
        turn = '2';
    }
    else {
        turn = '1';
    }
}
void historyPrint(int historyCounter,int*history,char player) {
    for (int i = 0;i < historyCounter;i += 2) {
        cout << "P" << player << "->" << "(" << history[i] << ',' << history[i] << ")" << endl;
        if (player == '1') {
            player = '2';
        }
        else {
            player = '1';
        }
    }
}
void backFunction(int &lastCounter,char**matrix,int*lastChecked,int*history,char&turn,int&historyCounter) {
    if (historyCounter < 2) {
        cout << "No moves to undo." << endl;
        return;
    }
    else {
        for (int i = 0; i < lastCounter; i += 2) {
            matrix[lastChecked[i]][lastChecked[i + 1]] = '0';
        }
        int y = history[historyCounter - 1];
        int x = history[historyCounter - 2];
        matrix[x][y] = '0';
        historyCounter -= 2;
        if (turn == '1') {
            turn = '2';
        }
        else {
            turn = '1';
        }
    }
}

int main()
{
    cout << "Welcome to the game \"Queens\"" << endl << endl;
    cout << "These are all commands in the game:" << endl;
    printHelp();
    cout << endl;
    cout << "Enter command: ";
    char command[commandSize];
    cin >> command;
    int N = 0, M = 0;
    char** matrix = nullptr;
    int* history = nullptr;
    int historyCounter = 0;
    char turn = '1';
    char player = '1';
    int* lastChecked = nullptr;
    int lastCounter = 0;
    while (myStrcmp(command, "end") == false) {
        char ch;
        bool hasExtra = false;
        while (cin.get(ch) && ch != '\n') {
            if (ch != ' ' && ch != '\t') {
                hasExtra = true;
            }
        }

        if (hasExtra) {
            cout << "Invalid command" << endl;
            cout << "Enter new command: ";
            cin >> command;
            continue;
        }
        if (myStrcmp(command, "new")) {
            int n, m;
            while (true) {
                cout << "Enter size of the board: ";

                if (!(cin >> n >> m)) {
                    cout << "Invalid input. Enter two integers." << endl;
                    cin.clear();
                    char ch;
                    while (cin.get(ch) && ch != '\n');
                    continue;
                }

                if (n < 1 || n > maxSizeOfBoard || m < 1 || m > maxSizeOfBoard) {
                    cout << "N and M must be in the interval [1,15]" << endl;
                    continue;
                }
                else {
                    cout << "Board " << n << "x" << m << endl;
                    matrix = createMatrix(n, m);
                    N = n;
                    M = m;
                    history = new int[N * M * 2];
                    lastChecked = new int[N * M * 2];
                    printMatrix(n, m, matrix);

                }
                break;
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
                    playOnPlace(matrix,N,M,x,y,turn,history,&historyCounter,lastChecked,&lastCounter);
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
        else if (myStrcmp(command, "back")) {   
            backFunction(lastCounter, matrix, lastChecked, history, turn, historyCounter);
            
            cout << "Enter new command: ";
            cin >> command;
            
        }
        else if (myStrcmp(command, "history")) {     
            historyPrint(historyCounter, history, player);
            cout << "Enter new command: ";
            cin >> command;

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



