#include "../../includes/minishell.h"

static int	handle_lexer_cases(
				t_minishell **minishell, char *input,
				int *curr_pos, t_token *token);

int	lexer(t_minishell **minishell, char *input)
{
	int		index;
	t_token	*token;
	int		return_value;

	index = 0;
	return_value = 0;
	(*minishell)->tokens = NULL;
	while (input[index] != '\0')
	{
		token = (t_token *)malloc(sizeof(t_token));
		if (token == NULL)
		{
			perror("Malloc failed");
			return (EXIT_FAILURE);
		}
		token->value = NULL;
		return_value = handle_lexer_cases(minishell, input, &index, token);
		if (return_value)
		{
			free(token);
			return (EXIT_FAILURE);
		}
		ft_lstadd_back(&(*minishell)->tokens, ft_lstnew((void *)token));
	}
	return (EXIT_FAILURE);
}

static int	handle_word(char *input, int *curr_index, t_token *token)
{
	int	substr_end;
	int	word_len;

	substr_end = *curr_index + 1;
	while (input[substr_end] != '\"' && input[substr_end] != '\''
		&& input[substr_end] != '\0' && input[substr_end] != ' '
		&& input[substr_end] != '<' && input[substr_end] != '>'
		&& input[substr_end] != '|' && input[substr_end] != '$'
		&& input[substr_end] != '\t')
		substr_end++;
	word_len = substr_end - *curr_index;
	token->value = ft_substr(input, *curr_index, substr_end - *curr_index);
	token->length = word_len;
	token->category = TOKEN_ARGUMENT;
	*curr_index = substr_end;
	return (EXIT_SUCCESS);
}

static int	handle_lexer_cases(
	t_minishell **minishell, char *input, int *curr_pos, t_token *token)
{
	int	return_value;

	return_value = 0;
	if (input[*curr_pos] == ' ' || input[*curr_pos] == '\t')
		return_value += handle_space(curr_pos, token);
	else if (input[*curr_pos] == '|')
		return_value += handle_pipe(curr_pos, token);
	else if (input[*curr_pos] == '$')
		return_value += handle_dollar_sign(minishell, input, curr_pos, token);
	else if (input[*curr_pos] == '\'')
		return_value += handle_single_quote(input, curr_pos, token);
	else if (input[*curr_pos] == '\"')
		return_value += handle_double_quote(input, curr_pos, token);
	else if (input[*curr_pos] == '>' || input[*curr_pos] == '<')
		return_value += handle_redirection(input, curr_pos, token);
	else
		return_value += handle_word(input, curr_pos, token);
	return (return_value);
}
