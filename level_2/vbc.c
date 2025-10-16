/* Assignment name:		vbc
   Expected files:		*.c *h
   Allowed functions:	malloc, calloc, realloc, free, printf, isdigit, write

   Escriba un programa que imprima el resultado de una expresión matemática dada como argumento.
   Debe manejar sumas, multiplicaciones y paréntesis. Todos los valores están entre 0 y 9 (incluidos).
   En caso de un símbolo inesperado, debe imprimir "Token inesperado '%c'\n".
   Si la expresión termina inesperadamente, debe imprimir "Fin de entrada inesperado\n".
   La misma regla se aplica si se encuentra un '(' o ')' inesperado.
   En caso de un fallo en la llamada al sistema, debe salir con 1.

   Ejemplos:
   $> ./vbc '1' | cat -e
   1$
   $> ./vbc '2+3' | cat -e
   5$
   $> ./vbc '3*4+5' | cat -e
   17$
   $> ./vbc '3+4*5' | cat -e
   23$
   $> ./vbc '(3+4)*5' | cat -e
   35$
   $> ./vbc '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' | cat -e
   188$
   $> ./vbc '1+'
   Fin de entrada inesperado
   $> ./vbc '1+2)' | cat -e
   Token inesperado ')'$ */

#include "vbc.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

node	*new_node(node n)
{
	node *ret = calloc(1, sizeof(*ret)); // cambiamos el sizeof(*ret)
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void	destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n"); //siempre tiene que ser input
}

int	accept(char **s, char c)
{
	if (**s == c) // cambiado, añadimos la comparacion con c, if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int	expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}

/* Declaraciones de funciones estáticas (solo visibles en este archivo) */
static node	*parse_expr_r(char **s);
static node	*parse_term(char **s);
static node	*parse_factor(char **s);

static node	*parse_factor(char **s)
{
	node	*e;

	node n; // nuevo nodo
	if (isdigit((unsigned char)**s)) // comprueba si el caracter es un digito
	{
		n.type = VAL;
		n.val = **s - '0';
		n.l = NULL;
		n.r = NULL;
		(*s)++;
		return (new_node(n));
	}
	if (accept(s, '(')) // comprueba si existe un paréntesis entero
	{
		e = parse_expr_r(s);
		if (!e)
			return (NULL);
		if (!expect(s, ')')) // si no hay un parentesis de cierre libera
		{
			destroy_tree(e);
			return (NULL);
		}
		return (e);
	}
	unexpected(**s);
	return (NULL);
}
static node	*parse_term(char **s)
{
	node	*left;
	node	*right;
	node	n;

	left = parse_factor(s);
	if (!left)
		return (NULL);
	while (accept(s, '*'))
	{
		right = parse_factor(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		n.type = MULTI;
		n.l = left;
		n.r = right;
		left = new_node(n);
		if (!left)
			return (NULL);
	}
	return (left);
}
static node	*parse_expr_r(char **s)
{
	node	*left;
	node	*right;
	node	n;

	left = parse_term(s);
	if (!left)
		return (NULL);
	while (accept(s, '+'))
	{
		right = parse_term(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		if()
		n.type = ADD;
		n.l = left;
		n.r = right;
		left = new_node(n);
		if (!left)
			return (NULL);
	}
	return (left);
}
node	*parse_expr(char *s)
{
	char	*p;
	node	*ret;

	p = s;
	ret = parse_expr_r(&p);
	if (!ret)
		return (NULL);
	if (*p)
	{
		unexpected(*p);
		destroy_tree(ret);
		return (NULL);
	}
	return (ret);
}
int	eval_tree(node *tree)
{
	switch (tree->type)
	{
	case ADD:
		return (eval_tree(tree->l) + eval_tree(tree->r));
	case MULTI:
		return (eval_tree(tree->l) * eval_tree(tree->r));
	case VAL:
		return (tree->val);
	}
	return (0); // por si acaso
}

int	main(int argc, char **argv)
{
	node	*tree;

	if (argc != 2)
		return (1);
	tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0); // por si acaso
}
