#ifndef VBC_H
# define VBC_H

# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
	enum
	{
		ADD,
		MULTI,
		VAL
	} type;
	int			val;
	struct node	*l;
	struct node	*r;
}				node;

node			*new_node(node n);
void			destroy_tree(node *n);
void			unexpected(char c);
int				accept(char **s, char c);
int				expect(char **s, char c);
node			*parse_expr(char *s);
int				eval_tree(node *tree);

#endif