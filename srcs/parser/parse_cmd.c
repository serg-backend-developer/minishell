#include "../../includes/minishell.h"

static void	create_command(t_cmd *cmd, t_list **tokens);

void	parse_commands(t_minishell **minishell)
{
	t_list	*command_node;
	t_list	*current_token;
	t_cmd	*new_command;
	int		token_type;

	(*minishell)->cmds = NULL;
	current_token = (*minishell)->tokens;
	while (current_token)
	{
		token_type = ((t_token *)(current_token->content))->category;
		if (token_type == TOKEN_ARGUMENT || token_type == TOKEN_REDIR_OUT || \
			token_type == TOKEN_REDIR_IN || token_type == TOKEN_HEREDOC)
		{
			new_command = (t_cmd *)malloc(sizeof(t_cmd));
			create_command(new_command, &current_token);
			command_node = ft_lstnew(new_command);
			ft_lstadd_back(&(*minishell)->cmds, command_node);
		}
		else
			current_token = current_token->next;
	}
}

static int	count_arguments(t_list *tokens)
{
	int		count;
	t_list	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (((t_token *)(current->content))->category == TOKEN_ARGUMENT)
			count++;
		else if (((t_token *)(current->content))->category == TOKEN_PIPE)
			break ;
		current = current->next;
	}
	return (count);
}

static int	process_token(t_cmd *cmd, t_list **tokens, int *arg_index, int flag)
{
	t_fd	*file;

	if (flag == 0)
	{
		(cmd->args)[*arg_index] = ft_strdup(
				((t_token *)((*tokens)->content))->value);
		(*arg_index)++;
	}
	else
	{
		if (flag == TOKEN_HEREDOC)
			cmd->heredoc = ((t_token *)((*tokens)->content))->value;
		else if (flag == TOKEN_REDIR_OUT || flag == TOKEN_REDIR_IN
			|| flag == TOKEN_APPEND)
		{
			file = malloc(sizeof(t_fd));
			if (!file)
				return (flag);
			file->filename = ((t_token *)((*tokens)->content))->value;
			file->mode = flag;
			ft_lstadd_back(&cmd->files, ft_lstnew(file));
		}
		flag = 0;
	}
	return (flag);
}

static void	create_command(t_cmd *cmd, t_list **tokens)
{
	int	token_type;
	int	arg_count;
	int	arg_index;
	int	flag;

	arg_count = count_arguments(*tokens);
	cmd->args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	cmd->files = NULL;
	cmd->heredoc = NULL;
	arg_index = 0;
	flag = 0;
	while (*tokens)
	{
		token_type = ((t_token *)((*tokens)->content))->category;
		if (token_type == TOKEN_PIPE)
			break ;
		if (token_type == TOKEN_REDIR_OUT || token_type == TOKEN_REDIR_IN
			|| token_type == TOKEN_APPEND || token_type == TOKEN_HEREDOC)
			flag = token_type;
		else if (token_type == TOKEN_ARGUMENT)
			flag = process_token(cmd, tokens, &arg_index, flag);
		*tokens = (*tokens)->next;
	}
	(cmd->args)[arg_index] = NULL;
}
