#include "../../includes/minishell.h"

extern int	g_exit_status;

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	minishell->tokens = NULL;
	minishell->cmds = NULL;
	if (!minishell)
	{
		perror("Malloc failed");
		exit(EXIT_FAILURE);
	}
	create_env_list(&minishell, envp);
	g_exit_status = 0;
	return (minishell);
}

void	set_signals(void)
{
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	minishell_loop(t_minishell *minishell)
{
	char	*input_line;

	while (1)
	{
		set_signals();
		input_line = readline(MINISHELL);
		if (input_line == NULL)
		{
			free_minishell(&minishell);
			free_env_list(minishell);
			free(minishell);
			exit(EXIT_SUCCESS);
		}
		if (!*input_line)
		{
			free(input_line);
			continue ;
		}
		add_history(input_line);
		process_input(minishell, input_line);
	}
}
