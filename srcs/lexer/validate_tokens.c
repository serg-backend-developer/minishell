#include "../../includes/minishell.h"

static int	merge_tokens_if_needed(t_minishell **minishell);

int	validate_tokens(t_minishell **minishell)
{
	t_list	*token;
	int		token_type;

	open_and_process_quotes(minishell);
	merge_tokens_if_needed(minishell);
	delete_spaces(minishell);
	token = (*minishell)->tokens;
	if (!token)
		return (EXIT_SUCCESS);
	if (((t_token *)(token->content))->category == TOKEN_PIPE)
		return (print_syntax_error());
	while (token)
	{
		token_type = ((t_token *)(token->content))->category;
		if (token_type == TOKEN_REDIR_OUT || token_type == TOKEN_REDIR_IN
			|| token_type == TOKEN_APPEND || token_type == TOKEN_HEREDOC)
		{
			if (!token->next)
				return (print_syntax_error());
			if (((t_token *)(token->next->content))->category != TOKEN_ARGUMENT)
				return (print_syntax_error());
		}
		token = token->next;
	}
	return (EXIT_FAILURE);
}

static int	merge_tokens_if_needed(t_minishell **minishell)
{
	t_list	*curr_token;
	t_list	*next_token;
	char	*merged_str;

	curr_token = (*minishell)->tokens;
	next_token = curr_token->next;
	while (curr_token && next_token)
	{
		if (((t_token *)(curr_token->content))->category == TOKEN_ARGUMENT
			&& ((t_token *)(curr_token->next->content))->category == 4)
		{
			((t_token *)(curr_token->content))->length
				+= ((t_token *)(curr_token->next->content))->length;
			merged_str = ft_strjoin(((t_token *)(curr_token->content))->value,
					(((t_token *)(curr_token->next->content))->value));
			((t_token *)(curr_token->content))->value = merged_str;
			curr_token->next = next_token->next;
			ft_lstdelone(next_token, free);
			next_token = curr_token->next;
			continue ;
		}
		curr_token = curr_token->next;
		next_token = curr_token->next;
	}
	return (EXIT_FAILURE);
}
