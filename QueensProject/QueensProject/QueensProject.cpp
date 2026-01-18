#include <iostream>
#include <fstream>
/**
*
* Solution to course project #06
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Konstantin Ivanov Mitkov
* @idnumber 0MI0600614
* @compiler VISUAL STUDIO
*/

using namespace std;
int const COMMAND_SIZE=20;
int const MAX_SIZE_OF_BOARD = 15;

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
    if (!matrix) {
        cout << "No board!" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void deleteMatrix(int n, char**& matrix) {
    if (!matrix) {
        return;
    }
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}
void printHelp() {
    cout << "Commands:" << endl;
    cout << "new     - start new game with size N x M" << endl;
    cout << "play    - place queen at (x, y)" << endl;
    cout << "free    - show all valid cells" << endl;
    cout << "show    - visualize board" << endl;
    cout << "save    - save current state" << endl;
    cout << "load    - load state from file" << endl;
    cout << "turn    - show whose turn it is" << endl;
    cout << "help    - show this menu" << endl;
    cout << "history - show the history of the game" << endl;
    cout << "back    - return the game one play back" << endl;
    cout << "exit    - exit program" << endl;
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
    if (!matrix) {
        cout << "No board" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '0') {
                cout << "(" << i << ", " << j << ") ";
            }
        }
    }
    cout << endl;
}
void markColumn(int N,int x, int y, char**matrix, int*lastChecked, int*lastCounter) {
    for (int i = 0;i < N;i++) {
        if (i != x && matrix[i][y] == '0') {
            matrix[i][y] = '*';
            lastChecked[(*lastCounter)++] = i;
            lastChecked[(*lastCounter)++] = y;
        }
    }
}
void markRow(int M, int x, int y, char** matrix, int* lastChecked, int* lastCounter) {
    for (int i = 0;i < M;i++) {
        if (i != y && matrix[x][i] == '0') {
            matrix[x][i] = '*';
            lastChecked[(*lastCounter)++] = x;
            lastChecked[(*lastCounter)++] = i;
        }
    }
}
void markMainDiagUp(int i, int j,int x,int y, char** matrix, int* lastChecked, int* lastCounter) {
    i = x - 1; j = y - 1;
    while (i >= 0 && j >= 0) {
        if (matrix[i][j] == '0') {
            matrix[i][j] = '*';
            lastChecked[(*lastCounter)++] = i;
            lastChecked[(*lastCounter)++] = j;
        }
        i--; j--;
    }
}
void markMainDiagDown(int M,int N, int i, int j, int x, int y, char** matrix, int* lastChecked, int* lastCounter) {
    i = x + 1; j = y + 1;
    while (i < N && j < M) {
        if (matrix[i][j] == '0') {
            matrix[i][j] = '*';
            lastChecked[(*lastCounter)++] = i;
            lastChecked[(*lastCounter)++] = j;
        }
        i++; j++;
    }
}
void markSecondDiagUp(int M, int i, int j, int x, int y, char** matrix, int* lastChecked, int* lastCounter) {
    i = x - 1; j = y + 1;
    while (i >= 0 && j < M) {
        if (matrix[i][j] == '0') {
            matrix[i][j] = '*';
            lastChecked[(*lastCounter)++] = i;
            lastChecked[(*lastCounter)++] = j;
        }
        i--; j++;
    }
}
void markSecondDiagDown(int N, int i, int j, int x, int y, char** matrix, int* lastChecked, int* lastCounter) {
    i = x + 1; j = y - 1;
    while (i < N && j >= 0) {
        if (matrix[i][j] == '0') {
            matrix[i][j] = '*';
            lastChecked[(*lastCounter)++] = i;
            lastChecked[(*lastCounter)++] = j;
        }
        i++; j--;
    }
}
void playOnPlace(char**matrix,int N,int M, int x,int y,char&turn, int*history,int* historyCounter,int*lastChecked,int *lastCounter) {
    if ((x < 0 || x >= N) || (y < 0 || y >= M)) {
        cout << "The coordinates must be in the interval [1," << N << "] and [1," << M << "]" << endl;
    }
    else {
        if (matrix[x][y] != '0') {
            cout << "This place is taken" << endl;
            return;
        }
        else {
            *lastCounter = 0;
            matrix[x][y] = turn;       
            int i = 0;
            int j = 0;
            markColumn(N, x, y, matrix, lastChecked, lastCounter);
            markRow(M, x, y, matrix, lastChecked, lastCounter);
            markMainDiagUp(i, j, x, y, matrix, lastChecked, lastCounter);
            markMainDiagDown(M, N, i, j, x, y, matrix, lastChecked, lastCounter);
            markSecondDiagUp(M, i, j, x, y, matrix, lastChecked, lastCounter);
            markSecondDiagDown(N, i, j, x, y, matrix, lastChecked, lastCounter);
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
}
void historyPrint(int historyCounter, int* history) {
    char player = '1';
    if (historyCounter == 0) {
        cout << "There is no history to be shown." << endl;
    }
    else {
        for (int i = 0;i < historyCounter;i += 2) {
            cout << "P" << player << "->" << "(" << history[i] + 1 << ',' << history[i + 1] + 1 << ")" << endl;
            if (player == '1') {
                player = '2';
            }
            else {
                player = '1';
            }
        }
    }
}
void backFunction(int &lastCounter,char**matrix,int*lastChecked,int*history,char&turn,int&historyCounter) {
    if (historyCounter < 2||lastCounter == 0) {
        cout << "No moves to undo or you just backed." << endl;
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
        lastCounter = 0;
        if (turn == '1') {
            turn = '2';
        }
        else {
            turn = '1';
        }
    }
}
void deleteArray(int*& arr, int& counter) {
    delete[]arr;
    arr = nullptr;
    counter = 0;
}
void saveGame(char nameFile[], int N,int M, char& turn, int& historyCounter,int &lastCounter,char**matrix,int*history,int*lastChecked) {
    ofstream file(nameFile);
    if (!file) {
        cout << "Cannot open file!" << endl;
    }
    else {
        file << N << " " << M << endl;
        file << turn << endl;
        file << historyCounter << endl;
        for (int i = 0; i < historyCounter; i++) {
            file << history[i] << " ";
        }
        file << endl;
        file << lastCounter << endl;
        for (int i = 0; i < lastCounter; i++) {
            file << lastChecked[i] << " ";
        }
        file << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                file << matrix[i][j];
            }
            file << endl;
        }

        file.close();
        cout << "Game saved successfully." << endl;
    }
}
void loadGame(char**& matrix, int& N, int& M, int*& history, int& historyCounter, int*& lastChecked, int& lastCounter, char& turn){
    cout << "Enter name of file to be loaded: ";
    char fileName[COMMAND_SIZE];
    cin >> fileName;
    ifstream file(fileName);
    if (!file) {
        cout << "File with this name does not exists now: "<<fileName;
    }
    else {
        if (matrix != nullptr) {
            deleteMatrix(N, matrix);
        }
        if (history != nullptr) {
            deleteArray(history, historyCounter);
        }

        if (lastChecked != nullptr) {
            deleteArray(lastChecked, lastCounter);
        }
        file >> N >> M;
        file >> turn;
        file >> historyCounter;
        history = new int[MAX_SIZE_OF_BOARD * MAX_SIZE_OF_BOARD * 2];
        for (int i = 0;i < historyCounter;i++) {
            file >> history[i];
        }

        file >> lastCounter;
        lastChecked = new int[MAX_SIZE_OF_BOARD * MAX_SIZE_OF_BOARD * 2];
        for (int i = 0; i < lastCounter; i++) {
            file >> lastChecked[i];
        }
        matrix = createMatrix(N, M);
        for (int i = 0;i < N;i++) {
            for (int j = 0;j < M;j++) {
                file >> matrix[i][j];
            }
        }
        cout << "You load save: " << fileName << " successfully" << endl;
        cout << "The board is:" << endl;
        printMatrix(N, M, matrix);
    }
}
int main()
{
    cout << "Welcome to the game \"Queens\"" << endl << endl;
    cout << "These are all commands in the game:" << endl;
    printHelp();
    cout << endl;
    cout << "Enter command: ";
    char command[COMMAND_SIZE];
    cin >> command;
    int N = 0;
    int M = 0;
    char** matrix = nullptr;
    int* history = nullptr;
    int historyCounter = 0;
    char turn = '1';
    int* lastChecked = nullptr;
    int lastCounter = 0;
    while (true) {
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
            int n;
            int m;
            while (true) {
                cout << "Enter size of the board: ";

                if (!(cin >> n >> m)) {
                    cout << "Invalid input. Enter two integers." << endl;
                    cin.clear();
                    char ch;
                    while (cin.get(ch) && ch != '\n');
                    continue;
                }

                if (n < 1 || n > MAX_SIZE_OF_BOARD || m < 1 || m > MAX_SIZE_OF_BOARD) {
                    cout << "N and M must be in the interval [1,15]" << endl;
                    continue;
                }
                else {
                    cout << "Board " << n << "x" << m << endl;
                    if (matrix) {
                        deleteMatrix(N, matrix);
                    }
                    if (history) { 
                        delete[] history;
                    }
                    if (lastChecked) { 
                        delete[] lastChecked;
                    }
                    matrix = createMatrix(n, m);
                    N = n;
                    M = m;
                    history = new int[N * M * 2];
                    lastChecked = new int[N * M * 2];
                    historyCounter = 0;  
                    lastCounter = 0;     
                    turn = '1';
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
                int inputX, inputY;
                cin >> inputX >> inputY;
                int x = inputX - 1;
                int y = inputY - 1;             
                playOnPlace(matrix,N,M,x,y,turn,history,&historyCounter,lastChecked,&lastCounter);              
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
            if (matrix == nullptr) {
                cout << "No game to save!" << endl;
            }
            else {
                cout << "Enter name for the save: ";
                char nameFile[COMMAND_SIZE];
                cin >> nameFile;
                ifstream check(nameFile);
                if (check) {
                    cout << "File with this name already exists!" << endl;
                    check.close();
                }
                else {
                    saveGame(nameFile, N, M, turn, historyCounter, lastCounter, matrix, history, lastChecked);                   
                }
            }        
            cout << "Enter new command: ";
            cin >> command;
        }
        else if (myStrcmp(command, "load")) {
            loadGame(matrix,N,M,history,historyCounter,lastChecked,lastCounter,turn);
            cout << "Enter new command: ";
            cin >> command;
            
        }
        else if (myStrcmp(command, "turn")) {
            if (matrix == nullptr) {
                cout << "There is no board."<<endl;
            }
            else {
                cout << "Player: " << turn << " is now" << endl;
            }
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
            historyPrint(historyCounter, history);
            cout << "Enter new command: ";
            cin >> command;

        }
        else if (myStrcmp(command, "exit")) {
            if (matrix) {
                deleteMatrix(N, matrix);
            }
            if (history) {
                delete[] history;
            }
            if (lastChecked) { delete[] lastChecked; }

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



