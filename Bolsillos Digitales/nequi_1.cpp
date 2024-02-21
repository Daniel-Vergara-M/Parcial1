/*
Miembros del grupo:
- @Daniel-Vergara-M
- @DanielDSanchez

Dirigido a: @Tlcabrera
*/

#include <iostream> // Se importa la librería para inputs y outputs
#include <map>      // Se importa la librería map para hacer diccionarios

using namespace std;

#define MAX_USERS 10        // Se define el máximo de usuarios para el sistema
#define MAX_QUESTIONS 5     // Se define el número de preguntas de seguridad
#define QUESTIONS_COLUMNS 2 // Se define el número de columnas de la matriz de preguntas
#define MAX_ATTEMPTS 3      // Se define el número de intentos para el login

const string questions[MAX_QUESTIONS][QUESTIONS_COLUMNS] = {
    {"1", "¿Cuál es el nombre de tu mascota? "},
    {"2", "¿Cuál es el nombre de tu madre? "},
    {"3", "¿Cuál es el nombre de tu padre?"},
    {"4", "¿Cuál es el nombre de tu mejor amig@? "},
    {"5", "¿Cuál fue tu mejor asignatura?"}};
/*
Matriz bidimensional de tipo string que contiene 5 questions de preguntas y sus respectivos números.
*/

string db[MAX_USERS][6] = {
    // Structure: username, phoneNumber, password, questionId, questionAnswer, balance
    {"Juan", "3008493756", "1974", "1", "Peter", "100000"},
    {"Pedro", "3158640321", "0567", "3", "Alberto", "50000"},
    {"Daniel", "3125198270", "0604", "1", "Susy", "0"}};
/*
Matriz bidimensional de tipo string que soporta hasta 10 usuarios y contiene 5 columnas:
- Nombre de usuario
- Número de teléfono
- Contraseña
- Número de la pregunta de seguridad
- Respuesta de la pregunta de seguridad
- Saldo
*/

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
void registerAccount(string *username, string *phoneNumber, string *pass)
{
    // Registra una nueva cuenta en caso tal de que no este registrado en la base de datos
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (*(*(db + i) + 0) == "")
        {
            *(*(db + i) + 0) = *username;
            *(*(db + i) + 1) = *phoneNumber;
            *(*(db + i) + 2) = *pass;
            println("Seleccione una pregunta de seguridad: ");
            for (int j = 0; j < MAX_QUESTIONS; j++)
            {
                println(*(*(questions + j) + 0) + ". " + *(*(questions + j) + 1));
            }
            cin >> *(*(db + i) + 3);
            print("Ingrese la respuesta a la pregunta de seguridad: ");
            cin >> *(*(db + i) + 4);
            *(*(db + i) + 5) = "0"; // Saldo inicial de la cuenta
            println("Usuario registrado con éxito");
            return;
        }
    }
    println("No hay espacio para más usuarios");
};

void updatePassword(string *username, string *phoneNumber, string *newPass)
{
    string respuesta;
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (*(*(db + i) + 0) == *username && *(*(db + i) + 1) == *phoneNumber)
        {
            /*
            En la primera condición se verifica que elemento indice i,0 sea igual al valor de username
            En la segunda condición se verifica que elemento indice i,1 sea igual al valor de phoneNumber
            Esto por medio de operaciones de suma con punteros
           */
            print("Ingrese la respuesta a la pregunta de seguridad: ");
            cin >> respuesta;
            if (respuesta == *(*(db + i) + 4))
            // Se verifica que la respuesta sea igual al indice i,4 de la matriz db
            {
                // Se le asigna al indice i, 2 de la matriz db el valor de newPass
                *(*(db + i) + 2) = *newPass;
                println("Contraseña actualizada con éxito");
                return;
            }
            else
            {
                println("Respuesta incorrecta");
                return;
            }
        }
    }
    println("Usuario y/o contraseña no encontrado");
    return;
};

bool login(string *username, string *phoneNumber, string *pass)
{
    if (phoneNumber->length() != 10)
    {
        println("El número de teléfono debe tener 10 dígitos.");
        return false;
    }

    if (pass->length() != 4)
    {
        println("La contraseña debe tener 4 caracteres.");
        return false;
    }

    for (int i = 0; i < MAX_USERS; i++)
    {
        if (*(*(db + i) + 0) == *username && *(*(db + i) + 1) == *phoneNumber && *(*(db + i) + 2) == *pass)
        {
            println("Bienvenido " + *username);
            return true;
        }
    }
    return false;
};

void loginMenu()
{
    string usuario, numCelular, clave;
    int intentos;

    for (intentos = 0; intentos < MAX_ATTEMPTS; intentos++)
    {
        print("Ingrese su usuario: ");
        cin >> usuario;
        print("Ingrese su número de celular: ");
        cin >> numCelular;
        print("Ingrese su clave: ");
        cin >> clave;
        if (login(&usuario, &numCelular, &clave))
        {
            break;
        }
        else
        {
            println("¡Usuario no encontrado!");
        }
    }
    if (intentos == MAX_ATTEMPTS)
    {
        println("Ha superado el número de intentos permitidos");
        return;
    }
}

void registerMenu()
{
    string usuario, numCelular, clave;
    print("Ingrese su usuario: ");
    cin >> usuario;
    print("Ingrese su número de celular: ");
    cin >> numCelular;
    print("Ingrese su clave: ");
    cin >> clave;
    registerAccount(&usuario, &numCelular, &clave);
}

void recoverPasswordMenu()
{
    string usuario, numCelular, clave;
    print("Ingrese su usuario: ");
    cin >> usuario;
    print("Ingrese su número de celular: ");
    cin >> numCelular;
    print("Ingrese su nueva clave: ");
    cin >> clave;
    updatePassword(&usuario, &numCelular, &clave);
}

void mainMenu()
{
    int option = 0;
    int times = 0;
    do
    {
        times++;
        println("=== MENU ===");
        println("1. Iniciar sesión");
        println("2. Registrarse");
        println("3. Recuperar contraseña");
        println("4. Salir");
        print(" Seleccione una opción: ");
        cin >> option;
        switch (option)
        {
        case 1:
            loginMenu();
            break;
        case 2:
            registerMenu();
            break;
        case 3:
            break;
        case 4:
            println("Saliendo del programa.");
            break;
        default:
            println("Opción no válida");
            break;
        }
        if (times == 5)
        {
            option = 4;
        }
    } while (times < 6);
    print("" + times);
}
int main()
{

    mainMenu();
    return 0;
}
