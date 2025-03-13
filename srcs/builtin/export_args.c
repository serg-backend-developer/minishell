#include "../../includes/minishell.h"

extern int	g_exit_status;

static void	process_export_arg(t_minishell **minishell, char *arg);

int	handle_export_cmd(t_minishell **minishell, char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		handle_export_no_args(minishell);
	else
	{
		while (args[i])
		{
			process_export_arg(minishell, args[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

void	update_env_value(t_minishell **minishell, char *arg)
{
	char	*env_name;
	t_list	*env_list;

	env_name = retrieve_env_name(arg);
	env_list = (*minishell)->envs;
	while (env_list)
	{
		if (ft_strncmp(env_list->content, env_name, ft_strlen(env_name)) == 0)
		{
			free(env_list->content);
			env_list->content = arg;
			break ;
		}
		env_list = env_list->next;
	}
	free(env_name);
}

static int	validate_export_arg(char *arg)
{
	int	index;

	index = 0;
	if (!ft_isalpha(arg[index]) && arg[index] != '_')
	{
		display_error("export", arg, "not a valid identifier");
		return (1);
	}
	index++;
	while (arg[index] && arg[index] != '=')
	{
		if (!ft_isalnum(arg[index]) && arg[index] != '_')
		{
			display_error("export", arg, "not a valid identifier");
			return (1);
		}
		index++;
	}
	return (EXIT_SUCCESS);
}

static void	process_export_arg(t_minishell **minishell, char *arg)
{
	char	*env_name;
	char	*env_value;

	if (validate_export_arg(arg))
	{
		g_exit_status = 1;
		return ;
	}
	env_name = retrieve_env_name(arg);
	env_value = retrieve_env_value((*minishell)->envs, env_name);
	if (!env_value)
		ft_lstadd_back(&(*minishell)->envs, ft_lstnew(ft_strdup(arg)));
	else
		update_env_value(minishell, ft_strdup(arg));
	free(env_name);
	free(env_value);
}
