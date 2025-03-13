#include "../../includes/minishell.h"

extern int	g_exit_status;

int	main(int argc __attribute__((unused)),
	char **argv __attribute__((unused)), char **envp)
{
	t_minishell	*minishell;

	welcome();
	minishell = init_minishell(envp);
	minishell_loop(minishell);
	free(minishell);
	return (EXIT_SUCCESS);
}
