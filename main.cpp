#include <iostream>
#include <thread>
#include <stdlib.h>
using namespace std;

void generateDinamicPassword(int *clave)
{
    while (true)
    {
        this_thread::sleep_for(chrono::seconds(1));
        srand(time(nullptr));
        *clave = (rand() % 900000 + 100000);
        cout << "Espacio de Memoria Hilo " << &clave << " Valor " << *clave << endl;
    }
}

int* initThreadDinamicPassword()
{
    int dinamicPassword = 0;
    int *dinamicPasswordPtr = &dinamicPassword;
    thread threadDinamicPassword(generateDinamicPassword, dinamicPasswordPtr);
    threadDinamicPassword.detach();
    return dinamicPasswordPtr;
}

int main()
{
    int *dinamicPassword = initThreadDinamicPassword();
    cout << "Espacio de Memoria Principal " << &dinamicPassword << " Valor " << *dinamicPassword << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Espacio de Memoria Principal " << &dinamicPassword << " Valor " << *dinamicPassword << endl;

    return 0;
}