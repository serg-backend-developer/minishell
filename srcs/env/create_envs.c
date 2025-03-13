#include "../../includes/minishell.h"

int	create_env_list(t_minishell **minishell, char **envp)
{
	int		index;
	t_list	*new_env_node;

	if (!minishell || !*minishell || !envp)
		return (EXIT_FAILURE);
	index = 0;
	(*minishell)->envs = NULL;
	while (envp[index])
	{
		new_env_node = ft_lstnew(ft_strdup(envp[index]));
		ft_lstadd_back(&(*minishell)->envs, new_env_node);
		index++;
	}
	return (EXIT_SUCCESS);
}
