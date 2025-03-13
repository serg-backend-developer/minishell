#include "../../includes/minishell.h"

static void	free_token_list(t_minishell *minishell);
static void	free_command_list(t_minishell *minishell);

void	free_minishell(t_minishell **minishell)
{
	if ((*minishell)-> tokens)
		free_token_list(*minishell);
	if ((*minishell)-> cmds)
		free_command_list(*minishell);
}

static void	free_token_list(t_minishell *minishell)
{
	t_list	*next_token;

	while (minishell->tokens)
	{
		next_token = minishell->tokens->next;
		free(((t_token *)minishell->tokens->content)->value);
		((t_token *)minishell->tokens->content)->value = NULL;
		free((t_token *)minishell->tokens->content);
		minishell->tokens->content = NULL;
		free((t_token *)minishell->tokens);
		minishell->tokens = NULL;
		minishell->tokens = next_token;
	}
	minishell->tokens = NULL;
}

static void	free_file_list(t_list *file_list)
{
	t_list	*next_file;

	while (file_list)
	{
		next_file = file_list->next;
		free((t_fd *)file_list->content);
		file_list->content = NULL;
		free(file_list);
		file_list = NULL;
		file_list = next_file;
	}
	file_list = NULL;
}

static void	free_command(t_cmd *cmd)
{
	int	index;

	index = 0;
	while (cmd->args[index])
	{
		free(cmd->args[index]);
		cmd->args[index] = NULL;
		index++;
	}
	free(cmd->args);
	cmd->args = NULL;
	if (cmd->files)
		free_file_list(cmd->files);
	cmd->files = NULL;
	cmd->heredoc = NULL;
	free(cmd);
	cmd = NULL;
}

static void	free_command_list(t_minishell *minishell)
{
	t_list	*next_command;

	while (minishell->cmds)
	{
		next_command = minishell->cmds->next;
		free_command(minishell->cmds->content);
		minishell->cmds->content = NULL;
		free(minishell->cmds);
		minishell->cmds = NULL;
		minishell->cmds = next_command;
	}
	minishell->cmds = NULL;
}
