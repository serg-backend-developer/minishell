#include "../../includes/minishell.h"

int	handle_pwd(t_minishell **minishell)
{
	char	*curr_dir;
	char	buffer[4096];

	curr_dir = getcwd(buffer, 4096);
	if (curr_dir != NULL)
		ft_putendl_fd(curr_dir, 1);
	free_minishell(minishell);
	free_env_list(*minishell);
	free(*minishell);
	exit(EXIT_SUCCESS);
}
