/* Funciones permitidas: pipe, fork, dup2, execvp, close, exit

Escribe la siguiente función:

    int    ft_popen(const char *file, char *const argv[], int type)

La función debe lanzar el ejecutable file con los argumentos argv (usando execvp).
Si el tipo es 'r', la función debe devolver un descriptor de archivo conectado a la salida del comando. 
Si el tipo es 'w', la función debe devolver un descriptor de archivo conectado a la entrada del comando. 
En caso de error o parámetro inválido, la función debe devolver -1.

Ejemplo:

int main() {
    int fd = ft_popen("ls", (char const[]){"ls", NULL}, 'r');

    char line;
    while(line = get_next_line(fd))
        ft_putstr(line);
}

Pista: ¡No dejes descriptores de archivo abiertos!*/

#include <unistd.h>
int    ft_popen(const char *file, char *const argv[], int type)
{
	//necesitas crear los fd correspondientes para controlarlos con la funcion pipe
}

int main() 
{
    int fd = ft_popen("ls", (char const[]){"ls", NULL}, 'r');

    char line;
    while(line = get_next_line(fd))
        ft_putstr(line);
}