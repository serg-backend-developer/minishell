#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	count_args(char **args);
static int	is_numeric(char *str);

int	handle_exit(t_minishell **minishell, char **args)
{
	int	res;

	if (count_args(args) == 3)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_exit_status = 1;
		return (EXIT_SUCCESS);
	}
	else if (args[1] && !(is_numeric(args[1])))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_set(minishell);
		exit(255);
	}
	else if (count_args(args) == 1)
	{
		free_set(minishell);
		exit(g_exit_status);
	}
	res = ft_atoi(args[1]);
	free_set(minishell);
	exit(res);
}

static int	count_args(char **args)
{
	int		count;

	count = 0;
	while (*args)
	{
		count++;
		args++;
	}
	return (count);
}

static int	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (EXIT_SUCCESS);
		str++;
	}
	return (EXIT_FAILURE);
}
