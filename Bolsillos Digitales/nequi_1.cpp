/*
Miembros del grupo:
- @Daniel-Vergara-M
- @DanielDSanchez

Dirigido a: @Tlcabrera
*/

#include <iostream>  // Se importa la librería para inputs y outputs
#include <string>    // Se importa la librería para el manejo de strings
#include <map>       // Se importa la librería map para hacer diccionarios
#include "methods.h" // Se importa el archivo methods.h que contiene los métodos de impresión

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

string movimientosCuenta[20][6];
// Structure: phoneNumber , date, amount, type, description, toPhoneNumber
/* Possible types:
0. "Depósito",
1. "Retiro",
2. "Transferencia",
3. "Pago"
*/

void getMovementHistory(string *phoneNumber)
{
    /*
    Se obtiene el historial de movimientos para el número del teléfono
    */
    bool hasMovements = false;
    for (int i = 0; i < 20; i++)
    {
        if (*(*(movimientosCuenta + i) + 0) == *phoneNumber)
        {
            println("Fecha: " + *(*(movimientosCuenta + i) + 1) + " - Monto: " + *(*(movimientosCuenta + i) + 2) + " - Tipo: " + *(*(movimientosCuenta + i) + 3) + " - Descripción: " + *(*(movimientosCuenta + i) + 4) + " - Destinatario: " + *(*(movimientosCuenta + i) + 5));
            hasMovements = true;
        }
    }

    if (!hasMovements)
    {
        println("No hay movimientos para: " + *phoneNumber);
    }
}

void getBalance(string *phoneNumber)
{
    /*
    Se obtiene el saldo que se encuentra en la cuenta del número de teléfono
    */
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (*(*(db + i) + 1) == *phoneNumber)
        {
            println("Su saldo es: " + *(*(db + i) + 5));
            return;
        }
    }
    println("Número de teléfono no encontrado");
}

void transfer(string *phoneNumber, string *toPhoneNumber, string *amount)
{
    /*
    Se realizan transferencias del número A al número B con X cantidad de dinero
    Y se descuenta X cantidad de dinero del número A para agregar al número B
    Y se actualiza en la base de datos
    */
    for (int i = 0; i < 20; i++)
    {
        if (*(*(db + i) + 1) == *phoneNumber)
        {
            if (stoi(*(*(db + i) + 5)) >= stoi(*amount))
            {
                // Se actualiza el saldo de la persona que envia
                *(*(db + i) + 5) = to_string(stoi(*(*(db + i) + 5)) - stoi(*amount));

                // Se halla el índice de la persona que recibe
                int receiverIndex = -1;
                for (int j = 0; j < MAX_USERS; j++)
                {
                    if (*(*(db + j) + 1) == *toPhoneNumber)
                    {
                        receiverIndex = j;
                        break;
                    }
                }

                // Se actualiza el saldo de la persona que recibe
                if (receiverIndex != -1)
                {
                    *(*(db + receiverIndex) + 5) = to_string(stoi(*(*(db + receiverIndex) + 5)) + stoi(*amount));
                }

                // Se agrega la información a la matriz de movimientosCuenta
                int emptyIndex = getEmptyRowIndex(movimientosCuenta, 20, 6);
                if (emptyIndex != -1)
                {
                    *(*(movimientosCuenta + emptyIndex) + 0) = *phoneNumber;
                    *(*(movimientosCuenta + emptyIndex) + 1) = "2024-02-20";
                    *(*(movimientosCuenta + emptyIndex) + 2) = *amount;
                    *(*(movimientosCuenta + emptyIndex) + 3) = "2";
                    *(*(movimientosCuenta + emptyIndex) + 4) = "Transferencia";
                    *(*(movimientosCuenta + emptyIndex) + 5) = *toPhoneNumber;
                    println("Transferencia realizada con éxito");
                }
                return;
            }
            else
            {
                println("Saldo insuficiente!");
                return;
            }
        }
    }
    println("Número de teléfono no encontrado");
}

void withdraw(string *phoneNumber, string *amount)
{
    /*
    Se retira X cantidad de dinero del número asignado por el usuario
    */
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (*(*(db + i) + 1) == *phoneNumber)
        {
            // Busca en la base de datos el mismo número
            if (stoi(*(*(db + i) + 5)) >= stoi(*amount))
            {
                // Se verifica que el usuario tenga saldo o no
                *(*(db + i) + 5) = to_string(stoi(*(*(db + i) + 5)) - stoi(*amount));
                int emptyIndex = getEmptyRowIndex(movimientosCuenta, 20, 6);
                if (emptyIndex != 1)
                {
                    *(*(movimientosCuenta + emptyIndex) + 0) = *phoneNumber;
                    *(*(movimientosCuenta + emptyIndex) + 1) = "2024-02-20";
                    *(*(movimientosCuenta + emptyIndex) + 2) = *amount;
                    *(*(movimientosCuenta + emptyIndex) + 3) = "1";
                    *(*(movimientosCuenta + emptyIndex) + 4) = "Retiro";
                    *(*(movimientosCuenta + emptyIndex) + 5) = "N/A";
                    println("Retiro realizado con éxito");
                }
                return;
            }
            else
            {
                println("Saldo insuficiente");
                return;
            }
        }
    }
    println("Número de teléfono no encontrado");
}

