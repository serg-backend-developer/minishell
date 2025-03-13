#include "../../includes/minishell.h"

void	free_set(t_minishell **minishell)
{
	free_minishell(minishell);
	free_env_list(*minishell);
	free(*minishell);
}
