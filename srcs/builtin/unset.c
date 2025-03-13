#include "../../includes/minishell.h"

static void	remove_node_if_matches(
				t_list **list, void *data,
				int (*cmp)(const void *,
					const void *, size_t));

int	unset_env_variable(t_minishell **minishell, char **args)
{
	int	index;

	index = 1;
	while (args[index])
	{
		remove_node_if_matches(
			&((*minishell)->envs),
			args[index],
			(int (*)(const void *, const void *, size_t))ft_strncmp);
		index++;
	}
	return (EXIT_SUCCESS);
}

int	print_env(t_minishell **minishell)
{
	t_list	*env_list;

	env_list = (*minishell)->envs;
	while (env_list)
	{
		printf("%s\n", (char *)env_list->content);
		env_list = env_list->next;
	}
	free_minishell(minishell);
	free_env_list(*minishell);
	free(*minishell);
	exit(EXIT_SUCCESS);
}

static void	remove_node_if_matches(
		t_list **list, void *data,
		int (*cmp)(const void *, const void *, size_t))
{
	t_list	*current_node;

	if (list == NULL || *list == NULL)
		return ;
	current_node = *list;
	if (cmp(current_node->content, data, ft_strlen(data)) == 0)
	{
		*list = current_node->next;
		free(current_node->content);
		free(current_node);
		remove_node_if_matches(list, data, cmp);
	}
	else
	{
		current_node = *list;
		remove_node_if_matches(&current_node->next, data, cmp);
	}
}
