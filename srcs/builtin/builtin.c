#include "../../includes/minishell.h"

static int	handle_cd(t_minishell **minishell, char **args);

int	handle_builtin(t_minishell **minishell, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (handle_echo(minishell, args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (handle_cd(minishell, args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (print_env(minishell));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (handle_exit(minishell, args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (handle_export_cmd(minishell, args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (handle_pwd(minishell));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset_env_variable(minishell, args));
	return (EXIT_FAILURE);
}

int	handle_spec(t_minishell **minishell, char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (change_directory(minishell, args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (handle_export_cmd(minishell, args));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (handle_exit(minishell, args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset_env_variable(minishell, args));
	return (EXIT_FAILURE);
}

static int	handle_cd(t_minishell **minishell, char **args)
{
	if (change_directory(minishell, args))
	{
		free_minishell(minishell);
		free_env_list(*minishell);
		free(*minishell);
		exit(EXIT_ERROR);
	}
	free_minishell(minishell);
	free_env_list(*minishell);
	free(*minishell);
	exit(EXIT_SUCCESS);
}
