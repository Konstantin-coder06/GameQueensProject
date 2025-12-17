#include <iostream>
using namespace std;
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
int main()
{
    cout << "Welcome to the game \"Queens\""<<endl<<endl;

    printHelp();
	int n,m;
	cin >> n>> m;
	cout << "Board " << n << "x" << m<<endl;
    int** matrix = createMatrix(n, m);
    printMatrix(n, m, matrix);
    deleteMatrix(n, matrix);
 
}


