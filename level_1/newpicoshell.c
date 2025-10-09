/*Cmds contiene una lista de comandos válidos terminada en NULL. Cada fila 
de cmds es un array argv directamente utilizable para una llamada a execvp. El primer 
argumento de cada comando es el nombre del comando o ruta y puede pasarse 
directamente como primer argumento de execvp.

Si ocurre cualquier error, la función debe devolver 1 (por supuesto, debes 
cerrar todos los descriptores de archivo abiertos antes). De lo contrario, la función debe esperar a todos los procesos 
hijos y devolver 0. Encontrarás en este directorio un archivo main.c que 
contiene algo para ayudarte a probar tu función.

Ejemplos: 
./picoshell /bin/ls "|" /usr/bin/grep picoshell
picoshell
./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'
squblblb/ 

Funciones permitidas:    close, fork, wait, exit, execvp, dup2, pipe
*/

#include <sys/types.h>
#include <unistd.h>

int    picoshell(char **cmds[])
{
	int pipe_fd[2];
	pid_t pid; //para guardar el fork
	int i = 0;
	int status;
	int result;
	int up_fd = 0; //extremo de lectura (fd[0]) del comando anterior

	while(cmds[i])
	{
		if(cmds[i + 1]) //si existe un segundo comando, creamos entonces el pipe
		{
			if(pipe(pipe_fd) == -1)
				return(1);
		}
		else //si no existe (es el último), añadimos este valor como flag para gestionar luego
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
		}
		pid = fork;
		if(pid < 0)
		{
			if(pipe_fd[0] != -1)
				close(pipe_fd[0]);
			if(pipe_fd[1] != -1)
				close(pipe_fd[1]);
			if(up_fd != 0)
				close(up_fd);
			return(1);
		}
		if(pid == 0)//proceso hijo
		{
			//aqui debemos de ejecutar los comandos y redirigir el fd[1](escritura)
		}
		if(pid > 0)//proceso padre
		{
			//se realizan comprobaciones para poder cerrar por completo los procesos hijos
		}
		while(wait(&status) > 0)
		{
			//se controlan las señales
		}
	}
}