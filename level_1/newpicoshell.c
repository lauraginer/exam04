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
	int up_fd = 0; //valor copiado del pipe_df[0], lo utilizamos en el proceso padre

	if(!cmds)
		return(1); //creo que deberia de retornar 1 segun el subject
	while(cmds[i])
	{
		if(cmds[i + 1])
		
		//necesitamos este bucle para recorrer los comandos y crear el pipe como tal
		pid = fork;
		if(pid < 0)
		{

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