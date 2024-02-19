#include <iostream>
#include <thread>
#include <stdlib.h>
using namespace std;

void threadOne(string *clave)
{
    srand(0);
    this_thread::sleep_for(std::chrono::seconds(5));
    *clave = "prueba";
    cout << rand()%100 << endl;
}

int main()
{
    string clave = "trabajo";
    thread first(threadOne, &clave);

    first.join();
    cout << clave << endl;
    cout << "Final de los hilos";

    return 0;
}