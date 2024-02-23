# Bolsillos Digitales

#### Miembros del grupo:

- Daniel Vergara
- Daniel Sanchéz

### Documentación

Se hace uso de la clase/módulo `methods.h` con el fin de que las funciones que esten puestas ahí se puedan usar en cualquier programa y evitar sobrecargar el archivo principal.

**Tener en cuenta:**

- El número del teléfono del usuario ha de tener una longitud de 10 dígitos.
- La contraseña para acceder a la aplicación ha de tener una longitud de 4 dígitos.
- Al iniciar el programa y registrarse, depositar un monto de dinero a la cuenta.
- En la opción de "Pago", se hace referencia a los servicios de entretenimiento u otros que se realizan pagos automáticos, que dentro del programa serían semi-automáticos.

**Funciones dentro de `methods.h`:**

- println(texto); Muestra en consola el texto y luego un salto de línea.
- print(texto); Muestra en consola el texto.
- printMatriz(matriz, filas, columnas); Muestra todos los elementos de la matriz fila por fila.
- getEmptyRowIndex(matriz, filas, columnas); Devuelve la primera fila vacia.

**Funciones dentro de `nequi.cpp`:**

- **Funciones de acceso:**

  - registerAccount(nombre_de_usuario, número_de_teléfono, contraseña); Se registra la cuenta en la base de datos para luego usarse para el login.
  - login(nombre_de_usuario, número_de_teléfono, contraseña); Se inicia sesión con las credenciales dadas. Devuelve `true` o `false` si hubo un logueo exitoso o no.
  - updatePassword(nombre_de_usuario, número_de_teléfono, contraseña_nueva); Se actualiza la contraseña del usuario por medio de la respuesta a su pregunta de seguridad designada al momento de crear la cuenta.

- **Funciones con relación al dinero o movimientos:**
  - searchCashier(); Muestra en consola una lista de cajeros disponibles y calcula los movimientos que tienes que hacer para llegar al mismo
  - initThreadDinamicPassword(); inicia un hilo concurrente y separado al hilo inicial de la aplicacion en el cual se va a ir actualizando cada cierto tiempo la clave dinamica
  - getMovementHistory(número_de_teléfono); Muestra en consola el historial de movimientos realizados para la cuenta activa.
  - getBalance(número_de_teléfono); Muestra en consola el saldo total en la cuenta activa.
  - transfer(número_de_teléfono, número_de_teléfono_a_enviar, cantidad); Se realiza la transferencia de un monto de dinero desde la cuenta activa, a otra cuenta activa del servicio.
  - withdraw(número_de_teléfono, cantidad); Se realiza el retiro de dinero desde la cuenta activa y se descuenta.
  - deposit(número_de_teléfono, cantidad); Se realiza el deposito de dinero a la cuenta activa.
  - pay(número_de_teléfono, cantidad, descripción); Se realiza el pago de algún servicio de entretenimiento manualmente.

- **Funciones menú:**
  - registerMenu(); Registro de usuarios.
  - loginMenu(); Inicio de sesión para los usuarios registrados.
  - recoverPasswordMenu(); Cambio de contraseña.
  - onLoginMenu(); Menú que muestra las funcionalidades que tienen relación al dinero o movimientos.
  - mainMenu(); Hace uso de las 3 primeras funciones en este apartado y te permite escoger a cual quieres acceder.
