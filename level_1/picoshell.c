/*Funciones permitidas:    close, fork, wait, exit, execvp, dup2, pipe
___

Escribe la siguiente función:

int    picoshell(char *cmds[]);

El objetivo de esta función es ejecutar un pipeline. Debe ejecutar cada 
uno de los comandos de cmds y conectar la salida de uno con la entrada del 
siguiente comando (como lo hace un shell).

Cmds contiene una lista de comandos válidos terminada en NULL. Cada fila 
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
*/

