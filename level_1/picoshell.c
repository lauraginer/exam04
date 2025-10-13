/*Funciones permitidas:    close, fork, wait, exit, execvp, dup2, pipe
___

Escribe la siguiente función:

int	picoshell(char **cmds[]);

El objetivo de esta función es ejecutar un pipeline. Debe ejecutar cada
uno de los comandos de cmds y conectar la salida de uno con la entrada del
siguiente comando (como lo hace un shell).

Cmds contiene una lista de comandos válidos terminada en NULL. Cada fila
de cmds es un array argv directamente utilizable para una llamada a execvp. El primer
argumento de cada comando es el nombre del comando o ruta y puede pasarse
directamente como primer argumento de execvp.

Si ocurre cualquier error, la función debe devolver 1 (por supuesto, debes
cerrar todos los descriptores de archivo abiertos antes). De lo contrario,
	la función debe esperar a todos los procesos
hijos y devolver 0. Encontrarás en este directorio un archivo main.c que
contiene algo para ayudarte a probar tu función.

Ejemplos:
./picoshell /bin/ls "|" /usr/bin/grep picoshell
picoshell
./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'
squblblb/
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int    picoshell(char **cmds[])
{
	int pipe_fd[2];
	pid_t pid; //para guardar el fork
	int i = 0;
	int status;
	int result = 0;
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
		pid = fork();
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
			if(up_fd != 0)
			{
				if(dup2(up_fd, 0) == -1)
					exit(1);
				close(up_fd);
			}
			if(pipe_fd[1] != -1)
			{
				if(dup2(pipe_fd[1], 1) == -1)
					exit(1);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if(pid > 0)//proceso padre
		{
			if(up_fd != 0)
				close(up_fd);
			if(pipe_fd[1] != -1)
				close(pipe_fd[1]); //solo cerramos el extremo de escritura
			up_fd = pipe_fd[0];
			i++;
			//se realizan comprobaciones para poder cerrar por completo los procesos hijos
		}
	}
	while(wait(&status) > 0)
	{
		if(WIFEXITED(status) && (WEXITSTATUS(status) != 0)) //si el proceso hijo ha terminado bien y el codigo de status es diferente a 0
			result = 1;
		if(!WIFEXITED(status))
			result = 1;
			//se controlan las señales
	}
	return(result);
}
// man 2 wait
// man pipe- estructura pipe funcional