void deposit(string *phoneNumber, string *amount)
{
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (*(*(db + i) + 1) == *phoneNumber)
        {
            *(*(db + i) + 5) = to_string(stoi(*(*(db + i) + 5)) + stoi(*amount));
            int emptyIndex = getEmptyRowIndex(movimientosCuenta, 20, 6);
            if (emptyIndex != 1)
            {
                *(*(movimientosCuenta + emptyIndex) + 0) = *phoneNumber;
                *(*(movimientosCuenta + emptyIndex) + 1) = "2024-02-20";
                *(*(movimientosCuenta + emptyIndex) + 2) = *amount;
                *(*(movimientosCuenta + emptyIndex) + 3) = "0";
                *(*(movimientosCuenta + emptyIndex) + 4) = "Depósito";
                *(*(movimientosCuenta + emptyIndex) + 5) = "N/A";
                println("Depósito realizado con éxito");
            }
            return;
        }
    }
    println("Número de teléfono no encontrado");
}

void pay(string *phoneNumber, string *amount, string *description)
{
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (*(*(db + i) + 1) == *phoneNumber)
        {
            if (stoi(*(*(db + i) + 5)) >= stoi(*amount))
            {
                *(*(db + i) + 5) = to_string(stoi(*(*(db + i) + 5)) - stoi(*amount));
                int emptyIndex = getEmptyRowIndex(movimientosCuenta, 20, 6);
                if (emptyIndex != -1)
                {
                    *(*(movimientosCuenta + i) + 0) = *phoneNumber;
                    *(*(movimientosCuenta + i) + 1) = "2024-02-20";
                    *(*(movimientosCuenta + i) + 2) = *amount;
                    *(*(movimientosCuenta + i) + 3) = "3";
                    *(*(movimientosCuenta + i) + 4) = *description;
                    *(*(movimientosCuenta + i) + 5) = "N/A";
                    println("Pago realizado con éxito");
                }
                return;
            }
            else
            {
                println("Saldo insuficiente");
                return;
            }
        }
    }
    println("Número de teléfono no encontrado");
}
void registerAccount(string *username, string *phoneNumber, string *pass)
{
    // Registra una nueva cuenta en caso tal de que no este registrado en la base de datos
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (*(*(db + i) + 0) == "")
        {
            // Verifica que el primer elemento de la fila este vacio
            *(*(db + i) + 0) = *username;
            *(*(db + i) + 1) = *phoneNumber;
            *(*(db + i) + 2) = *pass;
            println("Seleccione una pregunta de seguridad: ");
            for (int j = 0; j < MAX_QUESTIONS; j++) // Se itera en la matriz bidimensional de preguntas
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
        // Se verifica que la longitud del número del teléfono sea igual a 10
        println("El número de teléfono debe tener 10 dígitos.");
        return false;
    }

    if (pass->length() != 4)
    {
        // Se verifica que la longitud de la contraseña sea igual a 4
        println("La contraseña debe tener 4 caracteres.");
        return false;
    }

    for (int i = 0; i < MAX_USERS; i++)
    {
        if (*(*(db + i) + 0) == *username && *(*(db + i) + 1) == *phoneNumber && *(*(db + i) + 2) == *pass)
        {
            // Se verifican los valores introducidos por el usuario, con lo que se encuentra en base de datos
            println("Bienvenido " + *username);
            return true;
        }
    }
    return false;
};

void onLoginMenu(string *phoneNumber)
{
    int option = 0;
    string amount, description, toPhoneNumber, newPass, username, pass, questionId, questionAnswer;
    do
    {
        println("=== MENU ===");
        println("1. Consultar saldo");
        println("2. Realizar transferencia");
        println("3. Retirar dinero");
        println("4. Depositar dinero");
        println("5. Pagar");
        println("6. Historial de movimientos");
        println("7. Salir");
        print(" Seleccione una opción: ");
        cin >> option;
        switch (option)
        {
        case 1:
            getBalance(phoneNumber);
            break;
        case 2:
            print("Ingrese el número de teléfono al que desea transferir: ");
            cin >> toPhoneNumber;
            print("Ingrese el monto a transferir: ");
            cin >> amount;
            transfer(phoneNumber, &toPhoneNumber, &amount);
            break;
        case 3:
            print("Ingrese el monto a retirar: ");
            cin >> amount;
            withdraw(phoneNumber, &amount);
            break;
        case 4:
            print("Ingrese el monto a depositar: ");
            cin >> amount;
            deposit(phoneNumber, &amount);
            break;
        case 5:
            print("Ingrese el monto a pagar: ");
            cin >> amount;
            print("Ingrese la descripción del pago: ");
            cin >> description;
            pay(phoneNumber, &amount, &description);
            break;
        case 6:
            getMovementHistory(phoneNumber);
            break;
        case 7:
            println("Saliendo del programa.");
            break;
        default:
            println("Opción no válida");
            break;
        }
    } while (option != 7);
}
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
            onLoginMenu(&numCelular);
            break;
        }
        else
        {
            println("¡Usuario no encontrado!");
        }
    }
    if (intentos == MAX_ATTEMPTS - 1)
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
            recoverPasswordMenu();
            break;
        case 4:
            break;
        default:
            println("Opción no válida");
            break;
        }
        if (option == 4)
        {
            println("Saliendo del programa.");
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
