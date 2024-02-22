#include <iostream>

using namespace std;

void println(string text)
{
    cout << text << endl;
}

void print(string text)
{
    cout << text;
}

template <typename T>
void printMatriz(T vector, const int rows, const int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            print(vector[i][j] + ", ");
        }
        println("");
    }
}

template <typename T>
int getEmptyRowIndex(T vector, const int rows, const int columns) {
    /*
    Se busca el primer indice de filas en la matriz que esté vacio y se retorna el valor o -1
    */
    for (int i = 0; i < rows; i++) {
        bool isEmpty = true;
        for (int j = 0; j < columns; j++) {
            if (!vector[i][j].empty()) {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            return i;
        }
    }
    return -1;
}