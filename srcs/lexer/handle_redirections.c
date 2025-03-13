#include "../../includes/minishell.h"

static void	update_token_values(
				char *value_str, int token_type, int len, t_token *token);

int	handle_redirection(char *input, int *curr_index, t_token *token)
{
	if (input[*curr_index] == '>')
	{
		if (input[*curr_index + 1] == '>')
			update_token_values(">>", TOKEN_REDIR_IN, 2, token);
		else
			update_token_values(">", TOKEN_REDIR_OUT, 1, token);
	}
	else
	{
		if (input[*curr_index + 1] == '<')
			update_token_values("<<", TOKEN_HEREDOC, 2, token);
		else
			update_token_values("<", TOKEN_APPEND, 1, token);
	}
	*curr_index += token->length;
	return (EXIT_SUCCESS);
}

static void	update_token_values(
	char *value_str, int token_type, int len, t_token *token)
{
	if (token->value)
		free(token->value);
	token->value = ft_strdup(value_str);
	token->category = token_type;
	token->length = len;
}
