#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	handle_dollar_special_cases(
				char *input, int *curr_index, t_token *parsed_token);
static int	handle_dollar_with_env(
				t_minishell **minishell, char *input,
				int *curr_index, t_token *parsed_token);

int	handle_dollar_sign(
	t_minishell **minishell, char *input,
	int *curr_index, t_token *parsed_token)
{
	int		next_index;

	next_index = *curr_index + 1;
	if (parsed_token->value)
		free(parsed_token->value);
	if (input[next_index] == '?' || input[next_index] == ' '
		|| !input[next_index])
	{
		handle_dollar_special_cases(input, curr_index, parsed_token);
		return (EXIT_SUCCESS);
	}
	handle_dollar_with_env(minishell, input, curr_index, parsed_token);
	return (EXIT_SUCCESS);
}

static int	handle_dollar_special_cases(
	char *input, int *curr_index, t_token *parsed_token)
{
	if (input[*curr_index + 1] == '?')
	{
		parsed_token->value = ft_itoa(g_exit_status);
		parsed_token->length = ft_strlen(parsed_token->value);
		parsed_token->category = TOKEN_ARGUMENT;
		*curr_index = *curr_index + 2;
	}
	else if (input[*curr_index + 1] == ' ' || !input[*curr_index + 1])
	{
		parsed_token->value = ft_strdup("$");
		parsed_token->length = 1;
		parsed_token->category = TOKEN_ARGUMENT;
		*curr_index = *curr_index + 1;
	}
	return (EXIT_SUCCESS);
}

static int	handle_dollar_with_env(
	t_minishell **minishell, char *input,
	int *curr_index, t_token *parsed_token)
{
	int		j;
	char	*var_name;
	char	*env_value;

	j = *curr_index + 1;
	while (input[j] != '\0' && input[j] != ' ' && input[j] != '|'
		&& input[j] != '\'' && input[j] != '\"'
		&& input[j] != '<' && input[j] != '>' && input[j] != '$')
		j++;
	var_name = ft_substr(input, *curr_index + 1, j - *curr_index - 1);
	env_value = retrieve_env_value((*minishell)->envs, var_name);
	if (env_value == NULL)
	{
		parsed_token->value = ft_strdup("");
		free(env_value);
	}
	else
		parsed_token->value = env_value;
	parsed_token->length = ft_strlen(parsed_token->value);
	parsed_token->category = TOKEN_ARGUMENT;
	*curr_index = *curr_index + ft_strlen(var_name) + 1;
	free(var_name);
	return (EXIT_SUCCESS);
}
