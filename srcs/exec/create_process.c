#include "../../includes/minishell.h"

static void	handle_sigint(int signal);

void	create_process(
	int current_pipe[2], int cmd_index, t_list *cmds, int process_ids[1000])
{
	int	index;

	index = cmd_index;
	if (index == 0)
		while (index < 1000)
			process_ids[index++] = 0;
	pipe(current_pipe);
	process_ids[cmd_index] = fork();
	signal(SIGINT, &handle_sigint);
	if (((t_cmd *)cmds->content)->heredoc)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, &handle_sigint);
}

static void	handle_sigint(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", 1);
		ft_putnbr_fd(SIGQUIT, 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
	else
		ft_putstr_fd("\n", 1);
}
