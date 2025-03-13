#include "../../includes/minishell.h"

extern int	g_exit_status;

int	handle_single_quote(char *input, int *index, t_token *token)
{
	int	end_index;
	int	token_len;

	end_index = *index + 1;
	while (input[end_index] != '\'' && input[end_index] != '\0')
		end_index++;
	if (input[end_index] == '\0')
	{
		printf("Error: unclosed quotes\n");
		free(token);
		g_exit_status = 1;
		return (EXIT_FAILURE);
	}
	token->value = ft_substr(input, *index + 1, end_index - *index - 1);
	token_len = end_index - *index + 1;
	token->length = token_len;
	token->category = TOKEN_ARGUMENT;
	*index = end_index + 1;
	return (EXIT_SUCCESS);
}

int	handle_double_quote(char *input, int *index, t_token *token)
{
	int	end_index;
	int	token_len;

	end_index = *index + 1;
	while (input[end_index] != '\"' && input[end_index] != '\0')
		end_index++;
	if (input[end_index] == '\0')
	{
		printf("Error: unclosed quotes\n");
		free(token);
		g_exit_status = 1;
		return (EXIT_FAILURE);
	}
	token->value = ft_substr(input, *index + 1, end_index - *index - 1);
	token_len = end_index - *index + 1;
	token->length = token_len;
	token->category = TOKEN_DOUBLE_QUOTE;
	*index = end_index + 1;
	return (EXIT_SUCCESS);
}
