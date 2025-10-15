/* Funciones permitidas: pipe, fork, dup2, execvp, close, exit

Escribe la siguiente función:

	int    ft_popen(const char *file, char *const argv[], int type)

La función debe lanzar el ejecutable file con los argumentos argv (usando execvp).
Si el tipo es 'r',
	la función debe devolver un descriptor de archivo conectado a la salida del comando.
Si el tipo es 'w',
	la función debe devolver un descriptor de archivo conectado a la entrada del comando.
En caso de error o parámetro inválido, la función debe devolver -1.

Ejemplo:

int	main(void) {
	int fd = ft_popen("ls", (char const[]){"ls", NULL}, 'r');

	char line;
	while(line = get_next_line(fd))
		ft_putstr(line);
}

Pista: ¡No dejes descriptores de archivo abiertos!*/

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int	ft_popen(const char *file, char *const argv[], int type)
{
	int		pipe_fd[2];
	pid_t	pid;

	if ((type != 'w' && type != 'r') || !argv || !file)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			close(pipe_fd[0]); //cerramos el extremo de lectura del pipe
			if (dup2(pipe_fd[1], 1) == -1) //redirigimos stdout al extremo de escritura
				exit(-1);
		}
		else //type == 'w'
		{
			close(pipe_fd[1]); //cerramos el extremo de escritura del pipe
			if (dup2(pipe_fd[0], 0) == -1) //redirigimos stdin al extremo de lectura
				exit(-1);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execvp(file, argv);
		exit(-1);
	}
	if (pid > 0)
	{
		if (type == 'r')
		{
			close(pipe_fd[1]);
			return (pipe_fd[0]);
		}
		else
		{
			close(pipe_fd[0]);
			return (pipe_fd[1]); //retornamos el fd, como se nos pide en el subject
		}
	}
}

//función principal para probar ft_popen
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	*simple_read_line(int fd)
{
	static char	buffer[1024];
	int			i;
	char		c;

	i = 0;
	while (read(fd, &c, 1) > 0 && c != '\n' && i < 1023)
		buffer[i++] = c;
	if (i == 0)
		return (NULL);
	buffer[i] = '\0';
	return (buffer);
}

int	main(void)
{
	printf("=== Test 1: ls (modo 'r') ===\n");
	char *args1[] = {"ls", "-la", NULL};
	int fd1 = ft_popen("ls", args1, 'r');

	if (fd1 < 0)
	{
		printf("Error al ejecutar ls\n");
		return (1);
	}

	printf("Output de ls -la:\n");
	char *line;
	while ((line = simple_read_line(fd1)) != NULL)
		printf("%s\n", line);

	close(fd1);

	printf("\n=== Test 2: cat (modo 'w') ===\n");
	char *args2[] = {"cat", NULL};
	int fd2 = ft_popen("cat", args2, 'w');

	if (fd2 < 0)
	{
		printf("Error al ejecutar cat\n");
		return (1);
	}

	const char *text = "Hola, mundo! Esto es una prueba.\n";
	printf("Enviando texto a cat: %s", text);
	write(fd2, text, strlen(text));
	close(fd2);

	printf("\n=== Tests completados ===\n");
	return (0);
}