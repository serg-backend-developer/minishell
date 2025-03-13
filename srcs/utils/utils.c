#include "../../includes/minishell.h"

void	remove_list_nodes(
	t_list **list, void *value_to_remove,
	int (*cmp)(const char *, const void *))
{
	t_list	*current_node;

	if (list == NULL || *list == NULL)
		return ;
	current_node = *list;
	if (cmp(((t_token *)(current_node->content))->value, value_to_remove) == 0)
	{
		*list = current_node->next;
		free(((t_token *)(current_node->content))->value);
		free(current_node->content);
		free(current_node);
		remove_list_nodes(list, value_to_remove, cmp);
	}
	else
	{
		current_node = *list;
		remove_list_nodes(&current_node->next, value_to_remove, cmp);
	}
}

void	display_error(char *cmd, char *arg, char *error_message)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
}

int	print_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	return (EXIT_SUCCESS);
}

void	free_env_list(t_minishell *minishell)
{
	t_list	*next_env;

	while (minishell->envs)
	{
		next_env = minishell->envs->next;
		free(minishell->envs->content);
		minishell->envs->content = NULL;
		free(minishell->envs);
		minishell->envs = NULL;
		minishell->envs = next_env;
	}
	minishell->envs = NULL;
}

void	free_path_dirs(char **path_dirs)
{
	int	index;

	index = 0;
	while (path_dirs[index])
	{
		free(path_dirs[index]);
		index++;
	}
	free(path_dirs);
}
