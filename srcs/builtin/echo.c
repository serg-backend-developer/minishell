#include "../../includes/minishell.h"

int	handle_echo(t_minishell **minishell, char **args)
{
	int	index;
	int	newline_flag;

	index = 1;
	newline_flag = 0;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline_flag = 1;
		index = 2;
	}
	while (args[index])
	{
		write(1, args[index], ft_strlen(args[index]));
		if (args[index + 1])
			write(1, " ", 1);
		index++;
	}
	if (newline_flag == 0)
		write(1, "\n", 1);
	free_set(minishell);
	exit(EXIT_SUCCESS);
}
