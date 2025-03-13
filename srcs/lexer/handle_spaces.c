#include "../../includes/minishell.h"

int	handle_space(int *curr_index, t_token *parsed_token)
{
	parsed_token->value = ft_strdup(" ");
	parsed_token->length = 1;
	parsed_token->category = TOKEN_SPACE;
	(*curr_index)++;
	return (EXIT_SUCCESS);
}

int	delete_spaces(t_minishell **minishell)
{
	remove_list_nodes(
		&(*minishell)->tokens, " ",
		(int (*)(const char *, const void *))ft_strcmp);
	return (EXIT_FAILURE);
}
