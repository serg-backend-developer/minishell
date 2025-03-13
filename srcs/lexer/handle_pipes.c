#include "../../includes/minishell.h"

int	handle_pipe(int *curr_index, t_token *parsed_token)
{
	parsed_token->value = ft_strdup("|");
	parsed_token->length = 1;
	parsed_token->category = TOKEN_PIPE;
	(*curr_index)++;
	return (EXIT_SUCCESS);
}
