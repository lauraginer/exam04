/*Funciones permitidas	:	fork, waitpid, exit, alarm, sigaction, kill,
						printf, strsignal, errno

Escribe la siguiente función:

#include <stdbool.h>
int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)

Esta función debe probar si la función f es una función buena o una función mala,
devolverás 1 si f es buena, 0 si f es mala o -1 en caso de un error en
tu función.

Una función se considera mala si es terminada o detenida por una señal
(segfault, abort...), si termina con cualquier otro código de salida distinto a 0 o si
se agota el tiempo.

Si verbose es true, debes escribir el mensaje apropiado entre los siguientes:

"Nice function!\n"
"Bad function: exited with code <exit_code>\n"
"Bad function: <signal description>\n"
"Bad function: timed out after <timeout> seconds\n"

No debes tener fugas de procesos (incluso en estado zombie, esto se comprobará usando
wait).

Probaremos tu código con funciones muy malas.*/
