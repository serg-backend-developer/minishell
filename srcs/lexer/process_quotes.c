#include "../../includes/minishell.h"

static void	handle_quotes_in_token(t_minishell **minishell, t_token *token);

int	open_and_process_quotes(t_minishell **minishell)
{
	t_list	*token_node;

	token_node = (*minishell)->tokens;
	while (token_node)
	{
		if (((t_token *)(token_node->content))->category == TOKEN_DOUBLE_QUOTE)
		{
			handle_quotes_in_token(minishell, token_node->content);
			((t_token *)(token_node->content))->category = TOKEN_ARGUMENT;
		}
		token_node = token_node->next;
	}
	return (EXIT_FAILURE);
}

static char	*process_dollar_case(
	char *input_str, int start_idx, int end_idx, char *final_str)
{
	char	*after_dollar;
	char	*temp_str;

	after_dollar = ft_substr(input_str, end_idx, start_idx - end_idx);
	free(input_str);
	temp_str = final_str;
	final_str = ft_strjoin(temp_str, after_dollar);
	free(after_dollar);
	free(temp_str);
	return (final_str);
}

static void	set_token_value_and_len(char *value_str, t_token *token)
{
	if (token->value)
		free(token->value);
	token->value = value_str;
	token->length = ft_strlen(value_str);
}

static char	*process_before_dollar(
	t_token *token, char *before_dollar, char *final_str)
{
	char	*inside_dollar;
	char	*temp_str;

	inside_dollar = token->value;
	token->value = NULL;
	temp_str = ft_strjoin(final_str, before_dollar);
	free(final_str);
	free(before_dollar);
	final_str = ft_strjoin(temp_str, inside_dollar);
	free(inside_dollar);
	free(temp_str);
	return (final_str);
}

static void	handle_quotes_in_token(t_minishell **minishell, t_token *token)
{
	char	*input_str;
	char	*final_str;
	char	*before_dollar;
	int		curr;
	int		k;

	input_str = ft_strdup(token->value);
	curr = 0;
	k = 0;
	final_str = ft_strdup("");
	while (input_str[curr])
	{
		while (input_str[curr] && input_str[curr] != '$')
			curr++;
		if (input_str[curr] == '$')
		{
			before_dollar = ft_substr(input_str, k, curr - k);
			handle_dollar_sign(minishell, input_str, &curr, token);
			k = curr;
			final_str = process_before_dollar(token, before_dollar, final_str);
		}
	}
	final_str = process_dollar_case(input_str, curr, k, final_str);
	set_token_value_and_len(final_str, token);
}
