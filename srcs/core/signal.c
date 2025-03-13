#include "../../includes/minishell.h"

int	g_exit_status;

void	handle_signal(int signal)
{
	ft_putstr_fd(MINISHELL, 1);
	ft_putstr_fd(rl_line_buffer, 1);
	ft_putstr_fd("  ", 1);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (signal == SIGINT)
		g_exit_status = 1;
}
