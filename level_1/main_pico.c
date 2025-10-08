#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Declaración de la función picoshell
int		picoshell(char **cmds[]);

// Función auxiliar para crear los arrays de argumentos
char	**create_cmd(const char *cmd_str)
{
	char	**result;
	char	*cmd_copy;
	char	*token;
	int		count;

	cmd_copy = strdup(cmd_str);
	count = 0;
	// Contar el número de tokens
	token = strtok(cmd_copy, " ");
	while (token)
	{
		count++;
		token = strtok(NULL, " ");
	}
	// Reservar memoria para el array de strings + NULL
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
	{
		free(cmd_copy);
		return (NULL);
	}
	// Llenar el array
	strcpy(cmd_copy, cmd_str);
	token = strtok(cmd_copy, " ");
	count = 0;
	while (token)
	{
		result[count] = strdup(token);
		count++;
		token = strtok(NULL, " ");
	}
	result[count] = NULL;
	free(cmd_copy);
	return (result);
}

// Función para liberar la memoria de los comandos
void	free_cmds(char **cmds[])
{
	int i, j;
	for (i = 0; cmds[i] != NULL; i++)
	{
		for (j = 0; cmds[i][j] != NULL; j++)
		{
			free(cmds[i][j]);
		}
		free(cmds[i]);
	}
	free(cmds);
}

int	main(int argc, char *argv[])
{
	// Test 1: ls | grep .c
	printf("Test 1: ls | grep .c\n");
	char **test1_cmds[3];
	test1_cmds[0] = create_cmd("ls");
	test1_cmds[1] = create_cmd("grep .c");
	test1_cmds[2] = NULL;

	int result1 = picoshell(test1_cmds);
	printf("Result: %d\n\n", result1);
	free_cmds(test1_cmds);

	// Test 2: echo Hello World | tr 'a-z' 'A-Z'
	printf("Test 2: echo Hello World | tr a-z A-Z\n");
	char **test2_cmds[3];
	test2_cmds[0] = create_cmd("echo Hello World");
	test2_cmds[1] = create_cmd("tr a-z A-Z");
	test2_cmds[2] = NULL;

	int result2 = picoshell(test2_cmds);
	printf("Result: %d\n\n", result2);
	free_cmds(test2_cmds);

	// Test 3: ls | grep no_such_file | wc -l
	printf("Test 3: ls | grep no_such_file | wc -l\n");
	char **test3_cmds[4];
	test3_cmds[0] = create_cmd("ls");
	test3_cmds[1] = create_cmd("grep no_such_file");
	test3_cmds[2] = create_cmd("wc -l");
	test3_cmds[3] = NULL;

	int result3 = picoshell(test3_cmds);
	printf("Result: %d\n\n", result3);
	free_cmds(test3_cmds);

	return (0);
}