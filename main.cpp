#include <iostream>
#include <thread>
using namespace std;

int dinamicPassword = 0;       // Variable global para almacenar la contraseña dinámica
const int directions[5][4] = { // Matriz que almacena las direcciones de los establecimientos
    {1, 11, 23, 12},
    {2, 11, 3, 57},
    {3, 19, 1, 96},
    {4, 19, 7, 29},
    {5, 95, 11, 49}};

// Función para generar la contraseña dinámica
void generateDinamicPassword(int *password)
{
    while (true)
    {
        this_thread::sleep_for(chrono::seconds(5)); // Detiene el hilo de la generacion de la clave dinamica por 5 segundos
        srand(time(nullptr));                       // Inicializa el generador de números aleatorios
        *password = (rand() % 900000 + 100000);     // Genera un número aleatorio de 6 dígitos
    }
}

// Función para inicializar el hilo de la contraseña dinámica
void initThreadDinamicPassword()
{
    thread threadDinamicPassword(generateDinamicPassword, &dinamicPassword); // Inicia un hilo para generar la contraseña dinámica
    threadDinamicPassword.detach();                                          // separa el hilo principal del hilo de la contraseña dinámica
}

// Función para calcular las indicaciones de dirección
void calculateIndications(int *calleOrigen, int *carreraOrigen, int *numeroOrigen, int *selectedDirection)
{
    // Calcula la cantidad de cuadras en la calle y carrera
    int blocksStreet = abs(*calleOrigen - *(*(directions + *selectedDirection) + 1));
    int blocksCra = abs(*carreraOrigen - *(*(directions + *selectedDirection) + 2));

    // Imprime las indicaciones de dirección
    cout << "Desde la ubicación ";
    cout << "Calle " << *calleOrigen << " Carrera " << *carreraOrigen << " #" << *numeroOrigen;
    cout << " hasta la ubicación ";
    cout << "Calle " << *(*(directions + *selectedDirection) + 1) << " Carrera " << *(*(directions + *selectedDirection) + 2) << " #" << *(*(directions + *selectedDirection) + 3) << ":\n";

    // Imprime la primera indicación
    cout << "1. Dirígase hacia ";
    if (*calleOrigen < *(*(directions + *selectedDirection) + 1))
    {
        cout << "el sur ";
    }
    else
    {
        cout << "el norte ";
    }
    cout << "por " << blocksStreet << " cuadras en la Calle " << *calleOrigen << ".\n";

    // Imprime la segunda indicación
    cout << "2. Gire a la ";
    if (*carreraOrigen < *(*(directions + *selectedDirection) + 2))
    {
        cout << "derecha ";
    }
    else
    {
        cout << "izquierda ";
    }

    cout << "en la Carrera " << *carreraOrigen << " y avance ";
    cout << blocksCra << " cuadras hacia ";
    if (*carreraOrigen < *(*(directions + *selectedDirection) + 2))
    {
        cout << "el occidente.\n";
    }
    else
    {
        cout << "el oriente.\n";
    }

    // Imprime la tercera indicación
    cout << "3. Busque el número de establecimiento " << *(*(directions + *selectedDirection) + 3) << " en la Calle " << *(*(directions + *selectedDirection) + 1) << ".\n";
}

// Función para buscar el cajero
void searchCashier()
{
    int street, cra, number, selectedDirection;
    // Solicita al usuario ingresar la calle, carrera y número de establecimiento
    cout << "Ingrese la calle en la que se encuentra: " << endl;
    cin >> street;

    cout << "Ingrese la carrera en la que se encuentra: " << endl;
    cin >> cra;

    cout << "Ingrese el numero de establecimiento en el que se encuentra: " << endl;
    cin >> number;

    cout << "Seleccione alguna de las siguientes ubicaciones de cajeros: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << *(*(directions + i)) << ". ";
        cout << "Calle: " << *(*(directions + i) + 1);
        cout << " Carrera: " << *(*(directions + i) + 2);
        cout << " Numero Establecimiento: " << *(*(directions + i) + 3) << endl;
    }
    cin >> selectedDirection;
    selectedDirection = selectedDirection - 1;
    calculateIndications(&street, &cra, &number, &selectedDirection); // Calcula las indicaciones para llegar al cajero
}

int main()
{
    initThreadDinamicPassword(); // Inicializa el hilo para la contraseña dinámica
    searchCashier();             // Busca el cajero
    return 0;
}